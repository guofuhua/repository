#include "CSysInfoElement.h"

CSysInfoElement::CSysInfoElement()
{
    m_name = "";//应用程序或命令的名字
    m_State = "";//任务的状态，运行/睡眠/僵死/
    m_Tid = 0;//线程ID
    m_Pid = 0;//进程ID
    m_memRate = 0.0;//内存占用率
    m_cpuRate = 0.0;//CPU占用率
}
