#ifndef TASK_H
#define TASK_H

#include <Qstring>
#include <QDate>
#include <Qvector>
#include <QUuid>

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>



class Task
{
private:
    //    primary key not null, will be initialized with a UUID ( Universal Unique Identifier 128-Bit Number )
    QString     task_id{""};
    //     Name of the task  must be set
    QString     task_description{""};
    //     duration of the task in hours
    int         task_duration{0};
    //	   datetime  at the start
    QDateTime   task_start_date{QDateTime::currentDateTime()};
    //	   datetime when the task is finished
    QDateTime   task_end_date{QDateTime::currentDateTime()};
    //	   will be set automatically   -- 0 = not finished, 1 = in progress, 2 = finished (enums)
    int         task_status{0};
    //	   additional comments
    QString     task_comments{""};

    // vector to store the tasks local
    // QVector<Task> vector_tasks{};

public:
    Task() ;
    Task(QString id,  QString description, int duration, QDateTime start_date, QDateTime end_date,  int status, QString comments );

    // setter methods
    void  set_task_id(QString id);
    void  set_task_description(QString description);
    void  set_task_duration(int duration );
    void  set_task_start_date(QDateTime start_date);
    void  set_task_end_date(QDateTime end_date);
    void  set_task_status(int status);
    void  set_task_comments(QString comments);

    // getter methods
    QString     get_task_id()                 const {  return task_id;          }
    QString     get_task_description()        const {  return task_description; }
    int         get_task_duration()           const {  return task_duration;    }
    QDateTime   get_task_start_date()         const {  return task_start_date;  }
    QDateTime   get_task_end_date()           const {  return task_end_date;    }
    int         get_task_status()             const {  return task_status;      }
    QString     get_task_comments()           const {  return task_comments;    }


    // task_start_date will be automatically set
    // finished()
    // task_end_date will be automatically set

};

#endif // TASK_H
