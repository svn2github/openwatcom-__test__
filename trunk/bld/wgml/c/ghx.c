/****************************************************************************
*
*                            Open Watcom Project
*
*  Copyright (c) 2004-2011 The Open Watcom Contributors. All Rights Reserved.
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
* Description:  WGML tags :H0 :H1 :H2 :H3 :H4 :H5 :H6 processing
*
*                  stitle is not implemented: not used in OW documentation
****************************************************************************/
#include    "wgml.h"
#include    "gvars.h"

static char hnumx[7] = "$hnumX";


/***************************************************************************/
/*  construct Header numbers  1.2.3.V ...                                  */
/*  and update $headn global variable                                      */
/***************************************************************************/

static void update_headnumx( int lvl, char *hnumstr, size_t hnsize )
{
    size_t          pos;
    char          * pn;
    int             rc;

    *hnumstr = 0;
    pos = 0;
    if( layout_work.hx[lvl].number_form == none ) {
        return;                         // no number output
    }

    if( lvl > 0 ) {               // reuse formatted number from previous lvl
       if( (layout_work.hx[lvl].number_form == num_prop) &&
           (layout_work.hx[lvl - 1].headnsub != NULL) ) {

           strcpy( hnumstr, layout_work.hx[lvl - 1].headnsub->value );
           pos = strlen( hnumstr );
       }
    }
    if( pos > 0 ) {             // we have a formatted number from parent lvl
       *(hnumstr + pos) = layout_work.heading.delim;
       pos++;
       *(hnumstr + pos) = 0;
    }
    pn = format_num( layout_work.hx[lvl].headn, hnumstr + pos, hnsize - pos,
                     layout_work.hx[lvl].number_style );
    if( pn != NULL ) {
         pos += strlen( pn );           // all ok
    } else {
         pn = hnumstr + pos;
         *pn = '?';                     // create dummy number
         *(pn + 1) = 0;
         pos++;
    }

    if( layout_work.hx[lvl].headnsub == NULL ) {// first time here
        rc = add_symvar_addr( &global_dict, hnumx, hnumstr, no_subscript, 0,
                              &layout_work.hx[lvl].headnsub );
    } else {
        if( strlen( layout_work.hx[lvl].headnsub->value ) < strlen( hnumstr ) ) {     // need more room
            layout_work.hx[lvl].headnsub->value =
                mem_realloc( layout_work.hx[lvl].headnsub->value, strlen( hnumstr ) + 1 );
        }
        strcpy_s( layout_work.hx[lvl].headnsub->value, strlen( hnumstr ) + 1, hnumstr );
    }
}


/***************************************************************************/
/*  output hx Header  only  called if display_heading = yes                */
/***************************************************************************/

static void hx_header( int hx_lvl, const char *hnumstr, const char *txt )
{
//    doc_element     *   cur_el;
    font_number         font_save;
    font_number         font;
    int32_t             width;
    int32_t             widthn;
    text_chars      *   curr_t;
    text_chars      *   curr_tn;
    text_line       *   hd_line;

    hd_line = NULL;
    font_save = g_curr_font;
    spacing = layout_work.hx[hx_lvl].spacing;

    if( layout_work.hx[hx_lvl].line_break ) {
        set_skip_vars( &layout_work.hx[hx_lvl].pre_skip,
                       &layout_work.hx[hx_lvl].pre_top_skip,
                       &layout_work.hx[hx_lvl].post_skip,
                       spacing,
                       layout_work.hx[hx_lvl].number_font );
    } else {
        set_skip_vars( &layout_work.hx[hx_lvl].pre_skip,
                       &layout_work.hx[hx_lvl].pre_top_skip,
                       NULL,
                       spacing,
                       layout_work.hx[hx_lvl].number_font );
    }

    post_space = 0;

    curr_t  = NULL;
    curr_tn = NULL;
    width   = 0;
    widthn  = 0;

    if( layout_work.hx[hx_lvl].number_form != none ) {
        font = layout_work.hx[hx_lvl].number_font;
        process_text( hnumstr, font );        
    }

    if( (txt != NULL) && (*txt != '\0') ) {
        font = layout_work.hx[hx_lvl].font;
        process_text( txt, font );        
    }
}

/***************************************************************************/
/*  :H0 - :H6  common processing                                           */
/***************************************************************************/

