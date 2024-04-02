#ifndef SEARCHINPUTTIPS_H
#define SEARCHINPUTTIPS_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class searchInputTips;
}

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

private:
    Ui::searchInputTips *ui;
    QString key;
    QString urlHead;
    QString urlTail;
    QString formatXml(const QByteArray& xml);

};

#endif // SEARCHINPUTTIPS_H
