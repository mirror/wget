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

/* wget_sockaddr is used instead of sockaddr where an IPV6 address
   must fit.  */

typedef union {
	struct sockaddr     sa;   /* Generic but too small */
	struct sockaddr_in  sin;  /* IPv4 socket address */
#ifdef ENABLE_IPV6
	struct sockaddr_in6 sin6; /* IPv6 socket address */
#endif
} wget_sockaddr;

typedef struct {
  unsigned char bytes[4];
} ip4_address;

/* If compiled with IPv6 support, we internally represent all IP
   addresses as IPv6 addresses.  IPv4 addresses are dynamically mapped
   to IPv6, i.e. stored in the format ::ffff:<Ipv4>.  */

#ifdef ENABLE_IPV6
# define MAX_IP_ADDRESS_SIZE 16
#else
# define MAX_IP_ADDRESS_SIZE 4
#endif

typedef struct {
  unsigned char bytes[MAX_IP_ADDRESS_SIZE];
} ip_address;

/* Function declarations */
struct address_list *lookup_host PARAMS ((const char *, int));
char *herrmsg PARAMS ((int));

void address_list_get_bounds PARAMS ((struct address_list *, int *, int *));
void address_list_copy_one PARAMS ((struct address_list *, int,
				    ip_address *));
int address_list_match_all PARAMS ((struct address_list *,
				    struct address_list *));
void address_list_set_faulty PARAMS ((struct address_list *, int));
void address_list_release PARAMS ((struct address_list *));

char *pretty_print_address PARAMS ((ip_address *));

int accept_domain PARAMS ((struct url *));
int sufmatch PARAMS ((const char **, const char *));

void host_cleanup PARAMS ((void));

void wget_sockaddr_set_address PARAMS((wget_sockaddr *, int, 
				       unsigned short, ip_address *));
void wget_sockaddr_set_port PARAMS((wget_sockaddr *, unsigned short));
void *wget_sockaddr_get_addr PARAMS((wget_sockaddr *));
unsigned short wget_sockaddr_get_port PARAMS((const wget_sockaddr *));
socklen_t sockaddr_len PARAMS(());
void map_ipv4_to_ip PARAMS((ip4_address *, ip_address *));
int  map_ip_to_ipv4 PARAMS((ip_address *, ip4_address *));
 
extern	int	ip_default_family;	/* defined in host.c */


#endif /* HOST_H */
