#ifndef QREGISTERPROCESS_H
#define QREGISTERPROCESS_H

#include <QObject>
#include <QMap>

class QRegisterProcess : public QObject
{
    Q_OBJECT
public:
    explicit QRegisterProcess(QObject *parent = 0);
    
    bool add(QString processName);
    QList<int> getRegisterPid();

private:
    bool getProgramID(const std::string &srtProgramName, int *pid);

public:
    QMap<QString, int> m_process;

signals:
    
public slots:
    
};

#endif // QREGISTERPROCESS_H
