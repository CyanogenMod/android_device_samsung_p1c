#!/bin/bash

source build/envsetup.sh
lunch cyanogen_vzwtab-eng
make -j8 bacon

