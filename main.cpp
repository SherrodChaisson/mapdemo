#include "searchinputtips.h"
#include <QApplication>
#include <QDebug>
#include <QSslSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    qDebug()<<"QSslSocket="<<QSslSocket::sslLibraryBuildVersionString();
//    qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();


    searchInputTips w;
    w.show();

    return a.exec();
}
