#include <stdio.h>

int main( void)
{
#ifdef __VMS_VERSION
printf( " __VMS_VERSION: >%s<.\n", __VMS_VERSION);
#else /* def __VMS_VERSION */
printf( " __VMS_VERSION: (undefined)<.\n");
#endif /* def __VMS_VERSION [else] */

#ifdef __VMS_VER
printf( " __VMS_VER  = %d.\n", __VMS_VER);
#else /* def __VMS_VER */
printf( " __VMS_VER  = (undefined).\n");
#endif /* def __VMS_VER [else] */

#ifdef __DECC_VER
printf( " __DECC_VER = %d.\n", __DECC_VER);
#else /* def __DECC_VER */
printf( " __DECC_VER = (undefined).\n");
#endif /* def __DECC_VER */

#ifdef __CRTL_VER
printf( " __CRTL_VER = %d.\n", __CRTL_VER);
#else /* def __CRTL_VER */
printf( " __CRTL_VER = (undefined).\n");
#endif /* def __CRTL_VER */

return 0;
}
