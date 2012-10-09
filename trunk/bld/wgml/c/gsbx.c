/****************************************************************************
*
*                            Open Watcom Project
*
*  Copyright (c) 2004-2009 The Open Watcom Contributors. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description: implement .bx (box)  script control word
*                    and related routines                            TBD
*
*  comments are from script-tso.txt
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1      /* use safer C library              */

#include "wgml.h"
#include "gvars.h"

/**************************************************************************/
/* BOX generates the horizontal lines and initiates the vertical lines of */
/* a box.                                                                 */
/*                                                                        */
/* 旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커           */
/* |     |                                                    |           */
/* |     | <h1 </> ... hn>                                    |           */
/* | .BX | <NEW|ON|OFF|SET> <h1 </> ... hn>                   |           */
/* |     | <CANCEL>                                           |           */
/* |     | <CHAR name>                                        |           */
/* |     |                                                    |           */
/* 읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸           */
/*                                                                        */
/* SCRIPT generates a box by constructing line segments through character */
/* positions or "cells".                                                  */
/*                                                                        */
/* Line Segments                                                          */
/*                                                                        */
/* There are only four possible line segments in a character cell, each   */
/* of which can be described in terms of movement from the center of the  */
/* cell to one of its four sides:                                         */
/* (1) horizontal right (from the center of the cell to the right side of */
/*     the cell)                                                          */
/* (2) horizontal left (from the center of the cell to the left side of   */
/*     the cell)                                                          */
/* (3) vertical ascender (from the center of the cell to the top of the   */
/*     cell)                                                              */
/* (4) vertical descender (from the center of the cell to the bottom of   */
/*     the cell)                                                          */
/*                                                                        */
/* In the operand descriptions below, the following two generalizations   */
/* are made:                                                              */
/* (1) horizontal rule (all of the horizontal segments from the center of */
/*     one cell to the center of a cell somewhere to the right on the     */
/*     same output line)                                                  */
/* (2) vertical rule (a vertical line from the top of one cell to the     */
/*     bottom of that same cell; that is, a vertical ascender plus a      */
/*     vertical descender)                                                */
/*                                                                        */
/* Operands                                                               */
/*                                                                        */
/* <h1 </> ... hn>: When used with numeric operands "h1 ... hn" only,     */
/*    .BX begins a single box by generating a horizontal rule with        */
/*    vertical descenders in the specified columns; if a previous box is  */
/*    still in effect, then the horizontal rule is generated from the     */
/*    leftmost vertical position of the two boxes to the rightmost        */
/*    vertical position of the two boxes, with vertical ascenders in the  */
/*    vertical positions of the previous box, and the previous box defi-  */
/*    nition is terminated. On all subsequent output lines until the      */
/*    next .BX control word is encountered, vertical rules will be gener- */
/*    ated in the specified columns.                                      */
/*       The numeric operands are relative to the current ADJUST (.ad)    */
/*    value, and must be specified in increasing column order. A signed   */
/*    numeric operand is relative to the preceding operand.               */
/*       When a Box definition is in effect and a .BX with no operands is */
/*    encountered, a horizontal rule is generated from the leftmost       */
/*    vertical position to the rightmost vertical position, with vertical */
/*    ascenders and descenders in all of the vertical positions.          */
/*       A single numeric operand defines a box with only one vertical    */
/*    descender.                                                          */
/*       The character '/' between numeric operands defines multiple      */
/*    side-by-side boxes between which no horizontal rules will be gener- */
/*    ated.                                                               */
/* ON <h1 </> ... hn>: When a box definition is in effect and SCRIPT      */
/*    encounters a new box definition that is specified using only        */
/*    numeric operands, the horizontal rule that closes the first box and */
/*    starts the second box is generated from the leftmost to the right-  */
/*    most of the vertical positions of the two boxes. "ON" as the first  */
/*    operand of the second box definition will suppress those parts of   */
/*    the horizontal rule that are not part of either box, in cases where */
/*    the two boxes are not vertically aligned.                           */
/* NEW <h1 </> ... hn>: superimposes the definition for this box on top   */
/*    of the previous box definition. If the new box overlaps the         */
/*    previous box, none of the line segments "beneath" the new box will  */
/*    be generated. This allows boxes to be drawn within or on top of     */
/*    boxes. The superimposed segments of the previous box will become    */
/*    visible again once the new box definition is terminated.            */
/*       If no column operands are present or if no previous box is still */
/*    in effect, then the "NEW" operand is ignored.                       */
/* SET <h1 </> ... hn>: is treated in all respects like "NEW" with the    */
/*    exception that the definition for the new box is put into effect    */
/*    without generating the horizontal rule or the vertical ascenders    */
/*    and descenders.                                                     */
/* OFF <h1 </> ... hn>: terminates the definition of the current box by   */
/*    generating the "bottom" horizontal rule and the appropriate         */
/*    vertical ascenders.                                                 */
/*       Any numeric column operands used with "OFF" will cause the hori- */
/*    zontal rule to be generated from the leftmost to the rightmost of   */
/*    the combination of the defined and specified vertical positions,    */
/*    with vertical ascenders in all of those positions. If no box is in  */
/*    effect when the OFF is encountered, only the numeric operands spec- */
/*    ified with the OFF determine the positions of the horizontal rule   */
/*    and vertical ascenders.                                             */
/*       If current box was started with NEW or SET, the vertical         */
/*    descenders of the previous box will also be generated.              */
/* CANcel (alias "DELETE"): terminates the definition of the current box  */
/*    without generating its closing horizontal rule and vertical ascen-  */
/*    ders.                                                               */
/* CHAR <TRM|32T|TNC|38C|GPC|APL>: specifies the character set that is    */
/*    to be used by SCRIPT in constructing the four line segments needed  */
/*    for boxes. By default, when SCRIPT is producing output for a        */
/*    terminal, the CHAR TRM set of "-", "|" and "+" is used to give a    */
/*    gross approximation of horizontal rules, vertical rules, and inter- */
/*    sections. In other cases, such as output to a line printer, SCRIPT  */
/*    uses the CHAR TNC set of special box-drawing characters for the TN  */
/*    print train; this results in a better approximation, although still */
/*    not exact. With the CHAR operand, the named set of characters will  */
/*    always be used, independent of the output device.                   */
/*       The IBM 3270 "text terminal" is specified by "32T". The IBM      */
/*    3800 character set with the long "or" bar is specified by "38C".    */
/*    The IBM 3800 GP12 font without the long "or" bar is specified by    */
/*    "GPC". The APL character set is specified by "APL".                 */
/*                                                                        */
/* Debugging Aid                                                          */
/*                                                                        */
/* CHAR HEX: The HEX operand is provided as a "debugging aid". Each       */
/*    character cell in which one or more of the four line segments       */
/*    occurs will be printed using one of the hexadecimal characters in   */
/*    the sequence 0123456789ABCDEF, to represent combinations of a 4-bit */
/*    pattern "xxxx" where each "x" is a 0 or a 1.                        */
/*       This pattern can best be discussed in terms of "8421". The "8"   */
/*    position represents "vertical ascender". The "4" position repre-    */
/*    sents "vertical descender". The "2" position represents "horizontal */
/*    left". The "1" position represents "horizontal right".              */
/*    Therefore, a character cell printed as "E" represents "1110", which */
/*    indicates that the cell contains a vertical ascender, a vertical    */
/*    descender, and a horizontal left. If CHAR TRM were in effect        */
/*    instead, SCRIPT would approximate that cell with a "+", which is    */
/*    clearly incorrect but is the best that can be done for that kind of */
/*    output device. If SCRIPT must approximate, it does so by            */
/*    displaying more than really exists, since displaying less could     */
/*    result in a blank cell.                                             */
/*                                                                        */
/* This control word creates a break.                                     */
/**************************************************************************/

