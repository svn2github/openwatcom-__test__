#if defined( _OS2 )
#define BITMAPX(x) BITMAP BITMAP_SPLASH x
#else
#define BITMAPX(x) BITMAP_SPLASH BITMAP x
#endif

#if defined( CSETUP )
BITMAPX( "../res/wcc.bmp" )
#elif defined( JCSETUP )
BITMAPX( "../res/wcc.bmp" )
#elif defined( F77SETUP )
BITMAPX( "../res/f77.bmp" )
#elif defined( JFSETUP )
BITMAPX( "../res/f77.bmp" )
#elif defined( DBSETUP )
BITMAPX( "../res/wsql.bmp" )
#elif defined( JDBSETUP )
BITMAPX( "../res/wsql.bmp" )
#elif defined( SDBSETUP )
BITMAPX( "../res/sqlserv.bmp" )
#else
BITMAPX( "../res/generic.bmp" )
#endif
