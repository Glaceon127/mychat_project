#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "global.h"
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private:
    Ui::login *ui;
    void initHead();
    bool checkUserValid();
    bool checkPwdValid();
    void AddTipErr(TipErr te,QString tips);
    void DelTipErr(TipErr te);
    QMap<TipErr, QString> _tip_errs;
    void showTip(QString str,bool b_ok);
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
public slots:
    void slot_forget_pwd();
signals:
    void switchRegister();
    void switchReset();
private slots:
    void on_login_btn_clicked();
};

#endif // LOGIN_H
