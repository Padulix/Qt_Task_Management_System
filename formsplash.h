#ifndef FORMSPLASH_H
#define FORMSPLASH_H

#include <QWidget>
#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class FormSplash;
}

class FormSplash : public QDialog
{
    Q_OBJECT

public:
    explicit FormSplash(QWidget *parent = nullptr);
    ~FormSplash();


private:
    Ui::FormSplash *ui;
};

#endif // FORMSPLASH_H
