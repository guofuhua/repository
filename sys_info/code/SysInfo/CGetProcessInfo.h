#ifndef CGETPROCESSINFO_H
#define CGETPROCESSINFO_H
#include<stdio.h>
#include<unistd.h>
#include<qstringlist.h>
#include<qvector.h>
#include<qlist.h>
#include"CSysMemInfoElement.h"

#define VMRSS_LINE 15//VMRSS所在行

class CGetProcessInfo
{
public:
    CGetProcessInfo();
    int getTotalMem();
    int getFreeMem();
    QVector<int> getLinuxProcessPid();
    void testPrintPidArray();
    CSysMemInfoElement getProcessMeminfo(int pid);
    QList<CSysMemInfoElement> getSysMemInfoList();
    QList<CSysMemInfoElement> getSysMemInfoList(QList<int> processPid);
    void sortByOccupy(QList<CSysMemInfoElement> &sys_info_list);

private:
    int m_totalmem;
};

#endif // CGETPROCESSINFO_H
