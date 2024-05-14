#include "MUSYNCSavDecode.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MUSYNCSavDecode w;
    w.show();
    return a.exec();
}
