# Explicit syntax-check exceptions.
exclude_file_name_regexp--sc_trailing_blank = ^doc/annou.*$$
exclude_file_name_regexp--sc_bindtextdomain = ^fuzz/.*.c$$
exclude_file_name_regexp--sc_require_config_h = (fuzz/.*.c|src/decc_ver.c|util/trunc.c)$$
exclude_file_name_regexp--sc_require_config_h_first = (fuzz/.*.c|src/decc_ver.c|src/vms.c|util/trunc.c)$$
exclude_file_name_regexp--sc_file_system = ^(NEWS|testenv/server/ftp/ftp_server.py)$$


export VC_LIST_EXCEPT_DEFAULT=^(lib/.*|m4/.*|md5/.*|build-aux/.*|src/gettext\.h|.*ChangeLog|tests/certs/.*)$$
config_h_header = "wget\.h"

local-checks-to-skip = \
    sc_const_long_option \
    sc_error_message_uppercase \
    sc_two_space_separator_in_usage \
    sc_useless_cpp_parens \
    \
    sc_prohibit_atoi_atof \
    sc_prohibit_strcmp \
    \
    sc_makefile_at_at_check \
    sc_cast_of_argument_to_free \
    sc_prohibit_gnu_make_extensions \
	\
	sc_indent

#SHELL=bash -x
show-vc-list-except:
	@$(VC_LIST_EXCEPT)

VC_LIST_ALWAYS_EXCLUDE_REGEX = ^ABOUT-NLS|((msdos|vms)/.*)|ChangeLog-2014-12-10|/.*\.der|^tests/certs/.*|^fuzz/.*\.(in|repro)/.*$$

update-copyright-env = UPDATE_COPYRIGHT_USE_INTERVALS=1
generated_files =

old_NEWS_hash = 5ad1696f7a50ffcd3aa268056a29a3ec
manual_title = $(VERSION)
