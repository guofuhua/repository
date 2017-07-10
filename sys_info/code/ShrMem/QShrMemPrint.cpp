#include "QShrMemPrint.h"
#include <stdio.h>
//common include
#include "ShareMem/CShrMem_DevState.h"
#include "ShareMem/CShrMem_DriverState.h"
#include "ShareMem/CShrMem_SystemMode.h"
#include "ShareMem/QShrMem_GpsInfo.h"
#include "ShareMem/QShrMem_LEDState.h"
#include "ShareMem/QShrMem_OSDVideoImage.h"
#include "ShareMem/QShrMem_TAXInfo.h"
#include "ShareMem/QShrMem_VideoImgae.h"

QShrMemPrint::QShrMemPrint(QObject *parent) :
    QObject(parent)
{
    connect(&m_print_timer,SIGNAL(timeout()),this,SLOT(slotPrintShrMem()));
}

void QShrMemPrint::startPrint()
{
    m_print_timer.start(2000);
}

void QShrMemPrint::stopPrint()
{
    m_print_timer.stop();
}

void QShrMemPrint::slotPrintShrMem()
{
    QShrMem_OSDVideoImage osd_video;
    STM32Data tax = QShrMem_TAXInfo::getInstance()->getSTM32Data();
    TGPS_State gps = QShrMem_GpsInfo::getInstance()->getGpsData();

    int channel_num = QShrMem_VideoImgae::getInstance()->GetInputCount();
    uint frame_num = QShrMem_VideoImgae::getInstance()->GetYUVFrameIndex();
    uint frame_osd_num = osd_video.ReadYUVFrameIndex();

    uchar ch1_s = CShrMem_DevState::getInstance()->getChannel1State();
    uchar ch2_s = CShrMem_DevState::getInstance()->getChannel2State();
    uchar ch3_s = CShrMem_DevState::getInstance()->getChannel3State();
    uchar ch4_s = CShrMem_DevState::getInstance()->getChannel4State();
    uchar can = CShrMem_DevState::getInstance()->getCanNetState();
    uchar net = CShrMem_DevState::getInstance()->getNetConnetState();
    uchar sd = CShrMem_DevState::getInstance()->getSDState();

    uint keep = CShrMem_DriverState::getInstance()->getKeepSec();
    uchar alu = CShrMem_DriverState::getInstance()->getAluState();
    uchar face = CShrMem_DriverState::getInstance()->getFaceState();
    int alarm = CShrMem_DriverState::getInstance()->getAlarmType();

    uchar side = CShrMem_SystemMode::getInstance()->getCurrentSide();
    uchar mode = CShrMem_SystemMode::getInstance()->getCureentMode();
    uchar sys6A = CShrMem_SystemMode::getInstance()->getSys6Amode();
    uchar train_type = CShrMem_SystemMode::getInstance()->getSigTrainType();

    uchar led1 = QShrMem_LEDState::getInstance()->getLEDState(1).uState;
    uchar led2 = QShrMem_LEDState::getInstance()->getLEDState(2).uState;
    uchar led3 = QShrMem_LEDState::getInstance()->getLEDState(3).uState;
    uchar led4 = QShrMem_LEDState::getInstance()->getLEDState(4).uState;
    uchar led5 = QShrMem_LEDState::getInstance()->getLEDState(5).uState;
    uchar led6 = QShrMem_LEDState::getInstance()->getLEDState(6).uState;
    uchar led7 = QShrMem_LEDState::getInstance()->getLEDState(7).uState;
    uchar led8 = QShrMem_LEDState::getInstance()->getLEDState(8).uState;
    printf("---------->>>>>>>>>>>>>>>>>>>>>>>------------------------------------------------------------\n");
    printf("TAX:speed(%d)\ttime(%s)\n",tax.m_realSpeed, tax.m_time.toString("yyyy-MM-dd h:m:s").toStdString().c_str());
    printf("GPS:lon(%s)\tlat(%s)\ttime(%s)\tspeed(%f)\n", gps.lon, gps.lat, gps.BJTime, gps.Speed);
    printf("VideoImage:channel(%d), frame(%d)\n", channel_num, frame_num);
    printf("OSDVideoImage:frame(%d)\n", frame_osd_num);
    printf("DevState:ch1(%d), ch2(%d), ch3(%d), ch4(%d), CanNetState(%d), NetConnetSate(%d), SDState(%d)\n",\
           ch1_s, ch2_s, ch3_s, ch4_s, can, net, sd);
    printf("DriverState:KeepSec(%u), AluState(%d), FaceState(%d), AlarmType(%d)\n", keep, alu, face, alarm);
    printf("SystemMode:CurrentSide(%d), CurrentMode(%d), Sys6AMode(%d), SigTrainType(%d)\n", \
           side, mode, sys6A, train_type);
    printf("LEDState:LED1(%d), LED2(%d), LED3(%d), LED4(%d), LED5(%d), LED6(%d), LED7(%d), LED8(%d)\n",
           led1, led2, led3, led4, led5, led6, led7, led8);
    printf("---------->>>>>>>>>>>>>>>>>>>>>>>------------------------------------------------------------\n");
    printf("-\n");
    return;
}
