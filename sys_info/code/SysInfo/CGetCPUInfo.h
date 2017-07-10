#ifndef CGETCPUINFO_H
#define CGETCPUINFO_H

class CGetCPUInfo
{
public:
    CGetCPUInfo();
    int get_sys_mem(char *mem);
    int get_phy_mem(int pid, char *ph);
    bool get_process_time(int pid, int tid, int *p_cpu);
    int get_all_time(unsigned int *p_idle);
    int get_all_time();
    char *skip_token(const char *p);
};

#endif // CGETCPUINFO_H
