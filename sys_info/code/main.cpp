#include <QCoreApplication>
//#include "ShrMem/QShrMemPrint.h"
#include "SysInfo/QSysMem.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //QShrMemPrint printShrMem;
    QSysMem printSysMem;
    //printShrMem.startPrint();
    printSysMem.testPrint();

    return a.exec();
}


