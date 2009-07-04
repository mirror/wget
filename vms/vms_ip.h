/*    VMS-specific "#include" directives for IP. */

#ifdef MULTINET

#include "multinet_root:[multinet.include.sys]types.h"
#include "multinet_root:[multinet.include]errno.h"
#include "multinet_root:[multinet.include]netdb.h"

#else /* MULTINET */

#include <sys/types.h>
#include <errno.h>
#include <netdb.h>

#if __CRTL_VER < 70000000
#define h_errno errno  /* Quiets the compiler, but probably ineffective. */
#endif /* __CRTL_VER < 70000000 */

#endif /* MULTINET */
