# Release name
PRODUCT_RELEASE_NAME := P1C

TARGET_BOOTANIMATION_NAME := vertical-540x960

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

# Inherit device configuration
$(call inherit-product, device/samsung/p1c/full_p1c.mk)

## Device identifier. This must come after all inclusions
PRODUCT_DEVICE := p1c
PRODUCT_NAME := cm_p1c
PRODUCT_BRAND := samsung
PRODUCT_MODEL := SCH-I800

#Set build fingerprint / ID / Product Name ect.
PRODUCT_BUILD_PROP_OVERRIDES += PRODUCT_NAME=SCH-I800 TARGET_DEVICE=SCH-I800 BUILD_FINGERPRINT=verizon/SCH-I800/SCH-I800:2.3.4/GINGERBREAD/EF01:user/release-keys PRIVATE_BUILD_DESC="SCH-I800-user 2.3.4 GINGERBREAD EF01 release-keys"

