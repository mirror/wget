Summary: A command-line client to download WWW/FTP documents with optional recursion.
Name: wget
%define version 1.4.5
Version: %{version}
Release: 3
Source: ftp://prep.ai.mit.edu/pub/gnu/wget-1.4.5.tar.gz
Group: Applications/Networking
Copyright: GPL
Buildroot: /var/tmp/wget-root
Packager: Jeff Johnson <jbj@jbj.org>

%description
GNU Wget is a freely available network utility to retrieve files from
the World Wide Web, using HTTP (Hyper Text Transfer Protocol) and
FTP (File Transfer Protocol), the two most widely used Internet
protocols.

%prep
%setup

%build
./configure --prefix=/usr --sysconfdir=/etc
make

%install
rm -rf $RPM_BUILD_ROOT

make prefix=$RPM_BUILD_ROOT/usr sysconfdir=$RPM_BUILD_ROOT/etc INSTALL_PROGRAM="install -s" install

gzip -9nf $RPM_BUILD_ROOT/usr/info/wget*

%post

/sbin/install-info /usr/info/wget.info.gz /usr/info/dir --entry="* wget: (wget).          GNU Wget Manual."

%preun

if [ $1 = 0 ]; then
	/sbin/install-info --delete /usr/info/wget.info.gz /usr/info/dir --entry="* wget: (wget).          GNU Wget Manual."
fi

%clean
rm -rf $RPM_BUILD_ROOT

%files
%doc README NEWS AUTHORS COPYING INSTALL MACHINES MAILING-LIST
/usr/bin/wget
/etc/wgetrc
/usr/info/wget*
/usr/man/man1/wget.1

%changelog

* Thu Feb 26 1998 Jeff Johnson <jbj@jbj.org>

- Simplify previous contrib version.

