#include <QCoreApplication>
#include <QStringList>
#include "foobar.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Foobar foo;
    QStringList list;
    list.append("bla");
    list.append("foobar");
    list.append("blorg");
    foo.MapThem(list);
    
    return a.exec();
}
