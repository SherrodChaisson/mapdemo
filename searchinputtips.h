#ifndef SEARCHINPUTTIPS_H
#define SEARCHINPUTTIPS_H

#include <QMainWindow>
#include <QString>
#include <QtXml>
#include <QVector>

namespace Ui {
class searchInputTips;
}

class Tip {
public:
    Tip(QString name = "Name Empty", QString address = "Address Empty") {
        this->name = name;
        this->address = address;
    }
    QString name;
    QString address;
};

class searchInputTips : public QMainWindow
{
    Q_OBJECT

public:
    explicit searchInputTips(QWidget *parent = nullptr);
    ~searchInputTips();



    void whenLineEditChange(const QString&);
    QString spliceUrl();
    void initFixedUrl();
    QByteArray getReplay(const QString& urlstr);
    void analyXml(const QString& xml);
    void analyXmlTip(QXmlStreamReader& xmlReader);
    void setUiListViewBySearch();


private:
    Ui::searchInputTips *ui;
    QString key;
    QString urlHead;
    QString urlTail;
    QVector<Tip> TipVec;
    QString formatXml(const QByteArray& xml);


};

#endif // SEARCHINPUTTIPS_H
