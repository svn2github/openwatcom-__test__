.*
.*
.dirctv OUTPUT
.*
.np
The "OUTPUT" directive overrides the normal operating system specific
executable format and creates either a raw binary image or an Intel Hex file.
 The format of the "OUTPUT" directive (short form "OUT") is as follows.
.mbigbox
    OUTPUT RAW|HEX [OFFSET=n][HSHIFT=n]
.embigbox
.synote
.*
.im lnkvalue
.*
.mnote RAW
specifies the output file to be a raw binary and will contain an absolute
image of the executable's code and data. Default file extension is ".bin".
.*
.mnote HEX
specifies the output file to contain a representation of the absolute image
of the code and data using the Intel standard hex file format. Default file
extension is ".hex".
.*
.mnote OFFSET=n
(short form "OFF") specifies that the linear address
.sy n
should be subtracted from all addresses being output to the executable image.
.*
.mnote HSHIFT
defines the relationship between segment values for type 02 records and
linear addresses. The value
.sy n
is the number of digits to right shift a 32-bit value containing a segment
address in its upper 16 bits in order to convert it to part of a linear
address. In more conventional terms, (16 -
.sy n
) is the amount to shift a segment value left in order to convert it to
part of a linear address.
.esynote
.*
.*
For raw binary files, the position in the file is the linear address after
the offset is subtracted from it. Any gaps filled with the value specified
through "OPTION FILLCHAR" (default is 0).
.np
For hex files, the linear address (after subtracting the offset) is used to
determine the output record generated. Records contain 16 bytes, unless a 
gap occurs prior to that in which case the record is shorter, and a new 
record starts after the gap. There are three types of Intel Hex records. The
oldest and most widely used is HEX80, which can only deal with 16-bit
addresses. For many ROM-based applications, this is enough, especially once
an offset has been subtracted. For maximum versatility, all addresses less
than 65536 are generated in this form.
.np
The HEX86 standard creates a segmentation that mirrors the CPU segmentation.
Type 02 records define the segment, and all subsequent addresses are based
on that segment value. For addresses above 64K, This form is used.
A program that understands HEX86 should assume the segment value is zero
until an 02 record is encountered. This preserves backward compatibility
with HEX80, and allows the automatic selection algorithm used in &lnkname
to work properly.
.np
Type 02 records are assumed to have segment values that, when shifted left
four bits, form a linear address. However, this is not suitable for 24-bit
segmented addressing schemes. Therefore, &lnkname uses the value specified
through "OPTION HSHIFT" to determine the relationship between segments and
offsets. This approach can work with any 16:16 segmented architecture
regardless of the segment alignment. The default shift value is 12,
representing the conventional 8086 architecture. This is not to be confused
with the optional "OUTPUT HSHIFT" value discussed below.
.np
Of course, PROM programmers or third-party tools probably were
.us not
designed to work with unconventional shift values, hence for cases where code
for a 24-bit (or other non-standard) target needs to be programmed into a
PROM or processed by a third-party tool, the "OUTPUT HSHIFT" option can be
used to override the "OPTION HSHIFT" value.  This would usually be of the
form "OUTPUT HSHIFT=12" to restore the industry standard setting. The
default for "OUTPUT HSHIFT" is to follow "OPTION HSHIFT". When neither is
specified, the default "OPTION HSHIFT" value of 12 applies, providing
industry standard compliance.
.np
If the address exceeds the range of type 02 records (1 MB for HSHIFT=12 and
16 MB for HSHIFT=8), type 04 extended linear records are generated, again
ensuring seamless compatibility and migration to large file sizes.