static void gml_hx_common( const gmltag * entry, int hx_lvl )
{
    bool            id_seen     = false;
    char        *   headp;
    char            hnumstr[64];
    char            id[ID_LEN];
    char        *   p;
    int             k;
    int             rc;
    size_t          current;
    size_t          headlen;
    size_t          txtlen;
    ref_entry   *   cur_ref;

    static char     headx[7]    = "$headX";
    static char     htextx[8]   = "$htextX";
    static char     hxstr[4]    = ":HX";

    *(hxstr + 2) = '0' + hx_lvl;
    htextx[6] = '0' + hx_lvl;
    hnumx[5] = '0' + hx_lvl;
    headx[5] = '0' + hx_lvl;

    switch( hx_lvl ) {
    case   0:
        if( !((ProcFlags.doc_sect == doc_sect_body) ||
            (ProcFlags.doc_sect_nxt == doc_sect_body)) ) {

            g_err( err_tag_wrong_sect, hxstr, ":BODY section" );
            err_count++;
            file_mac_info();
        }
        break;
    case  1:
        if( !((ProcFlags.doc_sect >= doc_sect_body) ||
            (ProcFlags.doc_sect_nxt >= doc_sect_body)) ) {

            g_err( err_tag_wrong_sect, hxstr, ":BODY :APPENDIX :BACKM sections" );
            err_count++;
            file_mac_info();
        }
        break;
    default:
        if( !((ProcFlags.doc_sect >= doc_sect_abstract) ||
            (ProcFlags.doc_sect_nxt >= doc_sect_abstract)) ) {

            g_err( err_tag_wrong_sect, hxstr, ":ABSTRACT section or later" );
            err_count++;
            file_mac_info();
        }
        break;
    }
    if( layout_work.hx[hx_lvl].number_form != num_none ) {
        layout_work.hx[hx_lvl].headn++;
    }

    p = scan_start;
    if( *p == '.' ) p++;                // possible tag end
    while( *p == ' ' ) p++;             // skip initial spaces

    for( ;; ) {
        while( *p == ' ' ) {            // over WS to attribute
            p++;
        }
        if( *p == '\0' ) {              // end of line: get new line
            if( !(input_cbs->fmflags & II_eof) ) {
                if( get_line( true ) ) {// next line for missing attribute
 
                    process_line();
                    scan_start = buff2;
                    scan_stop  = buff2 + buff2_lg;
                    if( (*scan_start == SCR_char) ||    // cw found: end-of-tag
                        (*scan_start == GML_char) ) {   // tag found: end-of-tag
                        ProcFlags.tag_end_found = true; 
                        break;          
                    } else {
                        p = scan_start; // new line is part of current tag
                        continue;
                    }
                }
            }
        }
        if( !strnicmp( "id", p, 2 ) ) {
            p += 2;
            p = get_refid_value( p, id );
            if( val_start == NULL ) {
                break;
            }
            id_seen = true;             // valid id attribute found
            if( ProcFlags.tag_end_found ) {
                break;
            }
        } else if( !strnicmp( "stitle", p, 6 ) ) {
            p += 6;

            g_warn( wng_unsupp_att, "stitle" );
            wng_count++;
            file_mac_info();

            p = get_att_value( p );

            scan_start = p;
            if( !ProcFlags.tag_end_found ) {
                continue;
            }
            break;
        } else {    // no match = end-of-tag in wgml 4.0
            ProcFlags.tag_end_found = true;
            break;
        }
    }

    /************************************************************************/
    /*  set the global vars $headx, $headnumx, $htextx                      */
    /*    perhaps text translated to upper or lower case                    */
    /************************************************************************/

    if( *p == '.' ) p++;                // possible tag end
    while( *p == ' ' ) p++;             // skip initial spaces
    if( *p ) {                          // text exists
        if( layout_work.hx[hx_lvl].cases == case_lower ) {
            strlwr( p );
        } else if( layout_work.hx[hx_lvl].cases == case_upper ) {
            strupr( p );
        }
    }
    rc = add_symvar( &global_dict, htextx, p, no_subscript, 0 );

    update_headnumx( hx_lvl, hnumstr, sizeof( hnumstr ) );

    txtlen = strlen( p );
    headlen = strlen( hnumstr) + txtlen + 2;
    headp = mem_alloc( headlen );
    if( layout_work.hx[hx_lvl].number_form != num_none ) {
        strcpy_s( headp, headlen, hnumstr); // numbered header
        strcat_s( headp, headlen, " " );
    } else {
        *headp = '\0';
    }
    strcat_s( headp, headlen, p );
    rc = add_symvar( &global_dict, headx, headp, no_subscript, 0 );

    if( !id_seen ) {
        id[0] = '\0';                   // zero out if no id given
    }

    /* Only create the entry on the first pass */

    cur_ref = find_refid( hx_ref_dict, id );
    if( pass == 1 ) {
        if( !cur_ref ) {                    // new entry
            hx_re = mem_alloc( sizeof( ref_entry ) );
            init_ref_entry( hx_re, id );
            hx_re->flags = rf_fx;                  // mark as Hx
            add_ref_entry( &hx_ref_dict, hx_re );
            current = strlen( hnumstr );
            if( current > 0 ) {             // prefix will be NULL for level 0 heading
                hx_re->prefix = (char *) mem_alloc( current + 1 );
                strcpy_s(hx_re->prefix, current + 1, hnumstr );
            }
            if( txtlen > 0 ) {              // text line not empty
                hx_re->text_cap = mem_alloc( txtlen + 1 );
                strcpy_s( hx_re->text_cap, txtlen + 1, p );
                hx_re->flags |= rf_textcap; // mark as having caption text
            }
        } else {                // duplicate id
            dup_id_err( cur_ref->id, "heading" );
        }
    } else {
        if( (page + 1) != cur_ref->pageno ) {       // page number changed
            cur_ref->pageno = page;
            init_fwd_ref( hx_fwd_refs, id );
        }
    }

    mem_free( headp );

    if( layout_work.hx[hx_lvl].number_reset ) {
        for( k = hx_lvl + 1; k < 7; k++ ) {
            layout_work.hx[k].headn = 0;// reset following levels
            if( layout_work.hx[k].headnsub != NULL ) {
                *(layout_work.hx[k].headnsub->value) = '\0';
            }
        }
    }

    /***********************************************************************/
    /*  creation of actual heading                                         */
    /***********************************************************************/

    /***********************************************************************/
    /*  eject page(s) if specified                                         */
    /***********************************************************************/

    scr_process_break();                    // commit any prior text 
    if( layout_work.hx[hx_lvl].page_eject != ej_no ) {

        if( ProcFlags.page_started ) {
            do_page_out();
            reset_t_page();
        }

        if( !ProcFlags.start_section ) {
            start_doc_sect();
        }
        set_headx_banners( hx_lvl );        // set possible banners
        reset_t_page();                     // and adjust page margins


        if( (layout_work.hx[hx_lvl].page_eject == ej_odd) && (page & 1) ) {
            do_page_out();              // next page would be even
            reset_t_page();
        } else if( (layout_work.hx[hx_lvl].page_eject == ej_even) && !(page & 1) ) {
            do_page_out();              // next page would be odd
            reset_t_page();
        }
    }

    if( layout_work.hx[hx_lvl].display_heading ) {
        hx_header( hx_lvl, hnumstr, p );
        scr_process_break();                    // commit the header
    }

/// something like this will eventually be needed, but where and how is not yet
/// clear
#if 0
    if( layout_work.hx[hx_lvl].page_eject == ej_no ) {
        insert_col_main( cur_el );
    } else {
        insert_page_width( cur_el );
    }
#endif

    scan_start = scan_stop + 1;
    return;
}

