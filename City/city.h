#ifndef CITY_H
#define CITY_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include "graph.h"
QT_BEGIN_NAMESPACE
namespace Ui { class City; }
QT_END_NAMESPACE

class City : public QWidget
{
    Q_OBJECT

public:
    City(QWidget *parent = nullptr);
    Graph mymap;
    void paintEvent(QPaintEvent *);
    ~City();


private slots:
    void on_pushButton_6_clicked();

    void on_BFS_clicked();

private:
    Ui::City *ui;

};
#endif // CITY_H
