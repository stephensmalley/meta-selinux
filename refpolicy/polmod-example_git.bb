DESCRIPTION = "Example SELinux policy module."
HOMEPAGE = "https://github.com/flihp/polmod-example"

SRC_URI = "git://github.com/flihp/${PN}.git"
SRCREV_default_pn-${PN} = "${AUTOREV}"

LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://${S}/COPYING;md5=393a5ca445f6965873eca0259a17f833"

PACKAGE_ARCH = "${MACHINE_ARCH}"
PR = "r0"
S = "${WORKDIR}/git"

FILES_${PN} =+ "${datadir}/selinux/${NAME}/*.pp"
FILES_${PN}-dev =+ "${datadir}/selinux/${NAME}/include/*.if"

PARALLEL_MAKE = ""

def get_poltype(f):
    import re
    config = open (f, "r")
    regex = re.compile('^[\s]*SELINUXTYPE=[\s]*(\w+)[\s]*$')
    for line in config:
        match = regex.match(line)
        if match is not None:
            return match.group(1)
    return None

conf_file = "${STAGING_DIR_HOST}${sysconfdir}/selinux/config"
NAME = "${@get_poltype(conf_file)}"

EXTRA_OEMAKE += " \
    BINDIR=${STAGING_BINDIR_NATIVE} \
    SBINDIR=${STAGING_DIR_NATIVE}${sbindir_native} \
    NAME=${NAME} \
    HEADERDIR=${STAGING_DIR_HOST}${datadir}/selinux/${NAME}/include \
    "

do_install () {
	oe_runmake DESTDIR=${D} install
	oe_runmake DESTDIR=${D} install-headers
}
