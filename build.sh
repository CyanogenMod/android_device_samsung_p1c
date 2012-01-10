#!/bin/bash

cd kernel/samsung/galaxytab-cdma
./build_kernel.sh
cd ../../..

source build/envsetup.sh
lunch teamhacksung_vzwtab-userdebug
make -j4 bacon

