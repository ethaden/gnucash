gncscmmoddir = ${GNC_SCM_INSTALL_DIR}/gnucash/report
gncscmmod_DATA = \
   aging.scm \
   customer-summary.scm \
   easy-invoice.scm \
   fancy-invoice.scm \
   taxinvoice.scm \
   receipt.scm \
   invoice.scm \
   job-report.scm \
   owner-report.scm \
   payables.scm \
   receivables.scm \
   balsheet-eg.scm \
   business-reports.scm

# Note: list these files separately because they can't be compiled by guile2
#       templates are a mixture of scheme and hmtl
#       css files are not scheme at all
gncscmtpldir = ${GNC_SCM_INSTALL_DIR}/gnucash/report
gncscmtpl_DATA = \
   taxinvoice.eguile.scm \
   taxinvoice.css \
   receipt.eguile.scm \
   receipt.css \
   balsheet-eg.css \
   balsheet-eg.eguile.scm

if GNUCASH_SEPARATE_BUILDDIR
SCM_FILE_LINKS = ${gncscmmod_DATA} \
  ${gncscmtpl_DATA}
endif

.scm-links:
	$(RM) -rf gnucash
	mkdir -p  gnucash
	mkdir -p  gnucash/report
if GNUCASH_SEPARATE_BUILDDIR
	for X in ${SCM_FILE_LINKS} ; do \
	  $(LN_S) -f ${srcdir}/$$X . ; \
	done
endif
	( cd gnucash/report; for A in $(gncscmmod_DATA) ; do $(LN_S) -f ../../$$A . ; done )
if ! OS_WIN32
# Windows knows no "ln -s" but uses "cp": must copy every time (see bug #566567).
	touch .scm-links
endif

if GNC_HAVE_GUILE_2
GUILE_COMPILE_ENV = \
  --gnc-module-dir ${top_builddir}/libgnucash/app-utils \
  --gnc-module-dir ${top_builddir}/libgnucash/engine \
  --gnc-module-dir ${top_builddir}/gnucash/gnome-utils \
  --gnc-module-dir ${top_builddir}/gnucash/html \
  --gnc-module-dir ${top_builddir}/gnucash/report/report-system \
  --guile-load-dir ${top_builddir}/libgnucash/app-utils \
  --guile-load-dir ${top_builddir}/libgnucash/core-utils \
  --guile-load-dir ${top_builddir}/libgnucash/engine \
  --guile-load-dir ${top_builddir}/libgnucash/gnc-module \
  --guile-load-dir ${top_builddir}/gnucash/gnome-utils \
  --guile-load-dir ${top_builddir}/gnucash/report/report-system \
  --guile-load-dir ${top_builddir}/gnucash/report/standard-reports \
  --guile-load-dir ${top_builddir}/gnucash/report/business-reports \
  --guile-load-dir ${top_builddir}/libgnucash/scm \
  --library-dir    ${top_builddir}/libgnucash/engine \
  --library-dir    ${top_builddir}/libgnucash/app-utils \
  --library-dir    ${top_builddir}/libgnucash/core-utils \
  --library-dir    ${top_builddir}/gnucash/gnome-utils \
  --library-dir    ${top_builddir}/libgnucash/backend/xml \
  --library-dir    ${top_builddir}/libgnucash/backend/sql \
  --library-dir    ${top_builddir}/gnucash/html \
  --library-dir    ${top_builddir}/libgnucash/gnc-module \
  --library-dir    ${top_builddir}/gnucash/report/report-system


%.go : %.scm .scm-links $(pkglib_LTLIBRARIES)
	GNC_UNINSTALLED=yes \
	GNC_BUILDDIR=${top_builddir} \
	$(shell ${abs_top_srcdir}/common/gnc-test-env.pl --noexports ${GUILE_COMPILE_ENV}) \
	$(GUILD) compile -o $@ $<

gncscmmodcachedir = ${pkglibdir}/scm/ccache/@GUILE_EFFECTIVE_VERSION@/gnucash/report
gncscmmodcache_DATA = $(gncscmmod_DATA:.scm=.go)
endif

clean-local:
	$(RM) -rf gnucash

noinst_DATA = .scm-links

EXTRA_DIST = \
  ${gncscmmod_DATA} \
  ${gncscmtpl_DATA} \
  CMakeLists.txt

CLEANFILES = .scm-links ${gncscmmodcache_DATA}
DISTCLEANFILES = ${SCM_FILE_LINKS}

AM_CPPFLAGS = -DG_LOG_DOMAIN=\"gnc.business.reports\"
