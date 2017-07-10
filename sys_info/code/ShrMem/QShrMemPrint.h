#ifndef QSHRMEMPRINT_H
#define QSHRMEMPRINT_H

#include <QObject>
#include <QTimer>

class QShrMemPrint : public QObject
{
    Q_OBJECT
public:
    explicit QShrMemPrint(QObject *parent = 0);
    void startPrint();
    void stopPrint();

private:
    QTimer m_print_timer;

signals:
    
public slots:
    void slotPrintShrMem();
    
};

#endif // QSHRMEMPRINT_H
