#!/bin/bash

cd kernel/samsung/galaxytab-cdma
./build_kernel.sh
cd ../../..

source build/envsetup.sh
lunch cyanogen_vzwtab-eng
make -j8 bacon

