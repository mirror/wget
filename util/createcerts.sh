#!/bin/bash

# Option handling is based on http://mywiki.wooledge.org/BashFAQ/035
# Tested on Ubuntu 16.04 (using bash)

testhostname="WgetTestingServer";
verbose=0 # Variables to be evaluated as shell arithmetic should be initialized to a default or validated beforehand.
cmd_openssl="";
CERTSDIR="../tests/certs/";
tmpfilelist="";

function finish {
	/bin/rm -f ${tmpfilelist};
	echo "done";
}

trap finish EXIT;

function show_usage {
	echo -e "$0 [options]\n";
	echo -e "Options:";
	echo -e "\t-h\tPrint this message";
	echo -e "\t-a\tRegenerate all certs & keys for testing";
	echo -e "\t-l\tRegenerate self-signed cert & key";
	echo -e "\t-s\tRegenerate server cert & key";
	echo -e "\t-c\tRegenerate client cert & key";
	echo -e "\t-e\tRegenerate expired cert";
	echo -e "\t-i\tRegenerate invalid cert";
	echo -e "\t-o\tRegenerate Root CA cert & key";
	echo -e "\t-w\tRegenerate IntermediateCA cert";
	echo -e "\t-r\tRegenerate cert & CRL for cert";

	return 0;
}

function check_prereqs {
	# Check if OpenSSL is available
	command -v openssl 2>/dev/null 1>&2 || { echo >&2 "Need OpenSSL to continue.  Aborting.";
											 exit 1; }
	cmd_openssl=`command -v openssl`;
	echo "Using ${cmd_openssl}";
	return 0;
}

function init_conf_file {
	local conffile=$1;
	local cacrt=$2;
	local cakey=$3;
	local crtindex=$4;
	local crtserial=$5;
	local crlnumber=$6;
	cat >${conffile}  <<EndOfCAConf
[ ca ]
default_ca = myca

[ crl_ext ]
issuerAltName=issuer:copy
authorityKeyIdentifier=keyid:always

 [ myca ]
 dir = ${CERTSDIR}
 new_certs_dir = ./
 unique_subject = no
 certificate = \$dir/${cacrt}
 database = ${crtindex}
 private_key = \$dir/${cakey}
 serial = ${crtserial}
 default_days = 730
 default_md = sha1
 policy = myca_policy
 x509_extensions = myca_extensions
 crlnumber = ${crlnumber}
 default_crl_days = 730

 [ myca_policy ]
 commonName = supplied
 stateOrProvinceName = supplied
 countryName = optional
 emailAddress = optional
 organizationName = supplied
 organizationalUnitName = optional

 [ myca_extensions ]
 basicConstraints = critical,CA:TRUE
 keyUsage = critical,any
 subjectKeyIdentifier = hash
 authorityKeyIdentifier = keyid:always,issuer
 keyUsage = digitalSignature,keyEncipherment,cRLSign,keyCertSign
 extendedKeyUsage = serverAuth
 crlDistributionPoints = @crl_section
 subjectAltName  = @alt_names
 authorityInfoAccess = @ocsp_section

 [ v3_ca ]
 basicConstraints = critical,CA:TRUE,pathlen:0
 keyUsage = critical,any
 subjectKeyIdentifier = hash
 authorityKeyIdentifier = keyid:always,issuer
 keyUsage = digitalSignature,keyEncipherment,cRLSign,keyCertSign
 extendedKeyUsage = serverAuth
 crlDistributionPoints = @crl_section
 subjectAltName  = @alt_names
 authorityInfoAccess = @ocsp_section

 [alt_names]
 DNS.0 = WgetTestingServer

 [crl_section]
 URI.0 = http://test.wgettest.org/Bogus.crl
 URI.1 = http://test.wgettest.org/Bogus.crl

 [ocsp_section]
 caIssuers;URI.0 = http://test.wgettest.com/Bogus.crt
 caIssuers;URI.1 = http://test.wgettest.com/Bogus.crt
 OCSP;URI.0 = http://test.wgettest.com/ocsp/
 OCSP;URI.1 = http://test.wgettest.com/ocsp/

EndOfCAConf
}

