FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
    file://misc-xattr-copy-xattrs.patch \
    file://Makefile.in-build-xattr.o.patch \
    file://misc-mke2fs.c-label-root-dir-and-cleanup.patch \
    file://misc-create_inode.c-label-fs-objects.patch \
"
