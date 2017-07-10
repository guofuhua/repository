#include "QSysMem.h"
#include "QGetCPUInfo.h"
#include <QDebug>

QSysMem::QSysMem(QObject *parent) :
    QObject(parent)
{
    m_processInfo.clear();

    if (!add("General_SystemMonitor_Model"))
    {
        printf("[WARNING][%s][%s][%d],General_SystemMonitor_Model not run!!\n", __FILE__,__FUNCTION__,__LINE__);
    }
}

void QSysMem::testPrint()
{
    CGetProcessInfo test;
    //test.testPrintPidArray();
    QList<CSysMemInfoElement> sys_info = test.getSysMemInfoList(m_registProcess.getRegisterPid());
    test.sortByOccupy(sys_info);
    testPrint_sysMem(sys_info);

    QMap<QString, CSysInfoElement>::iterator i;
    for (i = m_processInfo.begin(); i != m_processInfo.end(); ++i)
    {
        qDebug() << i.key() << ":" << i.value().m_Pid;
        CSysMemInfoElement mem = test.getProcessMeminfo(i.value().m_Pid);
        i.value().m_name = mem.m_name;
        i.value().m_State = mem.m_State;
        i.value().m_Tid = mem.m_Tgid;
        i.value().m_memRate = mem.m_occupancyRate;

        i.value().m_cpuRate = QGetCPUInfo;//test
    }
}

void QSysMem::testPrint_sysMem(QList<CSysMemInfoElement> &sys_info)
{
    int size = sys_info.size();
    int i = 0;
    for (i = 0; i < size; i++)
    {
        qDebug() << "pid:" << sys_info.at(i).m_Pid << "name:" << sys_info.at(i).m_name << "mem_use:" << sys_info.at(i).m_VmRSS << "occupy:" << sys_info.at(i).m_occupancyRate << "state:" << sys_info.at(i).m_State;
    }
}

//
//FUCTION:获得进程ID
//PARAMETER：srtProgramName：进程名；　pid　返回进程ＩＤ
//RETURN：是否获取成功
bool QSysMem::getProgramID(const std::string &srtProgramName, int *pid)
{
//ps | grep FatigueSupervise | grep -v grep | awk '{print $1}'
    std::string strCmd ;
    strCmd ="ps ax | grep  "+ srtProgramName + " | grep -v grep | awk '{print $1}'";
    qDebug() << QString(strCmd.c_str());
    FILE *fp = popen(strCmd.c_str(), "r");
    if(NULL == fp)
    {
        FUNC_OUT;
      return false;
    }
    char buf[24] = {0};
    int num = fread(buf, sizeof(char), sizeof(buf) - 1, fp);
    pclose(fp);
    if(num < 2)
    {
        FUNC_OUT;
        return false;
    }
    if(buf[num-1] == '\n') buf[num-1] = '\0';
    int cnt = atoi(buf);
    if (cnt <= 0)
    {
        FUNC_OUT;
       return false;
    }
    *pid = cnt;
    TRACE("%s, :%d\n",buf,*pid);
    FUNC_OUT;
    return true;
}

bool QSysMem::add(QString processName)
{
    CSysInfoElement curProcess;
    int pid = 0;

    bool ret = getProgramID(processName.toStdString(), &pid);

    if (ret)
    {
        curProcess.m_Pid = pid;
    }
    m_processInfo.insert(processName, curProcess);

    return ret;
}