function init_ca {
	init_conf_file "rootca.conf" "test-ca-cert.pem" "test-ca-key.pem" "certindex" "certserial" "crlnumber";
	init_conf_file "interca.conf" "interca.crt" "interca.key" "icertindex" "icertserial" "icrlnumber";
	tmpfilelist="${tmpfilelist} ./rootca.conf ./interca.conf";
	/usr/bin/touch certindex  crlnumber;
	/usr/bin/touch icertindex icrlnumber;
	echo "00">crlnumber;
	echo "00">icrlnumber;
	echo "01">certserial;
	echo "01">icertserial;
	tmpfilelist="${tmpfilelist} certindex*  crlnumber*";
	tmpfilelist="${tmpfilelist} icertindex* icrlnumber*";
	tmpfilelist="${tmpfilelist} certserial* icertserial*";
	for i in {1..10}
	do
		tmpfilelist="${tmpfilelist} 0$i.pem";
	done
}

function is_cert_key_ok {
	local certfile=$1;
	local keyfile=$2;
	local check_res=0;

	if ! [ -f $certfile ] && [ -s $certfile ]; then
		echo "Invalid cert $certfile\n";
		exit 1;
	fi
	if ! [ -f $keyfile ] && [ -s $keyfile ]; then
		echo "Invalid key $keyfile\n";
		exit 1;
	fi
	check_res=`(openssl x509 -noout -modulus -in $certfile | openssl md5 ;
			  openssl rsa  -noout -modulus -in $keyfile | openssl md5) |
			  uniq|wc -l`;
	if [ ${check_res} -ne 1 ]; then
		echo "Private key and certfile doesn't match\n";
		exit 1;
	fi

	return 0;
}

function generate_key {
	local keyfile=$1;

	local key_cmd="${cmd_openssl} genrsa -out ${keyfile} 4096";

	eval ${key_cmd} 2>/dev/null;
	if [ $? -ne 0 ]; then
		echo "Failed to generate key pair\n";
		return 1;
	fi

	return 0;
}

function generate_csr {
	local keyfile=$1;
	local csrfile=$2;
	local crttype=$3;
	local subj111="/C=US/ST=CA/L=Mystery Spot/O=Dis/CN=${testhostname}/";
	local subj112="emailAddress=${crttype}";
	local crtsubj=${subj111}${subj112};
	local csr_cmd="${cmd_openssl} req -new -key ${keyfile} -out ${csrfile} -subj \"${crtsubj}\""

	eval ${csr_cmd} 2>/dev/null;
	if [ $? -ne 0 ]; then
		echo "Failed to generate CSR\n";
		return 1;
	fi

	return 0;
}

function sign_cert {
	local csrfile=$1;
	local crtfile=$2;
	local catype=$3;
	local xopts=${4-'-days 365'};

	local caconf;
	if [ "$catype"x = "ROOT"x ]; then
		caconf="./rootca.conf";
	elif [ "$catype"x = "INTER"x ]; then
		caconf="./interca.conf";
	else
		exit 1;
	fi
	local crt_cmd="${cmd_openssl} ca -config ${caconf} -in ${csrfile} -out ${crtfile} -batch ${xopts}";

	eval ${crt_cmd} 2>/dev/null;
	if [ $? -ne 0 ]; then
		echo "Failed to create certificate from ${csrfile}";
		return 1;
	fi

	return 0;
}

function generate_crl {
	local crtfile=$1;
	local crlfile=$2

	local rootcrt="${CERTSDIR}/test-ca-cert.pem";
	local rootkey="${CERTSDIR}/test-ca-key.pem";
	local caconf="./rootca.conf";

	local crt_cmd="${cmd_openssl} ca -config ${caconf} -revoke ${crtfile}";
	eval ${crt_cmd} 2>/dev/null;
	if [ $? -ne 0 ]; then
		echo "Failed to Revoke certificate";
		return 1;
	fi

	local crl_cmd="${cmd_openssl} ca -config ${caconf} -gencrl -keyfile ${rootkey} -cert ${rootcrt} -out ${crlfile}";
	eval ${crl_cmd} 2>/dev/null;
	if [ $? -ne 0 ]; then
		echo "Failed to create CRL";
		return 1;
	fi

	return 0;
}

