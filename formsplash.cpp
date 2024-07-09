// formsplash.cpp
#include "formsplash.h"
#include "ui_formsplash.h"



FormSplash::FormSplash(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FormSplash)
{
    ui->setupUi(this);
}

FormSplash::~FormSplash()
{
    delete ui;
}


