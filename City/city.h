#ifndef CITY_H
#define CITY_H

#include <QWidget>
#include <QPainter>
#include <QPen>
QT_BEGIN_NAMESPACE
namespace Ui { class City; }
QT_END_NAMESPACE

class City : public QWidget
{
    Q_OBJECT

public:
    City(QWidget *parent = nullptr);
    ~City();


private:
    Ui::City *ui;
    void paintEvent(QPaintEvent *);
};
#endif // CITY_H