/******************************************************************************/
/*H0, H1, H2, H3, H4, H5, H6                                                  */
/*                                                                            */
/*Format: :Hn [id='id-name']                                                  */
/*            [stitle='character string'].<text line>                         */
/*        (n=0,1)                                                             */
/*                                                                            */
/*Format: :Hn [id='id-name'].<text line>                                      */
/*        (n=0,1,2,3,4,5,6)                                                   */
/*                                                                            */
/*These tags are used to create headings for sections and subsections of text.*/
/*A common convention uses the headings as follows:                           */
/*                                                                            */
/*    :H0 Major part of document.                                             */
/*    :H1 Chapter.                                                            */
/*    :H2 Section.                                                            */
/*    :H3, :H4, :H5, :H6 Subsections.                                         */
/*                                                                            */
/*The specific layout with which a document is formatted will determine the   */
/*format of the headings. Some layouts cause the headings to be automatically */
/*numbered according to a chosen convention. The heading text specified with  */
/*the tag may also be used in the creation of top and/or bottom page banners. */
/*                                                                            */
/*A heading may be used where a basic document element is permitted to appear,*/
/*with the following restrictions:                                            */
/*                                                                            */
/*    1. :h0 tags may only be used in the body of a document.                 */
/*    2. :h1 tags may not be used in the preface or the abstract.             */
/*                                                                            */
/*The stitle attribute allows you to specify a short title for the heading.   */
/*                                                                            */
/*The short title will be used instead of the heading text when creating the  */
/*top and/or bottom page banners. The short title attribute is valid with a   */
/*level one or level zero heading.                                            */
/*                                                                            */
/*The id attribute assigns an identifier name to the heading. The identifier  */
/*name is used when processing a heading reference, and must be unique within */
/*the document.                                                               */
/******************************************************************************/


void gml_h0( const gmltag * entry )
{
    gml_hx_common( entry, 0 );
}

void gml_h1( const gmltag * entry )
{
    gml_hx_common( entry, 1 );
}

void gml_h2( const gmltag * entry )
{
    gml_hx_common( entry, 2 );
}

void gml_h3( const gmltag * entry )
{
    gml_hx_common( entry, 3 );
}

void gml_h4( const gmltag * entry )
{
    gml_hx_common( entry, 4 );
}

void gml_h5( const gmltag * entry )
{
    gml_hx_common( entry, 5 );
}

void gml_h6( const gmltag * entry )
{
    gml_hx_common( entry, 6 );
}

