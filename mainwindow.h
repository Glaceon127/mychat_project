#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "myregister.h"
/***************************************************************
 * @file      mainwindow.h
 * @brief     主窗口
 *
 * @author    Glaceon
 * @date      2026/03/03
 * @history
 ***************************************************************/
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void SlotSwitchReg();
private:
    Ui::MainWindow *ui;
    login * login_dialog;
    myregister * reg_dialog;
};
#endif // MAINWINDOW_H
