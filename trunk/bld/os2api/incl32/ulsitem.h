/*
    ULS locale items
*/

#ifndef _ULS_ITEM
#define _ULS_ITEM

#ifdef __cplusplus
extern "C" {
#endif

#define LOCI_sDateTime          1
#define LOCI_sShortDate         2
#define LOCI_sTimeFormat        3
#define LOCI_s1159              4
#define LOCI_s2359              5
#define LOCI_sAbbrevDayName7    6
#define LOCI_sAbbrevDayName1    7
#define LOCI_sAbbrevDayName2    8
#define LOCI_sAbbrevDayName3    9
#define LOCI_sAbbrevDayName4    10
#define LOCI_sAbbrevDayName5    11
#define LOCI_sAbbrevDayName6    12
#define LOCI_sDayName7          13
#define LOCI_sDayName1          14
#define LOCI_sDayName2          15
#define LOCI_sDayName3          16
#define LOCI_sDayName4          17
#define LOCI_sDayName5          18
#define LOCI_sDayName6          19
#define LOCI_sAbbrevMonthName1  20
#define LOCI_sAbbrevMonthName2  21
#define LOCI_sAbbrevMonthName3  22
#define LOCI_sAbbrevMonthName4  23
#define LOCI_sAbbrevMonthName5  24
#define LOCI_sAbbrevMonthName6  25
#define LOCI_sAbbrevMonthName7  26
#define LOCI_sAbbrevMonthName8  27
#define LOCI_sAbbrevMonthName9  28
#define LOCI_sAbbrevMonthName10 29
#define LOCI_sAbbrevMonthName11 30
#define LOCI_sAbbrevMonthName12 31
#define LOCI_sMonthName1        32
#define LOCI_sMonthName2        33
#define LOCI_sMonthName3        34
#define LOCI_sMonthName4        35
#define LOCI_sMonthName5        36
#define LOCI_sMonthName6        37
#define LOCI_sMonthName7        38
#define LOCI_sMonthName8        39
#define LOCI_sMonthName9        40
#define LOCI_sMonthName10       41
#define LOCI_sMonthName11       42
#define LOCI_sMonthName12       43
#define LOCI_sDecimal           44
#define LOCI_sThousand          45
#define LOCI_sYesString         46
#define LOCI_sNoString          47
#define LOCI_sCurrency          48
#define LOCI_sCodeSet           49
#define LOCI_xLocaleToken       50
#define LOCI_xWinLocale         51
#define LOCI_iLocaleResnum      52
#define LOCI_sNativeDigits      53
#define LOCI_iMaxItem           54
#define LOCI_sTimeMark          55
#define LOCI_sEra               56
#define LOCI_sAltShortDate      57
#define LOCI_sAltDateTime       58
#define LOCI_sAltTimeFormat     59
#define LOCI_sAltDigits         60
#define LOCI_sYesExpr           61
#define LOCI_sNoExpr            62
#define LOCI_sDate              63
#define LOCI_sTime              64
#define LOCI_sList              65
#define LOCI_sMonDecimalSep     66
#define LOCI_sMonThousandSep    67
#define LOCI_sGrouping          68
#define LOCI_sMonGrouping       69
#define LOCI_iMeasure           70
#define LOCI_iPaper             71
#define LOCI_iDigits            72
#define LOCI_iTime              73
#define LOCI_iDate              74
#define LOCI_iCurrency          75
#define LOCI_iCurrDigits        76
#define LOCI_iLzero             77
#define LOCI_iNegNumber         78
#define LOCI_iLDate             79
#define LOCI_iCalendarType      80
#define LOCI_iFirstDayOfWeek    81
#define LOCI_iFirstWeekOfYear   82
#define LOCI_iNegCurr           83
#define LOCI_iTLzero            84
#define LOCI_iTimePrefix        85
#define LOCI_iOptionalCalendar  86
#define LOCI_sIntlSymbol        87
#define LOCI_sAbbrevLangName    88
#define LOCI_sCollate           89
#define LOCI_iUpperType         90
#define LOCI_iUpperMissing      91
#define LOCI_sPositiveSign      92
#define LOCI_sNegativeSign      93
#define LOCI_sLeftNegative      94
#define LOCI_sRightNegative     95
#define LOCI_sLongDate          96
#define LOCI_sAltLongDate       97
#define LOCI_sMonthName13       98
#define LOCI_sAbbrevMonthName13 99
#define LOCI_sName              100
#define LOCI_sLanguageID        101
#define LOCI_sCountryID         102
#define LOCI_sEngLanguage       103
#define LOCI_sLanguage          104
#define LOCI_sEngCountry        105
#define LOCI_sCountry           106
#define LOCI_sNativeCtryName    107
#define LOCI_iCountry           108
#define LOCI_sISOCodepage       109
#define LOCI_iAnsiCodepage      110
#define LOCI_iCodepage          111
#define LOCI_iAltCodepage       112
#define LOCI_iMacCodepage       113
#define LOCI_iEbcdicCodepage    114                           */
#define LOCI_sOtherCodepages    115
#define LOCI_sSetCodepage       116
#define LOCI_sKeyboard          117
#define LOCI_sAltKeyboard       118
#define LOCI_sSetKeyboard       119
#define LOCI_sDebit             120
#define LOCI_sCredit            121
#define LOCI_sLatin1Locale      122
#define LOCI_wTimeFormat        123
#define LOCI_wShortDate         124
#define LOCI_wLongDate          125
#define LOCI_jISO3CountryName   126
#define LOCI_jPercentPattern    127
#define LOCI_jPercentSign       128
#define LOCI_jExponent          129
#define LOCI_jFullTimeFormat    130
#define LOCI_jLongTimeFormat    131
#define LOCI_jShortTimeFormat   132
#define LOCI_jFullDateFormat    133
#define LOCI_jMediumDateFormat  134
#define LOCI_jDateTimePattern   135
#define LOCI_jEraStrings        136

#define LOCI_MAXITEM            136
#define LOCI_NOUSEROVERRIDE  0x8000

typedef int LocaleItem;

#ifdef __cplusplus
}
#endif

#endif
