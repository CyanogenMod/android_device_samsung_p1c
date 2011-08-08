#!/bin/bash
# this is a helper script for kernel build
# it does exactly the same stuff as full_galaxytab.mk
# but it can be called at any time
# run config and modules before building the tree
# run all after building the tree

HERE=`pwd`
DEPTH=../../../..

cd ${DEPTH}
ANDROID_BUILD_TOP=`pwd`
echo -n current directory is ${ANDROID_BUILD_TOP}

KERNEL_DIR=${ANDROID_BUILD_TOP}/kernel/samsung/2.6.32-tab
KERNEL_BUILD=${ANDROID_BUILD_TOP}/out/target/product/galaxytab/kernel_build
KERNEL_TOOLCHAIN=/opt/toolchains/arm-2009q3/bin/arm-none-linux-gnueabi-

mkdir -p ${KERNEL_BUILD}

case "$1" in
    config)
	make -C ${KERNEL_DIR} ARCH=arm O=${KERNEL_BUILD} CROSS_COMPILE=${KERNEL_TOOLCHAIN} p1_android_rfs_eur_cm7_defconfig
	;;
    menuconfig)
	make -C ${KERNEL_DIR} ARCH=arm O=${KERNEL_BUILD} CROSS_COMPILE=${KERNEL_TOOLCHAIN} menuconfig
	;;
    modules)
	make -j4 -C ${KERNEL_DIR} ARCH=arm O=${KERNEL_BUILD} CROSS_COMPILE=${KERNEL_TOOLCHAIN} modules
	;;
    all)
	make -j4 -C ${KERNEL_DIR} ARCH=arm O=${KERNEL_BUILD} CROSS_COMPILE=${KERNEL_TOOLCHAIN} all
	cp ${KERNEL_BUILD}/arch/arm/boot/zImage ${ANDROID_BUILD_TOP}/out/target/product/galaxytab/kernel
	cp ${KERNEL_BUILD}/arch/arm/boot/zImage ${HERE}
	;;
esac


cd ${HERE}
