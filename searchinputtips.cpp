#include "searchinputtips.h"
#include "ui_searchinputtips.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QLineEdit>
#include <QDomDocument>
#include <QVector>


searchInputTips::searchInputTips(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::searchInputTips)
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
    QString xmlStr = formatXml(xmlByteArray);
    ui->textBrowser->setText(xmlByteArray);

    //分析xml
    analyXml(xmlStr);
    setUiListViewBySearch();
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
    urlTail = "output=xml&key=" + key;
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

void searchInputTips::analyXml(const QString& xml)
{
    QXmlStreamReader xmlReader(xml);
    //看需求清空Vector
    TipVec.clear();
    while (!xmlReader.atEnd()) {
        //一层循环寻找tip标签
        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "tip") {
                analyXmlTip(xmlReader);
            }
        }
        xmlReader.readNext();
    }
    return;
}

void searchInputTips::analyXmlTip(QXmlStreamReader& xmlReader)
{
    Tip aTip;
    xmlReader.readNext();
    while (!xmlReader.atEnd() && xmlReader.name() != "tip") {
        //二层循环找寻tip标签内部数据
        if (xmlReader.isStartElement()) {
            if (xmlReader.name() == "name") {
                aTip.name = xmlReader.readElementText();
            }
            else if (xmlReader.name() == "address") {
                aTip.address = xmlReader.readElementText();
            }
        }
        xmlReader.readNext();
    }
    TipVec.push_back(aTip);
}

void searchInputTips::setUiListViewBySearch()
{
    //清空原先listWidget内容
    while (ui->listWidget->count() > 0)
    {
        QListWidgetItem* item = ui->listWidget->takeItem(0);
        delete item;
    }

    //放入展示数据
    for (int i = 0; i < TipVec.size(); i++) {
        QString tipStr =
            TipVec[i].name + "\t"
            + QStringLiteral("地址:") + TipVec[i].address;
        QListWidgetItem* item = new QListWidgetItem(tipStr);
        ui->listWidget->addItem(item);
    }
}
