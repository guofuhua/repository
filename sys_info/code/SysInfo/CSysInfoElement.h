#ifndef CSYSINFOELEMENT_H
#define CSYSINFOELEMENT_H
#include <QString>

class CSysInfoElement
{
public:
    CSysInfoElement();

public:
    QString m_name;//应用程序或命令的名字
    QString m_State;//任务的状态，运行/睡眠/僵死/
    int m_Tid;//线程ID
    int m_Pid;//进程ID
    float m_memRate;//内存占用率
    float m_cpuRate;//CPU占用率
};

#endif // CSYSINFOELEMENT_H
