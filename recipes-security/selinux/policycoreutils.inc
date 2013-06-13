PRINC = "3"

SUMMARY = "SELinux policy core utilities"
DESCRIPTION = "policycoreutils contains the policy core utilities that are required \
for basic operation of a SELinux system.  These utilities include \
load_policy to load policies, setfiles to label filesystems, newrole \
to switch roles, and run_init to run /etc/init.d scripts in the proper \
context."
SECTION = "base"
LICENSE = "GPLv2+"

SRC_URI += "${@base_contains('DISTRO_FEATURES', 'pam', '${PAM_SRC_URI}', '', d)}"

PAM_SRC_URI = "file://pam.d/newrole \
               file://pam.d/run_init \
              "

DEPENDS += "libsepol libselinux libsemanage python-native"
EXTRA_DEPENDS = "libcap-ng libcgroup"
DEPENDS += "${@['', '${EXTRA_DEPENDS}']['${PN}' != '${BPN}-native']}"

inherit selinux
DEPENDS += "${@target_selinux(d, 'libpam audit')}"

RDEPENDS_${BPN} += "\
	libselinux-python \
	libsemanage-python \
	sepolgen \
	"
RDEPENDS_${BPN} += "\
	python \
	python-unixadmin \
	python-shell \
	python-crypt \
	python-subprocess \
	python-syslog \
	python-textutils \
	python-ipy \
	"

RDEPENDS_${BPN}-fixfiles += "${BPN}-setfiles"
RDEPENDS_${BPN}-genhomedircon += "\
	${BPN}-genhomedircon \
	${BPN}-semodule \
	"
RDEPENDS_${BPN}-loadpolicy += "\
	libselinux \
	libsepol \
	"
RDEPENDS_${BPN}-newrole += "\
	libcap-ng \
	libselinux \
	"
RDEPENDS_${BPN}-runinit += "libselinux"
RDEPENDS_${BPN}-secon += "libselinux"
RDEPENDS_${BPN}-semodule += "\
	libsepol \
	libselinux \
	libsemanage \
	"
# static link to libsepol
DEPENDS_${BPN}-semodule-deps += "libsepol"
RDEPENDS_${BPN}-semodule-expand += "libsepol libselinux"
RDEPENDS_${BPN}-semodule-link += "libsepol libselinux"
RDEPENDS_${BPN}-semodule-package += "libsepol libselinux"
# static link to libsepol
DEPENDS_${BPN}-sepolgen-ifgen += "libsepol"
RDEPENDS_${BPN}-sepolgen-ifgen += "libselinux-python"
RDEPENDS_${BPN}-sestatus += "libselinux"
RDEPENDS_${BPN}-setfiles += "\
	libselinux \
	libsepol \
	"
RDEPENDS_${BPN}-setsebool += "\
	libsepol \
	libselinux \
	libsemanage \
	"

RDEPENDS_${BPN} += "setools setools-libs ${BPN}-python"

WARN_QA := "${@oe_filter_out('unsafe-references-in-scripts', '${WARN_QA}', d)}"
ERROR_QA := "${@oe_filter_out('unsafe-references-in-scripts', '${ERROR_QA}', d)}"

PACKAGES =+ "\
	${PN}-fixfiles \
	${PN}-genhomedircon \
	${PN}-loadpolicy \
	${PN}-newrole \
	${PN}-python \
	${PN}-runinit \
	${PN}-sandbox \
	${PN}-secon \
	${PN}-semodule \
	${PN}-semodule-deps \
	${PN}-semodule-expand \
	${PN}-semodule-link \
	${PN}-semodule-package \
	${PN}-sepolgen-ifgen \
	${PN}-sestatus \
	${PN}-setfiles \
	${PN}-setsebool \
	system-config-selinux \
	"
FILES_${PN}-fixfiles += "${base_sbindir}/fixfiles"
FILES_${PN}-genhomedircon += "${sbindir}/genhomedircon"
FILES_${PN}-loadpolicy += "\
	${base_sbindir}/load_policy \
	${sbindir}/load_policy \
	"
