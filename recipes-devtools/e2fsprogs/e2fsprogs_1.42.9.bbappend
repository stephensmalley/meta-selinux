FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
    file://misc-xattr-copy-xattrs.patch \
    file://Makefile.in-build-xattr.o.patch \
"
