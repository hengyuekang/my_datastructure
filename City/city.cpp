#include "city.h"
#include "ui_city.h"
#include <QString>
#include <iostream>
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
    mymap.createGraph();
    QPainter painter(this);
//    create map
    painter.setPen(QPen(Qt::black,3));
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<11;j++)
        {
            if(mymap.Edge[i][j]!=0&&mymap.Edge[i][j]!=9999)
            {
                painter.drawLine(mymap.pos[i],mymap.pos[j]);
            }
        }
    }
}

void City::on_pushButton_6_clicked()
{
    QString input=ui->lineEdit->text();
    mymap.setStart(input.toInt());
}

void City::on_BFS_clicked()
{

}
