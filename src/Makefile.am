AM_CPPFLAGS = @VMOD_INCLUDES@ -Wall -Werror

vmoddir = @VMOD_DIR@
vmod_LTLIBRARIES = libvmod_dgram.la

libvmod_dgram_la_CFLAGS = @VMOD_INCLUDES@
libvmod_dgram_la_LDFLAGS = -module -export-dynamic -avoid-version -shared

libvmod_dgram_la_SOURCES = \
	vmod_dgram.c
nodist_libvmod_dgram_la_SOURCES = \
	vcc_if.c \
	vcc_if.h

$(libvmod_dgram_la_OBJECTS): vcc_if.h

vcc_if.c vcc_if.h: @VMODTOOL@ $(top_srcdir)/src/vmod_dgram.vcc
	@VMODTOOL@ $(top_srcdir)/src/vmod_dgram.vcc

VMOD_TESTS = $(top_srcdir)/src/tests/*.vtc
.PHONY: $(VMOD_TESTS)

$(top_srcdir)/src/tests/*.vtc:
	@VARNISHTEST@ -Dvarnishd=@VARNISHD@ -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_dgram.vcc \
	$(VMOD_TESTS)

CLEANFILES = $(builddir)/vcc_if.c \
	$(builddir)/vcc_if.h \
	$(builddir)/vmod_dgram.man.rst \
	$(builddir)/vmod_dgram.rst
