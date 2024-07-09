#ifndef EDITTASK_H
#define EDITTASK_H

#include <QWidget>

namespace Ui {
class EditTask;
}

class EditTask : public QWidget
{
    Q_OBJECT

public:
    explicit EditTask(QWidget *parent = nullptr);
    ~EditTask();

private:
    Ui::EditTask *ui;
};

#endif // EDITTASK_H
