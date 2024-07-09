// details.cpp
#include "details.h"
#include "ui_details.h"
#include <QMessageBox>



Details::Details(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Details)
{
    ui->setupUi(this);


   // connect(ui->date_time_edit_start_date, &QDateTimeEdit::dateChanged, this, &Details::on_date_time_edit_start_date_dateChanged);

}

Details::~Details()
{
    delete ui;
}

void Details::on_button_save_clicked()
{
    current_task.set_task_duration(ui->lineEdit_duration->text().toInt());
    current_task.set_task_start_date(ui->date_time_edit_start_date->dateTime());
    current_task.set_task_comments(ui->textEdit_comments->toPlainText());

    // close the ialog with QDialog::Accepted, could add a question later
    accept();
}

void Details::on_button_exit_clicked()
{
    //
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Exit Details Window"), tr("Do you want to exit the Details Window?"),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        close();
    }
}


void Details::set_task(const Task &task)
{
    current_task = task;

    ui->lineEdit_id->setText(task.get_task_id());
    ui->lineEdit_description->setText(task.get_task_description());
    ui->lineEdit_status->setText(QString::number(task.get_task_status()));

    ui->lineEdit_duration->setText(QString::number(task.get_task_duration()));
    ui->date_time_edit_start_date->setDateTime(task.get_task_start_date());
    ui->textEdit_comments->setText(task.get_task_comments());
    ui->date_time_edit_end_date->setDateTime(task.get_task_end_date());



}

Task Details::get_task() const
{
    Task updated_task = current_task;
    updated_task.set_task_duration(ui->lineEdit_duration->text().toInt());
    updated_task.set_task_start_date(ui->date_time_edit_start_date->dateTime());
    updated_task.set_task_comments(ui->textEdit_comments->toPlainText());
    updated_task.set_task_end_date(updated_task.get_task_start_date().addSecs(updated_task.get_task_duration() * 3600));
    return updated_task;

}


void Details::on_button_reset_start_date_clicked()
{

    current_task.set_task_start_date(QDateTime::currentDateTime());
    ui->date_time_edit_start_date->setDateTime(current_task.get_task_start_date());

}


void Details::on_button_reset_end_date_clicked()
{
    current_task.set_task_end_date(QDateTime::currentDateTime());

}


void Details::on_date_time_edit_start_date_dateChanged(const QDateTime &datetime)
{
    // Check if the start date is in the future
    if (datetime > QDateTime::currentDateTime())
    {
        // Set the end date to be the same as the start date initially
        ui->date_time_edit_end_date->setDateTime(datetime);
    }
}





