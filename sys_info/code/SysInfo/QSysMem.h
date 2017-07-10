#ifndef QSYSMEM_H
#define QSYSMEM_H

#include <QObject>
#include "QRegisterProcess.h"
#include "CGetProcessInfo.h"
#include "CSysInfoElement.h"

class QSysMem : public QObject
{
    Q_OBJECT
public:
    explicit QSysMem(QObject *parent = 0);

    void testPrint();

    bool getProgramID(const std::string &srtProgramName, int *pid);
    bool add(QString processName);
private:
    void testPrint_sysMem(QList<CSysMemInfoElement> &sys_info);

private:
    QRegisterProcess m_registProcess;
    QMap<QString, CSysInfoElement> m_processInfo;

signals:
    
public slots:
    
};

#endif // QSYSMEM_H
