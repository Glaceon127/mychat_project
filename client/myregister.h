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

private:
    void initHttpHandlers();
    void showTip(QString str, bool b_ok);
    Ui::myregister *ui;
    QMap<ReqId, std::function<void (const QJsonObject&)>> _handlers;
};

#endif // REGISTER_H
