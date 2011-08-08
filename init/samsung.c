#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <fcntl.h>
#include <unistd.h>

#include "log.h"
#include "samsung.h"

int do_insmod(int nargs, char **args);

/*

/dev/block/stl6 on /mnt/.lfs type j4fs (rw,relatime)
brw-------    1 root     root      138,   6 Apr  5 09:30 stl6

*/

static status_t param_blk;
static int loaded = 0;

static int
load_param_blk(void)
{
    int err;
    int fd;
    static const char *devname = "/dev/stl6";
    static const char *lfs = "/.lfs";
    static const char *paramname = "/.lfs/param.blk";

    static char *mod_fsr[] = { "insmod", "/lib/modules/fsr.ko" };
    static char *mod_fsr_stl[] = { "insmod", "/lib/modules/fsr_stl.ko" };
    static char *mod_j4fs[] = { "insmod", "/lib/modules/j4fs.ko" };

    if (loaded)
    {
        return 0;
    }
    if ((err = do_insmod(2, mod_fsr)) < 0)
    {
        ERROR("failed to load fsr module %d\n", err);
        return err;
    }

    if ((err = do_insmod(2, mod_fsr_stl)) < 0)
    {
        ERROR("failed to load fsr_stl module %d\n", err);
        return err;
    }

    if ((err = do_insmod(2, mod_j4fs)) < 0)
    {
        ERROR("failed to load j4fs module %d\n", err);
        return err;
    }

    if ((err = mknod(devname, S_IFBLK | 0600, (138 << 8) | 6)) < 0)
    {
        ERROR("failed to create stl6 device node %d\n", err);
        return err;
    }

    mkdir(lfs, 0755);
    if ((err = mount(devname, lfs, "j4fs", 0, NULL)) < 0)
    {
        ERROR("failed to mount lfs %d\n", err);
        rmdir(lfs);
        unlink(devname);
        return err;
    }
    fd = open(paramname, O_RDONLY);
    if (fd < 0)
    {
        ERROR("failed to open param.blk %d\n", fd);
        umount(lfs);
        rmdir(lfs);
        unlink(devname);
        return fd;
    }

    if ((err = read(fd, &param_blk, sizeof(param_blk))) != sizeof(param_blk))
    {
        ERROR("failed to read param.blk %d\n", err);
        close(fd);
        umount(lfs);
        rmdir(lfs);
        unlink(devname);
        return -1;
    }

    close(fd);
    umount(lfs);
    rmdir(lfs);
    unlink(devname);

    if (param_blk.param_magic != PARAM_MAGIC
        || param_blk.param_version != PARAM_VERSION)
    {
        ERROR("param.blk magic or version is invalid\n");
        return -1;
    }
    loaded = 1;
    return 0;
}

int
samsung_bootmode(void)
{
    int err;
    unsigned int i;
    if ((err = load_param_blk()) < 0)
    {
        return err;
    }
    for (i = 0; i < MAX_PARAM - MAX_STRING_PARAM; i++)
    {
        if (__REBOOT_MODE == param_blk.param_list[i].ident)
        {
            ERROR("bootmode is %d\n", param_blk.param_list[i].value);
            INFO("bootmode is %d\n", param_blk.param_list[i].value);
            return param_blk.param_list[i].value;
        }
    }
    ERROR("cannot find REBOOT_MODE in param_blk\n");
    return -1;
}
