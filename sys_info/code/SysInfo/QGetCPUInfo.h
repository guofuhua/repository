#ifndef QGETCPUINFO_H
#define QGETCPUINFO_H

#include <QObject>
#include <QMap>
#include <QTimer>
#include "CGetCPUInfo.h"

typedef struct processCpuInfo
{
    int last_cpu;
    float use_rate;
} TProcessCPUInfo;

class QGetCPUInfo : public QObject
{
    Q_OBJECT
public:
    static QGetCPUInfo* getInstance()
    {
        static QGetCPUInfo instance;
        return &instance;
    }
    bool addMointorList(int pid);
    void removMointorList(int pid);
    
private:
    explicit QGetCPUInfo(QObject *parent = 0);

public:
    CGetCPUInfo m_cpuMethod;

private:
    QMap<int, TProcessCPUInfo> m_cpuList;
    int m_lastMomentCPU;
    int m_lastMomentIdleCPU;
    QTimer m_timer;
    float m_cpu_usage_rate;

signals:
    void signalPidNotExist(int);
    
public slots:
    void slotUpdateCPUUsage();
};

#endif // QGETCPUINFO_H
