/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <poll.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/select.h>

#include <cutils/log.h>

#include "LightSensor.h"

// lightsensor_file_illuminance is current value
// lightsensor_file_cmd powers the sensor on but reading file state does that too
#define LIGHT_SENSOR_FILE "/sys/class/lightsensor/switch_cmd/lightsensor_file_state"

#if 0
this is how classy the lightsensor code in kernel is
so it takes 180ms to read effin sensor

	if((bh1721_write_command(chip->client, &POWER_ON))>0)
		light_enable = ON;
	bh1721_write_command(chip->client, &H_RESOLUTION_2);

	/* Maximum measurement time */
	msleep(180);
	bh1721_read_value(chip->client, chip->illuminance_data);
	if((bh1721_write_command(chip->client, &POWER_DOWN))>0)
		light_enable = OFF;
	result = chip->illuminance_data[0] << 8 | chip->illuminance_data[1];
	result = (result*10)/12;
	
	/* apply hysteresis */
	result = get_next_level(result);
	return sprintf(buf, "%d\n", result);
#endif



/*****************************************************************************/

LightSensor::LightSensor()
    : SensorBase(NULL, NULL),
      mEnabled(0),
      mExtraDelay(0),
      mPendingEvents(0),
      mPushFD(-1)
{
    mPendingEvent.version = sizeof(sensors_event_t);
    mPendingEvent.sensor = ID_L;
    mPendingEvent.type = SENSOR_TYPE_LIGHT;
    memset(mPendingEvent.data, 0, sizeof(mPendingEvent.data));

    int sv[2];
    pipe(sv);
    data_fd = sv[0];
    mPushFD = sv[1];

    enable(0, 1);
}

LightSensor::~LightSensor() {
    if (mPushFD >= 0)
    {
        close(mPushFD);
        mPushFD = -1;
    }
    if (data_fd)
    {
        close(data_fd);
        data_fd = -1;
    }
}

int LightSensor::setInitialState() {
    read();
    return 0;
}

static void *jumper(void *arg)
{
    ((LightSensor *)arg)->readLoop();
    return NULL;
}

int LightSensor::enable(int32_t, int en) {
    int nNewState = en ? 1 : 0;
    int err = 0;
    if (nNewState != mEnabled) {
        if (nNewState)
        {
            setInitialState();
            bReaderRunning = true;
            pthread_create(&mReaderThread, NULL, jumper, (void *)this);
        }
        else
        {
            bReaderRunning = false;
            pthread_join(mReaderThread, NULL);
        }
        mEnabled = nNewState;
    }
    return err;
}

bool LightSensor::hasPendingEvents() const {
    return (mPendingEvents > 0);
}

int LightSensor::readEvents(sensors_event_t* data, int count)
{
    if (count < 1)
        return -EINVAL;
    int rd = 0;

    {
        android::Mutex::Autolock lock(mLock);
        while (count && mPendingEvents) {
            unsigned int l;
            ::read(data_fd, (void *)&l, sizeof(l));
            mPendingEvent.light = (float)l;
            mPendingEvent.timestamp = getTimestamp();
            *data = mPendingEvent;
            mPendingEvents--;
            count--;
            data++;
            rd++;
        }
    }

    return mEnabled ? rd : 0;
}

float
LightSensor::read(void)
{
    int fd;
    char buf[8];
    fd = open(LIGHT_SENSOR_FILE, O_RDONLY);
    ssize_t r;
    r = ::read(fd, (void *)buf, 7); // this probably takes 180ms
    close(fd);
    buf[r] = 0;
    unsigned int l;
    l = strtoul(buf, NULL, 10);
    int w;
    w = ::write(mPushFD, (void *)&l, sizeof(l));
    {
        android::Mutex::Autolock lock(mLock);
        mPendingEvents++;
    }
    return (float)l;
}

void
LightSensor::readLoop(void)
{
    while (bReaderRunning) {
        read();
        usleep(mExtraDelay);
    }
}

int
LightSensor::setDelay(int32_t handle, int64_t ns)
{
    ns /= 1000;
    if (ns > 180000)
    {
        mExtraDelay = (unsigned int)ns - 180000;
    }
    return 0;
}


