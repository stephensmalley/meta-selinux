PR .= ".1"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${PV}:"

SRC_URI += "file://findutils-selinux.patch"
SRC_URI += "file://findutils-selinux-gnulib.patch"

DEPENDS += "${@base_contains('DISTRO_FEATURES', 'selinux', 'libselinux', '', d)}"

EXTRA_OECONF += "${@base_contains('DISTRO_FEATURES', 'selinux', '--with-selinux', '--without-selinux', d)}"
