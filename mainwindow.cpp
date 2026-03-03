#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    login_dialog = new login();
    setCentralWidget(login_dialog);
    login_dialog->show();

    connect(login_dialog, &login::switchRegister, this, &MainWindow::SlotSwitchReg);
    reg_dialog = new myregister();
}

MainWindow::~MainWindow()
{
    delete ui;
    if(login_dialog){
        delete login_dialog;
        login_dialog = nullptr;
    }
    if(reg_dialog){
        delete reg_dialog;
        reg_dialog = nullptr;
    }
}

void MainWindow::SlotSwitchReg()
{
    setCentralWidget(reg_dialog);
    login_dialog->hide();
    reg_dialog->show();
}

