/*
  CloudApp.cpp
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
#include <Arduino.h>

#include "CloudApp.h"
#include "CloudGlobalDfs.h"

/*********************************************************************************************************
** Function name:           init
** Descriptions:            init
*********************************************************************************************************/
void CloudApp::init()
{
    cloudFree       = 1;                
    cntCloudFree    = 0;           
}

/*********************************************************************************************************
** Function name:           appTimerIsr
** Descriptions:            appTimerIsr
*********************************************************************************************************/
void CloudApp::appTimerIsr()
{
    if(!cloudFree)
    {
        cntCloudFree++;
        if(cntCloudFree > 12000)
        {
            cloudFree = 1;
        }
    }
}

/*********************************************************************************************************
** Function name:           appTimerIsr
** Descriptions:            appTimerIsr
*********************************************************************************************************/
bool CloudApp::isTrigger(unsigned char *dta)
{

    return (dta[FRAMEBITDESTID] == 0 && dta[FRAMEBITFRAME] == FRAMETYPEBC) ? 1 : 0;

}

/*********************************************************************************************************
** Function name:           carryState
** Descriptions:            carryState
*********************************************************************************************************/
void CloudApp::sendDtaYeelink(unsigned char *dta)
{
 
    if(cloudFree)
    {
        cloudFree = 0;
        
        int dtaSensor = 0;
        
        for(int i = 0; i<dta[FRAMEBITDATALEN]; i++)
        {
            dtaSensor    = dtaSensor << 8;
            dtaSensor   += dta[FRAMEBITDATA + i];
        }
        
        // add code here, send data to yeelink
        
    }
}

CloudApp APP;
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/