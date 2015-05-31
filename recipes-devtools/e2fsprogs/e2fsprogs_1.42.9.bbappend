FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
    file://misc-xattr-copy-xattrs.patch \
    file://Makefile.in-build-xattr.o.patch \
    file://misc-mke2fs.c-label-root-dir-and-cleanup.patch \
    file://misc-create_inode.c-label-fs-objects.patch \
    file://lib-ext2fs-ext2_ext_attr.h-add-xattr-index.patch \
    file://misc-xattr-create-xattr-block.patch \
    file://misc-xattr-create-xattr-block-node.patch \
    file://misc-xattr-create-xattr-cache.patch \
    file://Makefile.in-add-xattr-debug.patch \
    file://misc-xattr-create-xattr-block-debug.patch \
    file://misc-xattr-create-xattr-cache-debug.patch \
"
