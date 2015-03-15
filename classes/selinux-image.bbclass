selinux_set_labels () {
    POL_TYPE=$(sed -n -e "s&SELINUXTYPE[:space:]*=[:space:]*\([0-9A-Za-z_]\+\)&\1&p" ${IMAGE_ROOTFS}/${sysconfdir}/selinux/config)
    setfiles -v -r ${IMAGE_ROOTFS} ${IMAGE_ROOTFS}/${sysconfdir}/selinux/${POL_TYPE}/contexts/files/file_contexts ${IMAGE_ROOTFS} || exit 2;
}

IMAGE_PREPROCESS_COMMAND += "selinux_set_labels ;"
IMAGE_CMD_OPTS_tar += "--selinux"

inherit core-image
