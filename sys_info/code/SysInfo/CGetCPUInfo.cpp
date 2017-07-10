#include "CGetCPUInfo.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

CGetCPUInfo::CGetCPUInfo()
{
}

char * CGetCPUInfo::skip_token(const char *p)
{
    while (isspace(*p)) p++;
    while (*p && !isspace(*p)) p++;
    return (char *)p;
}

int CGetCPUInfo::get_sys_mem(char *mem)
{
    unsigned long tm,fm,bm,cm,ts,fs;
    char buffer[4096+1];
    int fd, len;
    char *p;
    //fd = open("/proc/meminfo", O_RDONLY);
    if((fd = open("/proc/meminfo", O_RDONLY)) < 0)
    {
        perror("open /proc/meminfo file failed");
        return (1);
    }
    len = read(fd, buffer, sizeof(buffer)-1);
    close(fd);

    buffer[len] = '\0';
    p = buffer;
    p = skip_token(p);
    tm = strtoul(p, &p, 10); /* total memory */

    p = strchr(p, '\n');
    p = skip_token(p);
    fm= strtoul(p, &p, 10); /* free memory */

    p = strchr(p, '\n');
    p = skip_token(p);
    bm= strtoul(p, &p, 10); /* buffer memory */

    p = strchr(p, '\n');
    p = skip_token(p);
    cm= strtoul(p, &p, 10); /* cached memory */

    for(int i = 0; i< 8 ;i++)
    {
        p++;
        p = strchr(p, '\n');
    }
    p = skip_token(p);
    ts= strtoul(p, &p, 10); /* total swap */

    p = strchr(p, '\n');
    p = skip_token(p);
    fs= strtoul(p, &p, 10); /* free swap */

    sprintf(mem,"Mem: %luk total,%luk used,%luk free,%luk buffer\nSwap: %luk total,%luk used, %luk  free,%luk cached\n",
            tm,tm-fm,fm,bm,ts,ts-fs,fs,cm);
    //printf("%s\n",mem);
    return tm;
}

int CGetCPUInfo::get_phy_mem(int pid,char* ph)
{
    char file[64] = {0};//文件名
    FILE *fd;         //定义文件指针fd
    char line_buff[256] = {0};  //读取行的缓冲区
    sprintf(file,"/proc/%d/status",pid);

    //fd = fopen (file, "r");
    if((fd = fopen (file, "r"))==NULL)
    {
        printf("Can't open file\n");
        exit(1);
    }

    //获取vmrss:实际物理内存占用
    int i;
    char name1[32];//存放项目名称
    int vmrss;//存放内存峰值大小
    char name2[32];
    int vmsize;
    for (i=0;i<12;i++)
    {
        fgets (line_buff, sizeof(line_buff), fd);
    }
    fgets (line_buff, sizeof(line_buff), fd);
    sscanf (line_buff, "%s %d", name2,&vmsize);
    //fprintf (stderr, "====%s：%d====\n", name2,vmsize);

    for (i=0;i<2;i++)
    {
         fgets (line_buff, sizeof(line_buff), fd);
    }

    fgets (line_buff, sizeof(line_buff), fd);//读取VmRSS这一行的数据,VmRSS在第15行
    sscanf (line_buff, "%s %d", name1,&vmrss);

    //fprintf (stderr, "====%s：%d====\n", name1,vmrss);

    fclose(fd);     //关闭文件fd
    sprintf(ph,"VIRT=%dKB RES=%dKB",vmsize,vmrss);
    //printf("=+=+=%s\n",ph);
    return vmrss;
}

bool CGetCPUInfo::get_process_time(int pid,int tid, int *p_cpu)
{
    char szStatStr[1024];
    char pname[64];
    char state;
    int ppid,pgrp,session,tty,tpgid;
    unsigned int    flags,minflt,cminflt,majflt,cmajflt;
    int utime,stime,cutime,cstime,counter,priority;
    unsigned int  timeout,itrealvalue;
    int           starttime;
    unsigned int  vsize,rss,rlim,startcode,endcode,startstack,kstkesp,kstkeip;
    int signal,blocked,sigignore,sigcatch;
    unsigned int  wchan;

    char file_stat [1024];
    if(tid==0)
    {
        sprintf( file_stat,"/proc/%d/stat",pid );
    }else if(tid!=-1)
    {
        sprintf( file_stat,"/proc/%d/task/%d/stat",pid,tid );
    }

    //printf("open file %s\n",file_stat);

    FILE* fid;
    //fid = fopen(file_stat,"r");
    if((fid = fopen (file_stat, "r"))==NULL)
    {
        printf("Can't open file\n");
        return true;
    }

    fgets(szStatStr,sizeof(szStatStr),fid);

    fclose(fid);

    //printf("+++szStatStr=%s\n",szStatStr);

    sscanf (szStatStr, "%u", &pid);
    char  *sp, *t;
    sp = strchr (szStatStr, '(') + 1;
    t = strchr (szStatStr, ')');
    strncpy (pname, sp, t - sp);

    sscanf (t + 2, "%c %d %d %d %d %d %u %u %u %u %u %d %d %d %d %d %d %u %u %d %u %u %u %u %u %u %u %u %d %d %d %d %u",
             /*     1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33*/
                    &state,&ppid,&pgrp,&session,&tty,&tpgid,&flags,&minflt,&cminflt,&majflt,&cmajflt,&utime,&stime,&cutime,&cstime,&counter,
                    &priority,&timeout,&itrealvalue,&starttime,&vsize,&rss,&rlim,&startcode,&endcode,&startstack,
                    &kstkesp,&kstkeip,&signal,&blocked,&sigignore,&sigcatch,&wchan);
    /*printf("-------%c %d %d %d %d %d %u %u %u %u %u -%d -%d -%d -%d %d %d %u %u %d %u %u %u %u %u %u %u %u %d %d %d %d %u",
                    state,ppid,pgrp,session,tty,tpgid,flags,minflt,cminflt,majflt,cmajflt,utime,stime,cutime,cstime,counter,
                    priority,timeout,itrealvalue,starttime,vsize,rss,rlim,startcode,endcode,startstack,
                    kstkesp,kstkeip,signal,blocked,sigignore,sigcatch,wchan);
    */
    //printf("+++%lu %lu %lu %lu\n",utime,stime,cutime,cstime);

    *p_cpu=utime+stime+cutime+cstime;
    return false;
}

int CGetCPUInfo::get_all_time(unsigned int *p_idle)
{
    FILE *fp;
    char buf[128];
    char tcpu[7];
    unsigned int  user,nice,sys,idle,iowait,irq,softirq,steal;
    unsigned int  all;

    if((fp = fopen ("/proc/stat", "r"))==NULL)
    {
        printf("Can't open /proc/stat file\n");
        return (1);
    }

    fgets(buf,sizeof(buf),fp);

    sscanf(buf,"%s%d%d%d%d%d%d%d%d",tcpu,&user,&nice,&sys,&idle,&iowait,&irq,&softirq,&steal);
    fclose(fp);

    printf("%s,%d,%d,%d,%d,%d,%d,%d,%d\n",tcpu,user,nice,sys,idle,iowait,irq,softirq,steal);

    all = user+nice+sys+idle+iowait+irq+softirq+steal;

    return all;
}

int CGetCPUInfo::get_all_time()
{
    int idle = 0;
    return get_all_time(&idle);
}
