#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <global.h>
namespace Ui {
class myregister;
}

class myregister : public QDialog
{
    Q_OBJECT

public:
    explicit myregister(QWidget *parent = nullptr);
    ~myregister();

private slots:
    void on_captcha_get_clicked();
    void slot_reg_mod_finish(ReqId id,QString res, ErrorCodes err);
    void on_sure_btn_clicked();

    void on_return_btn_clicked();
    void on_cancel_btn_clicked();

private:
    void initHttpHandlers();
    void showTip(QString str, bool b_ok);
    Ui::myregister *ui;
    QMap<ReqId, std::function<void (const QJsonObject&)>> _handlers;
    QMap<TipErr, QString> _tip_errs;
    bool checkUserValid();
    bool checkEmailValid();
    bool checkPassValid();
    bool checkVarifyValid();
    bool checkConfirmValid();
    void DelTipErr(TipErr te);
    void AddTipErr(TipErr te, QString tips);
    void ChangeTipPage();
    QTimer * _countdown_timer;
    int _countdown;
signals:
    void sigSwitchLogin();
};

#endif // REGISTER_H
