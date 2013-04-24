#ifndef FOOBAR_H
#define FOOBAR_H

#include <QObject>
#include <QStringList>
#include <QFutureWatcher>
#include <QtConcurrentMap>
#include <QObject>
#include <QStringList>
#include <QDebug>
#include <QTime>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

#include <functional>
#include <tr1/functional>

class Foobar : public QObject
{
    Q_OBJECT

public:
    explicit Foobar() : QObject(0) { }
    QString DoSomething(QString string) {
        Sleep(rand() % 1000 + 500);
        return string + ": done";
    }

    void MapThem(QStringList strings) {
        QObject::connect(&m_Watcher, SIGNAL(resultReadyAt(int)), this, SLOT(OnResultReadyAt(int)));
        QObject::connect(&m_Watcher, SIGNAL(finished()), this, SLOT(OnFinished()));
        QFuture<QString> res = QtConcurrent::mapped(strings, std::bind1st(std::mem_fun(&Foobar::DoSomething), this));
        m_Watcher.setFuture(res);
        foreach (QString str, res.results()) {
            qDebug() << str;
        }
    }

public slots:
    void OnResultReadyAt(int index) {
        qDebug() << "result ready at " << index << m_Watcher.resultAt(index);
    }
    void OnFinished() {
        qDebug() << "finished";
    }

signals:
    void Finished();

protected:
    QFutureWatcher<QString> m_Watcher;
};

#endif // FOOBAR_H
