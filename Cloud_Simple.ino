// cloud simple
#include <TimerOne.h>
#include <Streaming.h>
#include <BeaconDrive.h>
#include <SoftwareSerial.h>

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

#define __Debug                     0                   // debug mode

SoftwareSerial mySerial(6, 7);                          // RX, TX

unsigned char __GdtaUart[50];                           // uart data buff
unsigned char __GdtaUartLen        = 0;                 // uart data len
unsigned char __GstringComplete    = 0;                 // if get data

unsigned char yeelinkFree = 1;
unsigned int cntYeelink   = 0;
unsigned char getNodeDta  = 0;
unsigned int  dtaNode     = 0;

/*********************************************************************************************************
** Function name:           ledShine
** Descriptions:            ledShine
*********************************************************************************************************/
void ledShine(int time)
{
    BcnDrive.setLedShine(1, time);
}

/*********************************************************************************************************
** Function name:           yeelinkAdd
** Descriptions:            add a Node
*********************************************************************************************************/
void yeelinkAdd(unsigned char idNode, unsigned char idSensor, unsigned char idActuator)
{
    char tmp[20];
    sprintf(tmp, "ss1 %d,%d,%dgg", idNode, idSensor, idActuator);
    
    cout << tmp << endl;
    mySerial.println(tmp);
}

/*********************************************************************************************************
** Function name:           yeelinkDel
** Descriptions:            delete a Node 
*********************************************************************************************************/
void yeelinkDel(unsigned char idNode)
{
    char tmp[20];
    sprintf(tmp, "ss2 %dgg", idNode);
    mySerial.println(tmp);
}

/*********************************************************************************************************
** Function name:           yeelinkPost
** Descriptions:            post Data
*********************************************************************************************************/
void yeelinkPost(unsigned char idNode, unsigned int psDta)
{
    char tmp[20];
    sprintf(tmp, "ss3 %d,%d.00gg", idNode, psDta);
    cout << tmp << endl;
    mySerial.println(tmp);
}

/*********************************************************************************************************
** Function name:           timerIsr
** Descriptions:            timer one isr
*********************************************************************************************************/
void timerIsr()
{
    BcnDrive.ledIsr();

    if(!yeelinkFree)
    {
        cntYeelink++;
        if(cntYeelink > 12000)
        {
            cntYeelink  = 0;
            yeelinkFree = 1;

        }
    }
}

/*********************************************************************************************************
** Function name:           checkGoodDta
** Descriptions:            if uart get good data
*********************************************************************************************************/
unsigned char checkGoodDta(unsigned char *dta)
{
    unsigned char ioffset = 0;
    for(ioffset = 0; ioffset < __GdtaUartLen; ioffset++)
    {
        if(dta[ioffset] == FRAMESTART1 && dta[ioffset+1] == FRAMESTART2)
        {
            break;
        }
    }

    if(ioffset > 0)
    {
        for(int i = 0; i<7; i++)
        {
            dta[i] = dta[i+ioffset];
        }
    }

    if((__GdtaUartLen - ioffset)<6 \
        || !(   dta[0] == FRAMESTART1 \
             && dta[1] == FRAMESTART2 \
             && dta[8+dta[6]] == FRAMEEND1 \
             && dta[9+dta[6]] == FRAMEEND2 ))
    {
        __GdtaUartLen     = 0;
        __GstringComplete = 0;
        return 0;
    }

    return 1;
}

/*********************************************************************************************************
** Function name:           checkGoodDta
** Descriptions:            if uart get good data
*********************************************************************************************************/
void sendDtaYeelink(unsigned char *dta)
{

    //if(!yeelinkFree) return ;                       // yeelink not free

    if(!yeelinkFree)
    {
#if __Debug
        cout << "yeelink busy" << endl;
        cout << "cntYeelink = " << cntYeelink << endl;
#endif
        return ;
    }

#if __Debug
    cout << "yeelink free..." << endl;
#endif

    yeelinkFree = 0;
    unsigned int sensorDta   = 0;

    for(int i = 0; i<dta[FRAMEBITDATALEN]; i++)
    {
        sensorDta    = sensorDta << 8;
        sensorDta   += dta[FRAMEBITDATA + i];
    }

    BcnDrive.setLedShine(1, 500);
    
    yeelinkPost(2, sensorDta);                        // post data to yeelink

}

/*********************************************************************************************************
** Function name:           rfDtaProc
** Descriptions:            get data from rfBee and process
*********************************************************************************************************/
void rfDtaProc()
{

    if(__GstringComplete == 1 && checkGoodDta(__GdtaUart))                      // if serial get data
    {
        if(__GdtaUart[FRAMEBITFRAME] == 4)                                      // other device join
        {
            // add code here
        }
        else if(__GdtaUart[FRAMEBITFRAME] == 1)                                 // broad cast
        {
            // add code here
            BcnDrive.setLedShine(1, 20);
            sendDtaYeelink(__GdtaUart);
        }
        __GdtaUartLen      = 0;
        __GstringComplete  = 0;
    }
}

/*********************************************************************************************************
** Function name:           setup
** Descriptions:            setup
*********************************************************************************************************/
void setup() {

    Serial.begin(57600);
    mySerial.begin(9600);
    pinMode(13, OUTPUT);
    
    yeelinkAdd(2, 13, 0);
    delay(100);
    yeelinkAdd(2, 13, 0);
    delay(1000);

    Timer1.initialize(1000);
    Timer1.attachInterrupt( timerIsr );
    
    // yeelinkTest2();

#if __Debug
    cout << "hello world" << endl;
#endif
}

/*********************************************************************************************************
** Function name:           loop
** Descriptions:            loop
*********************************************************************************************************/
void loop()
{
    rfDtaProc();
    mySerialEvent();
}

/*********************************************************************************************************
** Function name:           serialEvent1
** Descriptions:            Serial event
*********************************************************************************************************/
void mySerialEvent()
{

#if 1
    while(Serial.available())
    {
        __GdtaUart[__GdtaUartLen++] = (unsigned char)Serial.read();
        __GstringComplete =   (__GdtaUart[__GdtaUartLen-1] == FRAMEEND2) ? 1 : __GstringComplete;
        __GdtaUartLen = (__GdtaUartLen > 45) ? 0 :  __GdtaUartLen;
    }
#else
    while(Serial.available())
    {
        char a = Serial.read();
        yeelinkTest(a);
    }
#endif
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/