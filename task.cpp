#include "task.h"


Task::Task()
{}

Task::Task(QString id,  QString description,int duration, QDateTime start_date, QDateTime end_date,  int status, QString comments )

{
    set_task_id(id);
    set_task_description(description);
    set_task_duration(duration);
    set_task_start_date(start_date);
    set_task_end_date(end_date);
    set_task_status(status);
    set_task_comments(comments);
}

// Task::

void  Task::set_task_id(QString id)
{
    task_id =  id;
}

void  Task::set_task_description(QString description)
{
    task_description = description;
}

void  Task::set_task_duration(int duration )
{
    task_duration = duration;
}

void  Task::set_task_start_date(QDateTime start_date)
{
    task_start_date = start_date;
}

void  Task::set_task_end_date(QDateTime end_date)
{
    task_end_date = end_date;
}

void  Task::set_task_status(int status)
{
    // enum status 0 == default , if you press the button left lower (in_progress_to_unfinished)
    // can be changed to 1 by ckick the button left_upper or in the ui->details,
    // if it is finished it will auto go to status == 2
    task_status = status;
}

void  Task::set_task_comments(QString comments)
{
    task_comments = comments;
}


