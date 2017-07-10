#include "QRegisterProcess.h"
#include <stdlib.h>
#include <stdio.h>

QRegisterProcess::QRegisterProcess(QObject *parent) :
    QObject(parent)
{
    m_process.clear();
}

//
//FUCTION:获得进程ID
//PARAMETER：srtProgramName：进程名；　pid　返回进程ＩＤ
//RETURN：是否获取成功
bool QRegisterProcess::getProgramID(const std::string &srtProgramName, int *pid)
{
//ps | grep FatigueSupervise | grep -v grep | awk '{print $1}'
    std::string strCmd ;
    strCmd ="ps x | grep  "+ srtProgramName + " | grep -v grep | awk '{print $1}'";
    FILE *fp = popen(strCmd.c_str(), "r");
    if(NULL == fp)
    {
      return false;
    }
    char buf[24] = {0};
    int num = fread(buf, sizeof(char), sizeof(buf) - 1, fp);
    pclose(fp);
    if(num < 2)
    {
        return false;
    }
    if(buf[num-1] == '\n') buf[num-1] = '\0';
    int cnt = atoi(buf);
    if (cnt <= 0)
    {
       return false;
    }
    *pid = cnt;
    return true;
}

bool QRegisterProcess::add(QString processName)
{
    int pid = 0;
    bool ret = getProgramID(processName.toStdString(), &pid);

    if (ret)
    {
        m_process.insert(processName, pid);
    }

    return ret;
}

QList<int> QRegisterProcess::getRegisterPid()
{
    return m_process.values();
}