FILES_${PN}-newrole += "\
	${bindir}/newrole \
	${@base_contains('DISTRO_FEATURES', 'pam', '${sysconfdir}/pam.d/newrole', '', d)} \
	"
FILES_${PN}-python = " \
	${bindir}/audit2allow \
	${bindir}/audit2why \
	${bindir}/chcat \
	${sbindir}/semanage \
	${sysconfdir}/bash_completion.d/semanage-bash-completion.sh \
	${libdir}/python${PYTHON_BASEVERSION}/site-packages/* \
	"
FILES_${PN}-runinit += "\
	${sbindir}/run_init \
	${sbindir}/open_init_pty \
	${@base_contains('DISTRO_FEATURES', 'pam', '${sysconfdir}/pam.d/run_init', '', d)} \
	"
FILES_${PN}-sandbox += "\
	${datadir}/sandbox/* \
	${bindir}/sandbox \
	${sbindir}/seunshare \
	${sysconfdir}/sysconfig/sandbox \
	"
FILES_${PN}-secon += "${bindir}/secon"
FILES_${PN}-semodule += "${sbindir}/semodule"
FILES_${PN}-semodule-deps += "${bindir}/semodule_deps"
FILES_${PN}-semodule-expand += "${bindir}/semodule_expand"
FILES_${PN}-semodule-link += "${bindir}/semodule_link"
FILES_${PN}-semodule-package += "\
	${bindir}/semodule_package \
	${bindir}/semodule_unpackage \
	"
FILES_${PN}-sepolgen-ifgen += "\
	${bindir}/sepolgen-ifgen \
	${bindir}/sepolgen-ifgen-attr-helper \
	"
FILES_${PN}-sestatus += "\
	${sbindir}/sestatus \
	${sysconfdir}/sestatus.conf \
	"
FILES_${PN}-setfiles += " \
	${base_sbindir}/restorecon \
	${base_sbindir}/setfiles \
	"
FILES_${PN}-setsebool += " \
	${sbindir}/setsebool \
	${sysconfdir}/bash_completion.d/setsebool-bash-completion.sh \
	"

AUDITH="`ls ${STAGING_INCDIR}/libaudit.h >/dev/null 2>&1 && echo /usr/include/libaudit.h `"
PAMH="`ls ${STAGING_INCDIR}/security/pam_appl.h >/dev/null 2>&1 && echo /usr/include/security/pam_appl.h `"
EXTRA_OEMAKE += "${@target_selinux(d, 'PAMH=${PAMH} AUDITH=${AUDITH}', 'PAMH= AUDITH= ')} INOTIFYH=n"
EXTRA_OEMAKE += "PREFIX=${D}"
EXTRA_OEMAKE += "INITDIR=${D}/etc/init.d"

BBCLASSEXTEND = "native"

PCU_NATIVE_CMDS = "setfiles semodule_package semodule semodule_link semodule_expand semodule_deps"

do_compile_virtclass-native() {
	for PCU_CMD in ${PCU_NATIVE_CMDS} ; do
		oe_runmake -C $PCU_CMD \
			INCLUDEDIR='${STAGING_INCDIR}' \
			LIBDIR='${STAGING_LIBDIR}'
	done
}

do_install_virtclass-native() {
	for PCU_CMD in ${PCU_NATIVE_CMDS} ; do
	     oe_runmake -C $PCU_CMD install \
			DESTDIR="${D}" \
			PREFIX="${D}/${prefix}" \
			SBINDIR="${D}/${base_sbindir}"
	done
}

do_install_append() {
	test "${CLASSOVERRIDE}" = "class-native" && return 0

	if [ -e ${WORKDIR}/pam.d ]; then
		install -d ${D}${sysconfdir}/pam.d/
		install -m 0644 ${WORKDIR}/pam.d/* ${D}${sysconfdir}/pam.d/
	fi
}
