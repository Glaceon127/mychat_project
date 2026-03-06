#include "myregister.h"
#include "ui_myregister.h"
#include "global.h"
#include "httpmgr.h"

myregister::myregister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myregister)
{
    ui->setupUi(this);
    ui->pass_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_edit->setEchoMode(QLineEdit::Password);
    ui->err_tip->setProperty("state","normal");
    repolish(ui->err_tip);
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &myregister::slot_reg_mod_finish);
    initHttpHandlers();
}

myregister::~myregister()
{
delete ui;
}

void myregister::on_captcha_get_clicked()
{
    auto email = ui->email_edit->text();
    QRegularExpression regex(R"(^[a-zA-Z0-9_%+-]+(\.[a-zA-Z0-9_%+-]+)*@[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)*\.[a-zA-Z]{2,}$)");
    bool match = regex.match(email).hasMatch();
    if(match){

    }else{
        showTip(tr("邮箱地址不正确"), false);
    }
}

void myregister::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        showTip(tr("网络请求错误"),false);
        return;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if(jsonDoc.isNull()){
        showTip(tr("json解析失败"),false);
        return;
    }
    if(!jsonDoc.isObject()){
        showTip(tr("json解析失败"),false);
        return;
    }

    _handlers[id](jsonDoc.object());
    return;
}

void myregister::initHttpHandlers()
{
    //注册获取验证码回包的逻辑
    _handlers.insert(ReqId::ID_GET_CAPTCHA, [this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已发送"),true);
        qDebug() << "email is" << email;
    });
}

void myregister::showTip(QString str, bool b_ok)
{
    if(b_ok){
        ui->err_tip->setProperty("state","normal");
    }else{
        ui->err_tip->setProperty("state","err");
    }
    ui->err_tip->setText(str);
    repolish(ui->err_tip);
}
