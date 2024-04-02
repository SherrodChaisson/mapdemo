#include "searchinputtips.h"
#include <QApplication>
#include <QDebug>
#include <QSslSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    searchInputTips w;
    w.show();

    return a.exec();
}
