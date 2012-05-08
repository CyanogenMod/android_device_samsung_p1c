#include <fcntl.h>
#include <string.h>
#include <cutils/properties.h>
#include <cutils/log.h>
#include <sys/stat.h>

#define LOG_TAG "bdaddr"
#define BDADDR_PATH "/data/bdaddr"

/* Read bluetooth MAC from RIL (different format),
 * write it directly to bluetoothd address
 *
 * Liberally borrowed from AOKP commit 7ff2808fc6db0601277d728eb2d933ccdbf21aea
 * via Bill Crossley
 */

int main() {
    int fd;
    char addr_from_ril[18];
    char buf[PROPERTY_VALUE_MAX];
    struct stat st;

    /*
     *Have we done this before?
     */

    if ( stat("/data/bdaddr", &st) == 0 ) {
        printf("bdaddr has previously been written, exiting\n");
        LOGE("bdaddr has previously been written, exiting\n");
        return -1;
    }


    /*
     *Get BT Address from ril property and write to btd address
     */
    property_get("ril.bt_macaddr", buf, "");

    if (buf[0] == 0) {
        printf("Unable to read default bdaddr from ril.bt_macaddr, reverting\n");
        LOGE("Unable to read default bdaddr from ril.bt_macaddr, reverting\n");
        return -1;
    }

    printf("Read default bdaddr from ril.bt_macaddr: %s\n", buf);
    LOGE("Read default bdaddr from ril.bt_macaddr: %s\n", buf);

    sprintf(addr_from_ril, "%2.2s:%2.2s:%2.2s:%2.2s:%2.2s:%2.2s\0",
            buf, buf+2, buf+4, buf+6, buf+8, buf+10);

    printf("Converted to formatted mac: %s\n", addr_from_ril);
    LOGE("Converted to formatted mac: %s\n", addr_from_ril);

    fd = open(BDADDR_PATH, O_WRONLY|O_CREAT|O_TRUNC, 00600|00060|00006);
    if (fd < 0) {
        printf("Unable to open bdaddr, bailing\n");
        LOGE("Unable to open bdaddr, bailing\n");
        return -2;
    }

    write(fd, addr_from_ril, 18);
    close(fd);
    LOGE("System will now read mac on reboot.\n");
    return (0);
}
