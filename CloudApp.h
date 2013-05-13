/*
  CloudApp.h
  2012 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2012-12-3
  
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
#ifndef __CLOUDAPP_H__
#define __CLOUDAPP_H__

class CloudApp{

private:

    unsigned char dtaSendRf[20];            // data send to rf
    unsigned char cloudFree;                // if yeelink free
    unsigned long cntCloudFree;             // counter of cloud free

public:

    void init();                            // init
    bool isTrigger(unsigned char *dta);     // if get trigger
    
    void appTimerIsr();                     // put in a tiemr isr, 1ms

    void sendDtaYeelink(unsigned char *dta);           // send data to yeelink
    
};

extern CloudApp APP;
#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/