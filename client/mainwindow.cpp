#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myregister.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    login_dialog = new login(this);
    login_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(login_dialog);
    //login_dialog->show();
    connect(login_dialog, &login::switchRegister, this, &MainWindow::SlotSwitchReg);
    connect(login_dialog, &login::switchReset, this, &MainWindow::SlotSwitchReset);

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
    reg_dialog = new myregister(this);
    reg_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    connect(reg_dialog, &myregister::sigSwitchLogin, this, &MainWindow::SlotSwitchLogin);
    setCentralWidget(reg_dialog);
    login_dialog->hide();
    reg_dialog->show();
}

void MainWindow::SlotSwitchLogin()
{
    //创建一个CentralWidget, 并将其设置为MainWindow的中心部件
    login_dialog = new login(this);
    login_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(login_dialog);

    reg_dialog->hide();
    login_dialog->show();
    //连接登录界面注册信号
    connect(login_dialog, &login::switchRegister, this, &MainWindow::SlotSwitchReg);
    //连接登录界面忘记密码信号
    connect(login_dialog, &login::switchReset, this, &MainWindow::SlotSwitchReset);
}

void MainWindow::SlotSwitchReset()
{
    //创建一个CentralWidget, 并将其设置为MainWindow的中心部件
    _reset_dlg = new ResetDialog(this);
    _reset_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_reset_dlg);

    login_dialog->hide();
    _reset_dlg->show();
    //注册返回登录信号和槽函数
    connect(_reset_dlg, &ResetDialog::switchLogin, this, &MainWindow::SlotSwitchLogin2);
}

void MainWindow::SlotSwitchLogin2()
{
    //创建一个CentralWidget, 并将其设置为MainWindow的中心部件
    login_dialog = new login(this);
    login_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(login_dialog);

    _reset_dlg->hide();
    login_dialog->show();
    //连接登录界面忘记密码信号
    connect(login_dialog, &login::switchReset, this, &MainWindow::SlotSwitchReset);
    //连接登录界面注册信号
    connect(login_dialog, &login::switchRegister, this, &MainWindow::SlotSwitchReg);
}
