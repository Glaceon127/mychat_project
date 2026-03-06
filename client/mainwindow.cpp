#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    login_dialog = new login(this);
    setCentralWidget(login_dialog);
    //login_dialog->show();
    reg_dialog = new myregister(this);
    connect(login_dialog, &login::switchRegister, this, &MainWindow::SlotSwitchReg);
    login_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    reg_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    reg_dialog->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
//    if(login_dialog){
//        delete login_dialog;
//        login_dialog = nullptr;
//    }
//    if(reg_dialog){
//        delete reg_dialog;
//        reg_dialog = nullptr;
//    }
}

void MainWindow::SlotSwitchReg()
{
    login_dialog->hide();
    setCentralWidget(reg_dialog);
    reg_dialog->show();
}

