#include "edittask.h"
#include "ui_edittask.h"

EditTask::EditTask(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EditTask)
{
    ui->setupUi(this);
}

EditTask::~EditTask()
{
    delete ui;
}
