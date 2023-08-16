AM_CPPFLAGS = -I $(top_srcdir)/include -I $(top_srcdir) -I $(srcdir)/standalone/include
 
# May be used by toolexeclibdir.
gcc_version := $(shell @get_gcc_base_ver@ $(top_srcdir)/../gcc/BASE-VER)

DEFS = -D_GNU_SOURCE -D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -DASAN_HAS_EXCEPTIONS=1 -DASAN_NEEDS_SEGV=1 -DCAN_SANITIZE_UB=0 -DASAN_HAS_CXA_RETHROW_PRIMARY_EXCEPTION=0 -DGWP_ASAN_HOOKS
if USING_MAC_INTERPOSE
DEFS += -DMAC_INTERPOSE_FUNCTIONS -DMISSING_BLOCKS_SUPPORT
endif
AM_CXXFLAGS = -Wall -W -Wno-unused-parameter -Wwrite-strings -pedantic -Wno-long-long  -fPIC -fno-builtin -fno-exceptions -fno-rtti -fomit-frame-pointer -funwind-tables -fvisibility=hidden -Wno-variadic-macros -fno-ipa-icf
AM_CXXFLAGS += $(LIBSTDCXX_RAW_CXX_CXXFLAGS)
AM_CXXFLAGS += -std=gnu++14
AM_CXXFLAGS += $(EXTRA_CXXFLAGS)
AM_CCASFLAGS = $(EXTRA_ASFLAGS)
ACLOCAL_AMFLAGS = -I $(top_srcdir) -I $(top_srcdir)/config

toolexeclib_LTLIBRARIES = libscudo.la

scudo_files = \
	standalone/checksum.cpp \
	standalone/flags_parser.cpp \
	standalone/mem_map_fuchsia.cpp \
	standalone/rss_limit_checker.cpp \
	standalone/wrappers_c_bionic.cpp \
	standalone/common.cpp \
	standalone/fuchsia.cpp \
	standalone/mem_map_linux.cpp \
	standalone/string_utils.cpp \
	standalone/wrappers_c.cpp \
	standalone/crc32_hw.cpp \
	standalone/linux.cpp \
	standalone/release.cpp \
	standalone/timing.cpp \
	standalone/wrappers_cpp.cpp \
	standalone/flags.cpp \
	standalone/mem_map.cpp \
	standalone/report.cpp \
	standalone/trusty.cpp

libscudo_la_SOURCES = $(scudo_files)
libscudo_la_LIBADD = $(top_builddir)/sanitizer_common/libsanitizer_common.la $(top_builddir)/gwp_asan/libgwp_asan.a
libscudo_la_LIBADD += $(LIBSTDCXX_RAW_CXX_LDFLAGS)

libscudo_la_LDFLAGS = -version-info `grep -v '^\#' $(srcdir)/libtool-version` $(link_libscudo)

# Work around what appears to be a GNU make bug handling MAKEFLAGS
# values defined in terms of make variables, as is the case for CC and
# friends when we are called from the top level Makefile.
AM_MAKEFLAGS = \
	"AR_FLAGS=$(AR_FLAGS)" \
	"CC_FOR_BUILD=$(CC_FOR_BUILD)" \
	"CFLAGS=$(CFLAGS)" \
	"CXXFLAGS=$(CXXFLAGS)" \
	"CFLAGS_FOR_BUILD=$(CFLAGS_FOR_BUILD)" \
	"CFLAGS_FOR_TARGET=$(CFLAGS_FOR_TARGET)" \
	"INSTALL=$(INSTALL)" \
	"INSTALL_DATA=$(INSTALL_DATA)" \
	"INSTALL_PROGRAM=$(INSTALL_PROGRAM)" \
	"INSTALL_SCRIPT=$(INSTALL_SCRIPT)" \
	"JC1FLAGS=$(JC1FLAGS)" \
	"LDFLAGS=$(LDFLAGS)" \
	"LIBCFLAGS=$(LIBCFLAGS)" \
	"LIBCFLAGS_FOR_TARGET=$(LIBCFLAGS_FOR_TARGET)" \
	"MAKE=$(MAKE)" \
	"MAKEINFO=$(MAKEINFO) $(MAKEINFOFLAGS)" \
	"PICFLAG=$(PICFLAG)" \
	"PICFLAG_FOR_TARGET=$(PICFLAG_FOR_TARGET)" \
	"SHELL=$(SHELL)" \
	"RUNTESTFLAGS=$(RUNTESTFLAGS)" \
	"exec_prefix=$(exec_prefix)" \
	"infodir=$(infodir)" \
	"libdir=$(libdir)" \
	"prefix=$(prefix)" \
	"includedir=$(includedir)" \
	"AR=$(AR)" \
	"AS=$(AS)" \
	"LD=$(LD)" \
	"LIBCFLAGS=$(LIBCFLAGS)" \
	"NM=$(NM)" \
	"PICFLAG=$(PICFLAG)" \
	"RANLIB=$(RANLIB)" \
	"DESTDIR=$(DESTDIR)"

MAKEOVERRIDES=

## ################################################################

