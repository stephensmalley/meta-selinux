SUMMARY = "MCS (Multi Category Security) variant of the SELinux policy"
DESCRIPTION = "\
This is the reference policy for SE Linux built with MCS support. \
MCS is an optional addition in SELinux that adds a set of categories to processes and files. \
In access checks, Constraints are applied which require the category component of the label in the source type be a superset of the target. \
"

PR = "r0"

POLICY_NAME = "mcs"
POLICY_TYPE = "mcs"
POLICY_DISTRO = "redhat"
POLICY_UBAC = "n"
POLICY_UNK_PERMS = "deny"
POLICY_DIRECT_INITRC = "n"
POLICY_MONOLITHIC = "n"
POLICY_CUSTOM_BUILDOPT = ""
POLICY_QUIET = "n"

POLICY_MLS_SENS = "16"
POLICY_MLS_CATS = "1024"
POLICY_MCS_CATS = "1024"

include refpolicy_${PV}.inc