function generate_self_signed {
	local keyfile=$1;
	local crtfile=$2;
	local defsubj1="/C=US/ST=CA/L=Mystery Spot/O=Dis/CN=${testhostname}/";
	local defsubj2="emailAddress=tester";
	local subj1=${3-${defsubj1}};
	local subj2=${4-${defsubj2}};
	local ss_certsubj="${subj1}${subj2}";

	local cmd1="${cmd_openssl} req -x509 -nodes -newkey rsa:4096 -keyout";
	local cmd2=" ${keyfile} -out ${crtfile} -days 365 -subj";
	local ss_cmd="${cmd1}${cmd2} \"${ss_certsubj}\"";

	eval "${ss_cmd}" 2>/dev/null;
	if [ $? -ne 0 ]; then
		echo "Failed to run self signing openssl command";
		return 1;
	fi

	is_cert_key_ok ${crtfile} ${keyfile};

	return 0;
}

# Re-generate self-signed cert & key for testing
function create_self_signed {
	local keyfile="${CERTSDIR}/selfsigned.key";
	local crtfile="${CERTSDIR}/selfsigned.crt";

	generate_self_signed ${keyfile} ${crtfile};

	return 0;
}

# Re-generate server cert
function create_server_cert {
	local keyfile="${CERTSDIR}/server.key";
	local csrfile="${CERTSDIR}/server.csr";
	local crtfile="${CERTSDIR}/server.crt";

	tmpfilelist="${tmpfilelist} ${csrfile}";
	generate_key ${keyfile};
	generate_csr ${keyfile} ${csrfile} "ServerTester";
	sign_cert ${csrfile} ${crtfile} "ROOT";

	is_cert_key_ok ${crtfile} ${keyfile};

	return 0;
}

# Re-generate expired cert
function create_expired_cert {
	local keyfile="${CERTSDIR}/expired.key";
	local csrfile="${CERTSDIR}/expired.csr";
	local crtfile="${CERTSDIR}/expired.crt";

	tmpfilelist="${tmpfilelist} ${csrfile}";
	generate_key ${keyfile};
	generate_csr ${keyfile} ${csrfile} "ExpiredTester";
	sign_cert ${csrfile} ${crtfile} "ROOT" "-enddate 170508160342Z";

	is_cert_key_ok ${crtfile} ${keyfile};

	return 0;
}

# Re-generate invalid cert
function create_invalid_cert {
	local keyfile="${CERTSDIR}/invalid.key";
	local csrfile="${CERTSDIR}/invalid.csr";
	local crtfile="${CERTSDIR}/invalid.crt";

	tmpfilelist="${tmpfilelist} ${csrfile}";
	local sdate=`date +%y%m%d%H%M%SZ --date=tomorrow`;
	generate_key ${keyfile};
	generate_csr ${keyfile} ${csrfile} "ServerTester";
	sign_cert ${csrfile} ${crtfile} "ROOT" "-startdate ${sdate}";

	is_cert_key_ok ${crtfile} ${keyfile};

	return 0;
}

# Re-generate client cert
function create_client_cert {
	local keyfile="${CERTSDIR}/client.key";
	local csrfile="${CERTSDIR}/client.csr";
	local crtfile="${CERTSDIR}/client.crt";

	tmpfilelist="${tmpfilelist} ${csrfile}";
	generate_key ${keyfile};
	generate_csr ${keyfile} ${csrfile} "ClientTester";
	sign_cert ${csrfile} ${crtfile} "ROOT";

	is_cert_key_ok ${crtfile} ${keyfile};

	return 0;
}

