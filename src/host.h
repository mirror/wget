/* Declarations for host.c
   Copyright (C) 1995, 1996, 1997, 2001 Free Software Foundation, Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

GNU Wget is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

In addition, as a special exception, the Free Software Foundation
gives permission to link the code of its release of Wget with the
OpenSSL project's "OpenSSL" library (or with modified versions of it
that use the same license as the "OpenSSL" library), and distribute
the linked executables.  You must obey the GNU General Public License
in all respects for all of the code used other than "OpenSSL".  If you
modify this file, you may extend this exception to your version of the
file, but you are not obligated to do so.  If you do not wish to do
so, delete this exception statement from your version.  */

#ifndef HOST_H
#define HOST_H

#ifdef WINDOWS
# include <winsock.h>
#else
# include <netdb.h>
# include <sys/socket.h>
# include <netinet/in.h>
#ifndef __BEOS__
# include <arpa/inet.h>
#endif
#endif

struct url;
struct address_list;

extern int ip_default_family;	/* defined in host.c */

typedef struct {
  enum { 
    IPv4_ADDRESS, 
#ifdef ENABLE_IPV6
    IPv6_ADDRESS 
#endif /* ENABLE_IPV6 */
  } type;
  union {
#ifdef ENABLE_IPV6
    struct {
      struct in6_addr addr;
#ifdef HAVE_SOCKADDR_IN6_SCOPE_ID
      unsigned int scope_id;
#endif /* HAVE_SOCKADDR_IN6_SCOPE_ID */
    } ipv6;
#endif /* ENABLE_IPV6 */
    struct {
      struct in_addr addr;
    } ipv4;
  } addr;
} ip_address;

#ifndef ENABLE_IPV6

#ifndef HAVE_SOCKADDR_STORAGE
#define sockaddr_storage sockaddr_in
#endif

#endif /* ENABLE_IPV6 */

/* Flags for lookup_host */
#define LH_SILENT    0x0001
#define LH_PASSIVE   0x0002
#define LH_IPv4_ONLY 0x0004
#ifdef ENABLE_IPV6
#define LH_IPv6_ONLY 0x0008
#endif /* ENABLE_IPV6 */

/* Function declarations */
struct address_list *lookup_host PARAMS ((const char *, int));
char *herrmsg PARAMS ((int));

void address_list_get_bounds PARAMS ((const struct address_list *,
				      int *, int *));
void address_list_copy_one PARAMS ((const struct address_list *, int,
				    ip_address *));
int address_list_match_all PARAMS ((const struct address_list *,
				    const struct address_list *));
void address_list_set_faulty PARAMS ((struct address_list *, int));
void address_list_release PARAMS ((struct address_list *));

const char *pretty_print_address PARAMS ((const ip_address *));

int accept_domain PARAMS ((struct url *));
int sufmatch PARAMS ((const char **, const char *));

void sockaddr_set_address PARAMS ((struct sockaddr *, unsigned short,
				   const ip_address *));
void sockaddr_get_address PARAMS ((const struct sockaddr *, unsigned short *,
				   ip_address *));
unsigned short sockaddr_get_port PARAMS ((const struct sockaddr *));
socklen_t sockaddr_len PARAMS ((const struct sockaddr *sa));

void host_cleanup PARAMS ((void));

#endif /* HOST_H */
