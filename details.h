#ifndef DETAILS_H
#define DETAILS_H

#include <QDialog>
#include "task.h"

namespace Ui {
class Details;
}

class Details : public QDialog
{
    Q_OBJECT

public:
    explicit Details(QWidget *parent = nullptr);
    ~Details();

    void set_task(const Task &task);
    Task get_task() const;

private slots:

    void on_button_save_clicked();
    void on_button_exit_clicked();
    void on_button_reset_start_date_clicked();
    void on_button_reset_end_date_clicked();
    void on_date_time_edit_start_date_dateChanged(const QDateTime &datetime);

private:
    Ui::Details *ui;

    Task current_task;
};

#endif // DETAILS_H
