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