typedef enum {
    bx_none,
    bx_on,
    bx_off,
    bx_new,
    bx_set,
    bx_can,
} bx_op;

/***************************************************************************/
/*  output blank lines with vertical box characters                        */
/***************************************************************************/

static void box_blank_lines( uint32_t lines )
{
    doc_element *   blank_el;
    int             i;
    int             i_b;
    text_chars  *   cur_chars;
    text_line   *   cur_blank;
    uint32_t        height;

    if( lines == 0 ) {          // why are we here?
        return;
    }

    height = wgml_fonts[g_curr_font_num].line_height;
    lines /= height;
    blank_el = alloc_doc_el( el_text );
    blank_el->depth = height + g_spacing;

    for( i = 0; i < lines; i++ ) {
        if( i == 0 ) {
            cur_blank = alloc_text_line();
            blank_el->element.text.first = cur_blank;
        } else {
            cur_blank->next = alloc_text_line();
            cur_blank = cur_blank->next;
        }
        cur_blank->line_height = height;
        for( i_b = 0; i_b < box_line.current; i_b++ ) {
            if( i_b == 0 ) {
                cur_chars = alloc_text_chars( &bin_device->box.vertical_line, 1,
                                              g_curr_font_num );
                cur_blank->first = cur_chars;
            } else {
                cur_chars->next = alloc_text_chars( &bin_device->box.vertical_line, 1, 
                                                    g_curr_font_num );
                cur_chars->next->prev = cur_chars;
                cur_chars = cur_chars->next;
            }
            cur_chars->x_address = box_line.cols[i_b].col + g_page_left -
                                                                       box_col_width;
            cur_chars->width = cop_text_width( cur_chars->text, cur_chars->count,
                                                                g_curr_font_num );
        }
        cur_blank->last = cur_chars;
    }
    insert_col_main( blank_el );

    return;
}

