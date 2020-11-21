#include "city.h"
#include "ui_city.h"
City::City(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::City)
{
    ui->setupUi(this);
}

City::~City()
{
    delete ui;
}
void City::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black,3));
    painter.drawLine(800,320,920,40);
    painter.drawLine(800,320,1280,250);
    painter.drawLine(1100,210,1280,250);
    painter.drawLine(1320,540,1280,250);
    painter.drawLine(1320,540,1050,600);
    painter.drawLine(950,550,1050,600);
    painter.drawLine(950,550,850,460);
    painter.drawLine(800,320,850,460);
    painter.drawLine(800,320,450,390);
    painter.drawLine(230,350,450,390);
    painter.drawLine(570,150,450,390);
    painter.drawLine(570,150,920,40);
    painter.drawLine(1280,250,920,40);
}
