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
    void paintEvent(QPaintEvent *event);

private:
    Ui::City *ui;
};
#endif // CITY_H