/***************************************************************************/
/*  merge prev_line and cur_line into box_line                             */
/***************************************************************************/

static void merge_lines( void )
{
    int             cur_col;
    int             line_col;
    int             prev_col;

/// temp
    out_msg( "Existing\n" );
    for( prev_col = 0; prev_col < prev_line.current; prev_col++ ) {
        out_msg( "column: %i ind: %i\n", prev_line.cols[prev_col].col, prev_line.cols[prev_col].ind );
    }

    out_msg( "Current\n" );
    for( cur_col = 0; cur_col < cur_line.current; cur_col++ ) {
        out_msg( "column: %i ind: %i\n", cur_line.cols[cur_col].col, cur_line.cols[cur_col].ind );
    }
/// end temp section

    cur_col = 0;
    line_col = 0;
    prev_col = 0;
    while( (cur_col < cur_line.current) || (prev_col < prev_line.current) ) {
        if( cur_col == cur_line.current ) {  // only prev_line now has entries
            box_line.cols[line_col].col = prev_line.cols[prev_col].col;
            box_line.cols[line_col].ind = prev_line.cols[prev_col].ind;
            box_line.current++;
            line_col++;
            prev_col++;
        } else if( prev_col == prev_line.current ) { // only cur_line now has entries
            box_line.cols[line_col].col = cur_line.cols[cur_col].col;
            box_line.cols[line_col].ind = cur_line.cols[cur_col].ind;
            box_line.current++;
            cur_col++;
            line_col++;
        } else if( cur_line.cols[cur_col].col < box_line.cols[prev_col].col ) {
            box_line.cols[line_col].col = cur_line.cols[cur_col].col;
            box_line.cols[line_col].ind = cur_line.cols[cur_col].ind;
            box_line.current++;
            cur_col++;
            line_col++;
        } else if( cur_line.cols[cur_col].col > box_line.cols[prev_col].col ) {
            box_line.cols[line_col].col = prev_line.cols[prev_col].col;
            box_line.cols[line_col].ind = prev_line.cols[prev_col].ind;
            box_line.current++;
            line_col++;
            prev_col++;
        } else {                            // equal column values
            box_line.cols[line_col].col = cur_line.cols[cur_col].col;
/// this may need more thought: suppose the ind fields differ?
            box_line.cols[line_col].ind = cur_line.cols[cur_col].ind;
            box_line.current++;
            line_col++;
            cur_col++;
            prev_col++;
        }
    }

/// temp
    out_msg( "Merged\n" );
    for( line_col  = 0; line_col  < box_line.current; line_col ++ ) {
        out_msg( "column: %i ind: %i\n", box_line.cols[line_col ].col, box_line.cols[line_col ].ind );
    }
/// end temp section

    return;
}

/***************************************************************************/
/*  implement control word BX                                              */
/*  some notes on how wgml 4.0 appears to differ from the TSO:             */
/*    ON <h1 </> ... hn> differs from <h1 </> ... hn> in that columns      */
/*      added outside the existing list of columns are treated as if "/"   */
/*      separated them from the first (if before) or last (if after)       */
/*      column, but only if there is one value after ON                    */
/*    SET, in character devices, produces a blank output line; in PS, it   */
/*      appears that no output at all occurs                               */
/*    CHAR is accepted but has no effect on the output; indeed, any token, */
/*      including HEX, or no token at all, can follow CHAR with no effect  */
/*      on the output and no error message                                 */
/*  despite what the TSO says at the start, operands BEGIN, END, YES, NO,  */
/*      and PURGE are not recognized by wgml 4.0 when used with BX         */
/*  control word AD is not used in the Open Watcom documents and so has    */
/*      not been implemented. Were it to be implemented, it's effects      */
/*      would be part of the left start position for text from which the   */
/*      BX columns are measured                                            */
/***************************************************************************/

