/*
  CloudGlobalDfs.h
  2012 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-4-23
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef __CLOUDGLOBALDFS_H__
#define __CLOUDGLOBALDFS_H__

#define SendByteToRfbee             Serial.write        // send a byte to Serial

#define TURNOFFDELAYTIME            80                  // when press the button for xx*10 ms, turn off the system

// data frame
#define FRAMESTART1                 0x53                // data frame start1
#define FRAMESTART2                 0x01                // data frame start2
#define FRAMEEND1                   0x2f                // data frame end1
#define FRAMEEND2                   0x45                // data frame end2

//bit of frame
#define FRAMEBITSTART1              0                   // frame data bit0
#define FRAMEBITSTART2              1
#define FRAMEBITSRCID               2
#define FRAMEBITSENSORID            3
#define FRAMEBITDESTID              4
#define FRAMEBITFRAME               5
#define FRAMEBITDATALEN             6
#define FRAMEBITDATA                7

// frame type
#define FRAMETYPEBC                 1                   // broadcast
#define FRAMETYPECTRL               2                   // control
#define FRAMETYPESET                3                   // setting

// led Mode
#define LEDEANBLE                   1
#define LEDDISABLE                  0

// send dta to yeelink ,atom cloud
#define YEEATOM                     0
#define YEECLOUD                    1

// EEPRMO ADDRESS
#define EEPADDISSET                 100                 // if setted! if not ,zero, if setted, 1
#define EEPADDDEVICEID              101                 // device id

// SENSOR ADDRESS
#define EEPADDIFSETSE               120                 // if set sensor
#define EEPADDSENSORID              EEPADDIFSETSE+1     // sensor id

#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/