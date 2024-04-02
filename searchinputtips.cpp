#include "searchinputtips.h"
#include "ui_searchinputtips.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QLineEdit>
#include <QDomDocument>

searchInputTips::searchInputTips(QWidget *parent)
    : QMainWindow(parent)
{
    ui->setupUi(this);
    initFixedUrl();

    connect(ui->lineEdit, &QLineEdit::textEdited,this, &searchInputTips::whenLineEditChange);
}

searchInputTips::~searchInputTips()
{
    delete ui;
}


void searchInputTips::whenLineEditChange(const QString&) {
    QByteArray xmlByteArray = getReplay(spliceUrl());
    ui->textBrowser->setText(xmlByteArray);
}

QString searchInputTips::spliceUrl()
{
    QString city = "city=020&";  //020代表广州
    QString inputKey = ui->lineEdit->text();
    QString keywords = "keywords=" + inputKey.toUtf8() + "&";
    QString url = urlHead + "?" + city + keywords + urlTail;
    return url;
}

void searchInputTips::initFixedUrl()
{
    key = "330428d3424fd7003888b252a8d8a734";
    urlHead = "http://restapi.amap.com/v3/assistant/inputtips";
    urlTail = "key=" + key;
}


QByteArray searchInputTips::getReplay(const QString& urlstr)
{
    //Qt获取网络数据 操作代码
    QNetworkAccessManager netManger;
    QUrl url(urlstr);
    QNetworkRequest netRequest(url);
    QNetworkReply* reply = netManger.get(netRequest);

    //等待请求完成
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    //判断错误
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Happend [reply] false:" << reply->error();
        return "reply error";
    }

    //返回
    QByteArray result = reply->readAll();
    delete reply;
    return result;
}

QString searchInputTips::formatXml(const QByteArray& xml)
{
    //QDomDocument可以整理格式
    QDomDocument doc;
    doc.setContent(xml);
    return doc.toString();
}