# Re-generate interca+rootca combo
function create_wot_cert {
	local ikeyfile="${CERTSDIR}/interca.key";
	local icsrfile="${CERTSDIR}/interca.csr";
	local icrtfile="${CERTSDIR}/interca.crt";
	local keyfile="${CERTSDIR}/user.key";
	local csrfile="${CERTSDIR}/user.csr";
	local crtfile="${CERTSDIR}/user.crt";

	tmpfilelist="${tmpfilelist} ${icsrfile}";
	generate_key ${ikeyfile};
	generate_csr ${ikeyfile} ${icsrfile} "IntermediateCA";
	sign_cert ${icsrfile} ${icrtfile} "ROOT";

	is_cert_key_ok ${icrtfile} ${ikeyfile};

	tmpfilelist="${tmpfilelist} ${csrfile}";
	generate_key ${keyfile};
	generate_csr ${keyfile} ${csrfile} "UserOfIntermidate";
	sign_cert ${csrfile} ${crtfile} "INTER";

	is_cert_key_ok ${crtfile} ${keyfile};

	/bin/cat "${CERTSDIR}/test-ca-cert.pem">"${CERTSDIR}/wotca.pem";
	/bin/cat ${icrtfile}>>"${CERTSDIR}/wotca.pem";

	return 0;
}

# Re-generate CRL
function create_revoked_cert {
	local keyfile="${CERTSDIR}/revoked.key";
	local csrfile="${CERTSDIR}/revoked.csr";
	local crtfile="${CERTSDIR}/revoked.crt";
	local crlfile="${CERTSDIR}/revokedcrl.pem";

	tmpfilelist="${tmpfilelist} ${csrfile}";
	generate_key ${keyfile};
	generate_csr ${keyfile} ${csrfile} "RevokedTester";
	sign_cert ${csrfile} ${crtfile} "ROOT";

	is_cert_key_ok ${crtfile} ${keyfile};

	generate_crl ${crtfile} ${crlfile};

	return 0;
}

# Re-generate RootCA
function create_root_ca {
	local keyfile="${CERTSDIR}/test-ca-key.pem";
	local crtfile="${CERTSDIR}/test-ca-cert.pem";
	local rcasubj1="/C=US/ST=CA/L=San Jose/O=Wget Testing Department/OU=Testing/CN=WgetTesting/";
	local rcasubj2="emailAddress=bugs-wget@gnu.org";

	generate_self_signed ${keyfile} ${crtfile} "${rcasubj1}" "${rcasubj2}";

	return 0;
}

# Regenerate all of the certs used in wget tests
function regenerate_all_certs {
	create_root_ca;
	create_self_signed;
	create_server_cert;
	create_client_cert;
	create_expired_cert;
	create_invalid_cert;
	create_revoked_cert;
	create_wot_cert;

	return 0;
}

# Begin script
init_ca;
check_prereqs;
# Hand-rolled getopts. Note:
# If there is input that follow the options, they
# will remain in the "$@" positional parameters.
while :; do
	case $1 in
	-h|-\?|--help)
		show_usage;
		exit 0;
		;;

	-a|--all)     # Re-generate all certs & keys for testing
		regenerate_all_certs;
		;;

	-l|--self)    # Re-generate self-signed cert & key for testing
		create_self_signed;
		;;

	-e|--expired) # Re-generate expired cert
		create_expired_cert;
		;;

	-i|--invalid) # Re-generate cert that is not valid yet
		create_invalid_cert;
		;;

	-r|--revoked) # Re-generate revoked cert
		create_revoked_cert;
		;;

	-c|--client)  # Re-generate client cert
		create_client_cert;
		;;

	-w|--wot)     # Re-generate interca+rootca combo
		create_wot_cert;
		;;

	-o|--root)    # Re-generate root cert
		create_root_ca;
		;;

	-s|--server)  # Re-generate server cert
		create_server_cert;
		;;

	--)           # End of all options.
		shift
		break
		;;

	-?*)
		printf 'WARN: Unknown option (ignored): %s\n' "$1" >&2
		;;

	*)
		break
	esac

   shift
done
