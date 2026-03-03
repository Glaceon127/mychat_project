#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>

namespace Ui {
class myregister;
}

class myregister : public QDialog
{
    Q_OBJECT

public:
    explicit myregister(QWidget *parent = nullptr);
    ~myregister();

private:
    Ui::myregister *ui;
};

#endif // REGISTER_H
