#include "QGetCPUInfo.h"

#define DEFAULT_CPU_RATE  (-1.0)

QGetCPUInfo::QGetCPUInfo(QObject *parent) :
    QObject(parent)
{
    m_cpuList.clear();
    m_lastMomentCPU = m_cpuMethod.get_all_time(&m_lastMomentIdleCPU);
    m_timer.start(5000);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(slotUpdateCPUUsage()));
    m_cpu_usage_rate = DEFAULT_CPU_RATE;
}


bool QGetCPUInfo::addMointorList(int pid)
{
    TProcessCPUInfo cpu = {0, DEFAULT_CPU_RATE};
    if (m_cpuMethod.get_process_time(pid, 0, &cpu.last_cpu))
    {
        return true;
    }
    m_cpuList.insert(pid,cpu);
    return false;
}

void QGetCPUInfo::removMointorList(int pid)
{
    m_cpuList.remove(pid);
}


void QGetCPUInfo::slotUpdateCPUUsage()
{
    QMap<int, TProcessCPUInfo>::iterator i;
    int idle_time = 0;
    int cpu_time = m_cpuMethod.get_all_time(&idle_time);
    int process_time = 0;
    m_cpu_usage_rate = (float)(idle_time - m_lastMomentIdleCPU) / (cpu_time - m_lastMomentCPU) * 100;

    for (i = m_cpuList.begin(); i != m_cpuList.end(); ++i)
    {
        qDebug() << i.key() << ":" << i.value().last_cpu;
        if (m_cpuMethod.get_process_time(i.key(), 0, &process_time))
        {
            emit signalPidNotExist(i.key());
            i.value().use_rate = DEFAULT_CPU_RATE;
        }
        else
        {
            i.value().use_rate = (float)(process_time - i.value().last_cpu) / (cpu_time - m_lastMomentCPU) * 100;
        }
        i.value().last_cpu = process_time;
    }
    m_lastMomentCPU = cpu_time;
    m_lastMomentIdleCPU = idle_time;
}
