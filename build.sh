#!/bin/bash

cd kernel/samsung/galaxytab-cdma
./build_kernel.sh
cd ../../..

source build/envsetup.sh
lunch cm_galaxytab7c-userdebug
make -j4 bacon

