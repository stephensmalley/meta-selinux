SUMMARY = "Policy analysis tools for SELinux"
DESCRIPTION = "\
SETools is a collection of graphical tools, command-line tools, and \
libraries designed to facilitate SELinux policy analysis. \
\n\
This meta-package depends upon the main packages necessary to run \
SETools."
SECTION = "base"
LICENSE = "GPLv2 & LGPLv2.1"

DEFAULT_PREFERENCE = "-1"

# ${S} is set in selinux_common above, but we need to change it here since the
# top level directory is named differently
S = "${WORKDIR}/git"

SRCREV = "f1e5b208d507171968ca4d2eeefd7980f1004a3c"
SRC_URI = "git://github.com/TresysTechnology/setools3.git;protocol=http"

SRC_URI += "file://setools-neverallow-rules-all-always-fail.patch"
SRC_URI += "file://setools-Fix-sepol-calls-to-work-with-latest-libsepol.patch"

SRC_URI += "file://setools-Don-t-check-selinux-policies-if-disabled.patch"
SRC_URI += "file://setools-configure-ac.patch"
SRC_URI += "file://setools-cross-ar.patch"

SRC_URI += "file://setools-Fix-test-bug-for-unary-operator.patch"
SRC_URI += "file://setools-Fix-python-setools-Makefile.am-for-cross.patch"

LIC_FILES_CHKSUM = "file://${S}/COPYING;md5=26035c503c68ae1098177934ac0cc795 \
                    file://${S}/COPYING.GPL;md5=751419260aa954499f7abaabaa882bbe \
                    file://${S}/COPYING.LGPL;md5=fbc093901857fcd118f065f900982c24"

CFLAGS_append = " -fPIC"
CXXFLAGS_append = " -fPIC"

DEPENDS += "bison-native flex-native python libsepol libselinux libxml2"

PACKAGE_BEFORE_PN += "${PN}-libs"

RPROVIDES_${PN} += "${PN}-console"

FILES_${PN}-dbg += "\
	${libdir}/python${PYTHON_BASEVERSION}/site-packages/setools/.debug \
	"

FILES_${PN}-libs = "\
	${libdir}/libqpol.so.* \
	${libdir}/libapol.so.* \
	${libdir}/libpoldiff.so.* \
	${libdir}/libsefs.so.* \
	${libdir}/libseaudit.so.* \
	${libdir}/python${PYTHON_BASEVERSION}/site-packages/*.egg-info \
	${libdir}/python${PYTHON_BASEVERSION}/site-packages/setools/*.so* \
	${libdir}/python${PYTHON_BASEVERSION}/site-packages/setools/*.py* \
	"

FILES_${PN} += "\
	${bindir}/seinfo \
	${bindir}/sesearch \
	${bindir}/indexcon \
	${bindir}/findcon \
	${bindir}/replcon \
	${bindir}/sechecker \
	${bindir}/sediff \
	${datadir}/setools-3.3/sechecker-profiles \
	${datadir}/setools-3.3/sechecker_help.txt \
	${datadir}/setools-3.3/sediff_help.txt \
	${datadir}/setools-3.3/sediffx* \
	${mandir}/man1/findcon.1.gz \
	${mandir}/man1/indexcon.1.gz \
	${mandir}/man1/replcon.1.gz \
	${mandir}/man1/sechecker.1.gz \
	${mandir}/man1/sediff.1.gz \
	${mandir}/man1/seinfo.1.gz \
	${mandir}/man1/sesearch.1.gz \
	"

inherit autotools pythonnative

# need to export these variables for python-config to work
export BUILD_SYS
export HOST_SYS
export STAGING_INCDIR
export STAGING_LIBDIR

EXTRA_OECONF = "-disable-bwidget-check --disable-selinux-check \
                --disable-swig-python --disable-swig-java --disable-swig-tcl \
                --disable-profiling --disable-gui --with-tk=no --with-tcl=no \
                --with-sepol-devel=${STAGING_LIBDIR}/.. \
                --with-selinux-devel=${STAGING_LIBDIR}/.."

do_configure_prepend() {
	export ac_cv_policydb_version_max=26
	export PYTHON=python
	export PYLIBVER='python${PYTHON_BASEVERSION}'
	export PYTHON_CPPFLAGS="-I${STAGING_INCDIR}/${PYLIBVER}"
	export PYTHON_LDFLAGS="${STAGING_LIBDIR}/lib${PYLIBVER}.so"
	export PYTHON_SITE_PKG="${libdir}/${PYLIBVER}/site-packages"
}

do_install_append() {
	rm -f ${D}/${libdir}/*.a
}

BBCLASSEXTEND = "native"
