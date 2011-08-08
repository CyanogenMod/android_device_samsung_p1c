This is a beta build of CyanogenMod 7 gingerbread
by Technomancer TCMAN-dmg on freenode.net and irc.droid-life.com

Bug reports: open issues at http://github.com/techomancer/android_device_samsung_galaxytab

This build is for beta testing, not for general consumption

CREDITS

See http://cmsgs.com for more info
The github for CMSGS Tab is http://github.com/cmsgs

It is based on great work of CM SGS team http://cmsgs.com

Thanks to codeworkx, coolya and noobnl and all beta testers.

INSTALLATION

Your Tab should be partitioned with P1_add_hidden
It should have unsigned bootloaders that can load Euro ROMs
Wipe your Tab (data, dbdata, cache)
Flash it with heimdall (use simple flashme script for full flash)
Or just flash zImage and factoryfs.ext4.

For Google apps download latest HDPI apps for Gingerbread http://goo-inside.me/gapps/ and install using recovery.

Status
Voice: OK
3G Data: OK
Wifi: works
BT: sometimes stuck on startup, doesnt fully pair
GPS: working
Buttons backlight - linked to LCD backlight
Sensors:
- BMA020/BMA150 Accelerometer
- AK8973B: gravity OK, rest needs tuning
- BH1721FVC Lightsensor: OK
- L3G4200D gyro: uninmplemented
- Proximity: faked at 10cm
Camera: broken

Issues and workarounds
* Stuck on CM boot ani after flash
    After first install please start in recovery and do full wipe (select "wipe data/factory reset in recovery)

* BT doesnt start
    Try again
    Try rebooting
    If that doesnt help try "adb shell stop hciattach" Sometimes hciattach service gets stuck when starting.

Changelog:
2011-04-05
    Fixed suid/root issues. Refreshed and rebuilt with latest.
    
2011-03-30
    Built from new repo branched off teamhacksung.
    overlay and libstagefrighthw (video accell) disabled so it is stable now.
    Camera is disabled (stubbed).
    data, dbdata and cache partition switched to ext4.

2011-03-02
    Added source modules for pvrsrvkm, s3c_bc and s3c_lcd to kernel sources and build them from scratch
    Refreshed, merged and rebuilt, media scanner works again
2011-03-01
    Refreshed and merged latest frameworks etc from CM repo
    Rebuilt everything
    Use vold built from source

2011-02-17
    Refreshed repo and rebuild
    initramfs built from sources instead of checked in, still far from automated build tho ;-(
2011-02-07
    Refreshed repo and rebuilt.
    Backed out codeworkx's bluetooth fix, it seems to make things worse. Added stopping and cleaning up hciattach if it fails. Now if Bluetooth start fails, just try starting it again.
    Removed overlay and copybit built from source, they cant both be installed. Use binary copybit since the ones built from the source use wrong kernel headers. Camera shows some signs of life now.
    Patched code that calls gralloc to remove usage flags not known by froyo gralloc.
    
2011-02-03 New kernel from Update1
    Refreshed repo and rebuild with latest
    added codeworkx's brcm_patchram_plus fix that should hopefully fix bluetooth initialization
    
2011-01-31 GPS should work now
    Used Nexus S GPS binaries
    Switched to init compiled from sources
    Switched to CWM 3.x (still very broken)

2011-01-29 Fixed 3G data

2011-01-28 First beta release


--
Dominik

