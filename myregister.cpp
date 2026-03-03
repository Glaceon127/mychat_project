#include "myregister.h"
#include "ui_myregister.h"

myregister::myregister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myregister)
{
    ui->setupUi(this);
}

myregister::~myregister()
{
delete ui;
}