void scr_bx( void )
{
    bool            go_down;
    bool            go_up;
    bx_h_ind        cur_ind;
    bx_op           cur_op;
    char        *   p;
    char        *   pa;
    doc_element *   box_el;         // holds the box line itself, for char devices
    doc_element *   cur_el;
    doc_element *   sav_el;         // used to isolate a GRAPHIC element
    int             i;              // overall index
    int             i_b;            // box_line index
    int             i_c;            // cur_line index
    int             i_p;            // prev_line index
    size_t          len;
    su              boxcolwork;
    text_chars  *   cur_chars;      // current text_chars in cur_text
    text_chars  *   new_chars;      // text_chars to be inserted into cur_text
    text_line   *   cur_text;       // current text_line
    uint32_t        c_current;      // cur_line.current
    uint32_t        cur_col;        // current column (not hbus)
    uint32_t        p_current;      // prev_line.current
    uint32_t        skippage;       // lines to skip (not hbus)
    uint32_t        cur_pos;        // current box column position (hbus)
    uint32_t        last_pos;       // last text_char text end position (hbus)
    
    scr_process_break();                // break processing

    p = scan_start;
    while( *p && *p != ' ' ) {          // over cw
        p++;
    }

    while( *p && (*p == ' ') ) {
        p++;
    }
    pa = p;
    while( *p && (*p != ' ') ) {
        p++;
    }
    len = p - pa;

    /* Identify any non-numeric operand */

    cur_op = bx_none;
    if( (len == 2) && !memicmp( pa , "on", len ) ) {
        cur_op = bx_on;
    } else if( len == 3 ) {
        if( !memicmp( pa , "can", len ) || !memicmp( pa , "del", len ) ) {
            cur_op = bx_can;
        } else if( !memicmp( pa , "new", len ) ) {
            cur_op = bx_new;
        } else if( !memicmp( pa , "off", len ) ) {
            cur_op = bx_off;
        } else if( !memicmp( pa , "set", len ) ) {
            cur_op = bx_set;
        }
    } else if( (len == 4) && !memicmp( pa , "char", len ) ) {
        scan_restart = scan_stop + 1;
        return;
    }

    if( cur_op == bx_none ) {               // reuse token if not recognized
        p = pa;
    }

    /* Now for the numerics, if any */

    cur_line.current = 0;                                   // clear cur_line
    if( *p ) {
        while( *p ) {
            if( cur_line.current == 0 ) {
                cur_line.cols[cur_line.current].ind = bx_h_rule;
                if( *p == '/' ) {
                    xx_line_err( err_spc_not_valid, p );
                    p++;
                }
            } else if( *p == '/' ) {
                cur_line.cols[cur_line.current - 1].ind = bx_h_stop;
                cur_line.cols[cur_line.current].ind = bx_h_start;
                p++;
            } else {
                cur_line.cols[cur_line.current].ind = bx_h_rule;
            }
            pa = p;
            if( !cw_val_to_su( &p, &boxcolwork ) ) {
                cur_line.cols[cur_line.current].col = conv_hor_unit( &boxcolwork );
#if 0
                if( boxcolwork.su_relative ) {
                    boxcolwork += g_indent;
                }
#endif
            } else {
                xx_line_err( err_spc_not_valid, pa );
            }
            while( *p && (*p == ' ') ) {
                p++;
            }
            cur_line.current++;
        }
    }

    /* Generate the list of box columns for the current horizontal line */
    box_line.current = 0;                           // clear box_line
    switch( cur_op ) {
    case bx_none :
        merge_lines();
        break;    
    case bx_on :
        merge_lines();
        break;    
    case bx_off :
        merge_lines();
        break;    
    case bx_new :
        merge_lines();
        break;    
    case bx_can :
        merge_lines();
        break;    
    default :
        internal_err( __FILE__, __LINE__ );
        break;    
    }

    ProcFlags.group_elements = false;   // stop accumulating doc_elements

    /* Create the doc_element to hold the box line */

    set_skip_vars( NULL, NULL, NULL, spacing, bin_device->box.font_number );
    box_el = alloc_doc_el( el_text );
    box_el->blank_lines = g_blank_lines;
    g_blank_lines = 0;
    box_el->subs_skip = g_subs_skip;
    box_el->top_skip = g_top_skip;
    box_el->element.text.overprint = ProcFlags.overprint;
    ProcFlags.overprint = false;
    box_el->element.text.spacing = g_spacing;

/// this is for char devices only; expansion will be needed to encompass PS
/// using hline and vline!

    /* construct the box line */
    box_el->element.text.first = alloc_text_line();
    box_el->element.text.first->line_height =
                                wgml_fonts[bin_device->box.font_number].line_height;
    box_el->depth = box_el->element.text.first->line_height + g_spacing;

    len = ((box_line.cols[box_line.current - 1].col - box_line.cols[0].col)
          / box_col_width);
    box_el->element.text.first->first = alloc_text_chars( NULL, len,
                                                   bin_device->box.font_number );
    box_el->element.text.first->first->x_address = box_line.cols[0].col +
                                                        g_page_left - box_col_width;

    p = box_el->element.text.first->first->text;
    i_b = 0;
    i_c = 0;
    i_p = 0;
    c_current = cur_line.current;
    p_current = prev_line.current;
    cur_col = box_line.cols[0].col;
    for( i = 0; i <= len; i++ ) {                    // iterate over all output columns
        if( cur_col < box_line.cols[i_b].col ) {    // not a box column
            *p = bin_device->box.horizontal_line;
        } else {                                    // box column found
            go_down = false;
            go_up = false;
            cur_ind = box_line.cols[i_b].ind;       // for eventual use, TBD
            if( (i_p < p_current) && (cur_col == prev_line.cols[i_p].col) ) {
                go_up = true;
                i_p++;
            }
            if( cur_op == bx_off ) {
                if( (i_c < c_current) && (cur_col == cur_line.cols[i_c].col) ) {
                    go_down = true;
                    i_c++;
                }
            } else {                                // mid-box line
                go_down = true;
            }
            if( i_b == 0 ) {                        // first box column
                if( go_down && go_up ) {            // both up and down
                    *p = bin_device->box.left_join;
                } else if( go_down ) {              // down only
                    *p = bin_device->box.top_left;
                } else {                            // up only
                    *p = bin_device->box.bottom_left;
                }
            } else if( i_b == box_line.current - 1 ) { // last box column
                if( go_down && go_up ) {            // both up and down
                    *p = bin_device->box.right_join;
                } else if( go_down ) {              // down only
                    *p = bin_device->box.top_right;
                } else {                            // up only
                    *p = bin_device->box.bottom_right;
                }
            } else {                                // all other box columns
                if( go_down && go_up ) {            // both up and down
                    *p = bin_device->box.inside_join;
                } else if( go_down ) {              // down only
                    *p = bin_device->box.top_join;
                } else {                            // up only
                    *p = bin_device->box.bottom_join;
                }
            }
            cur_col = box_line.cols[i_b].col;
            i_b++;
        }
        p++;
        cur_col += box_col_width;
        box_el->element.text.first->first->count++;
    }

    box_el->element.text.first->first->width =      // text is known to contain no tabs
                        cop_text_width( box_el->element.text.first->first->text,
                                        box_el->element.text.first->first->count,
                                        bin_device->box.font_number );

#if 0 // this will be needed eventually
    if( t_doc_el_group.first != NULL ) {
        t_doc_el_group.depth += (t_doc_el_group.first->blank_lines +
                                t_doc_el_group.first->subs_skip);
    }
    if( (t_doc_el_group.depth + t_page.cur_depth) > t_page.max_depth ) {
        /*  the block won't fit on this page */

        if( t_doc_el_group.depth  <= t_page.max_depth ) {
            /*  the block will on the next page */

            do_page_out();
            reset_t_page();
        }
    }
#endif

    /* line-drawing devices using BOX characters do not use vertical ascenders */

    cur_el = t_doc_el_group.first;
    t_doc_el_group.depth    = 0;
    t_doc_el_group.first    = NULL;
    t_doc_el_group.last     = NULL;

    if( !ProcFlags.has_aa_block ) {             // character device
        while( cur_el != NULL ) {
            if( !ProcFlags.page_started && (cur_el->blank_lines == 0) ) {
                skippage = cur_el->top_skip;
            } else {
                skippage = cur_el->blank_lines + cur_el->subs_skip;
            }
            if( skippage > 0 ) {            // convert skipped lines to output lines
                box_blank_lines( skippage );
                cur_el->top_skip = 0;
                cur_el->blank_lines = 0;
                cur_el->subs_skip = 0;
            }

            switch( cur_el->type ) {
            case el_text:

                /* insert vertical ascenders into the text lines */

                cur_text = cur_el->element.text.first;
                while( cur_text != NULL ) {
                    cur_chars = cur_text->first;
                    for( i_b = 0; i_b < box_line.current; i_b++ ) {
                        if( cur_chars == NULL ) {
                            new_chars = cur_text->last;
                            new_chars->next = alloc_text_chars( &bin_device->box.vertical_line,
                                                      1, g_curr_font_num );
                            new_chars->next->prev = new_chars;
                            new_chars->next->x_address = box_line.cols[i_b].col + g_page_left
                                                                      - box_col_width;
                            new_chars->width = cop_text_width( new_chars->text,
                                                new_chars->count, g_curr_font_num );
                            cur_text->last = new_chars->next;
                        } else {
                            if( cur_chars == cur_text->first ) {    // first text_chars
                                last_pos = g_page_left - 1;
                            } else {
                                last_pos = cur_chars->prev->x_address +
                                           cur_chars->prev->width;
                            }
                            cur_pos = box_line.cols[i_b].col + g_page_left - box_col_width;
                            if( (cur_pos > last_pos) && (cur_chars->x_address > cur_pos) ) {

                                /* box col position is not inside any text_chars */

                                new_chars = alloc_text_chars( &bin_device->box.vertical_line,
                                                          1, g_curr_font_num );
                                new_chars->x_address = box_line.cols[i_b].col + g_page_left
                                                                      - box_col_width;
                                new_chars->width = cop_text_width( new_chars->text,
                                        new_chars->count, g_curr_font_num );
                                if( cur_chars->prev == NULL ) { // first text_chars in cur_text
                                    cur_text->first = new_chars;
                                } else {
                                    new_chars->prev = cur_chars->prev;
                                    cur_chars->prev->next = new_chars;
                                }
                                new_chars->next = cur_chars;
                                cur_chars->prev = new_chars;

                                cur_chars = cur_chars->next;
                            } else {
                                cur_chars = cur_chars->next;
                            }
                        }    
                    }
                    cur_text = cur_text->next;
                }

                /* insert the element into the page */

                sav_el = cur_el;
                cur_el = cur_el->next;
                sav_el->next = NULL;
                insert_col_main( sav_el );
                break;

            case el_graph:

                /* replace GRAPHIC elements with blank lines */

                box_blank_lines( cur_el->depth );
                sav_el = cur_el;
                cur_el = cur_el->next;
                sav_el->next = NULL;
                add_doc_el_to_pool( sav_el );
                break;

            default:

                /* insert the element into the page */

                sav_el = cur_el;
                cur_el = cur_el->next;
                sav_el->next = NULL;
                insert_col_main( sav_el );
            }
        }
    } else {
        while( cur_el != NULL ) {
            insert_col_main( cur_el );
            cur_el = cur_el->next;
        }
    }

    if( prev_line.current != 0 ) {  // not first BX line
        if( !ProcFlags.page_started && (t_doc_el_group.first->blank_lines == 0) ) {
            skippage = box_el->top_skip;
        } else {
            skippage = box_el->blank_lines + box_el->subs_skip;
        }
        if( skippage > 0 ) {
            box_blank_lines( skippage );
            box_el->top_skip = 0;
            box_el->blank_lines = 0;
            box_el->subs_skip = 0;
        }
    }
    insert_col_main( box_el );  // insert the box line

    if( ( cur_op == bx_off ) || ( cur_op == bx_can ) ) {
        box_line.current = 0;               // clear box_line
    } else {
        ProcFlags.skips_valid = false;      // force set_skip_vars() in process_line_full()
        ProcFlags.group_elements = true;    // start accumulating doc_elements
    }

    prev_line.current = box_line.current;   // box_line becomes prev_line
    prev_line.length = box_line.length;
    for( i = 0; i < box_line.current; i++ ) {
        prev_line.cols[i].col = box_line.cols[i].col;
        prev_line.cols[i].ind = box_line.cols[i].ind;
    }

    scan_restart = scan_stop + 1;
    return;
}

