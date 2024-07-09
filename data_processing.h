#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVector>

#include "task.h"


class Data_processing
{

private:

    // open the database - check for errors
    QSqlDatabase db;
    QString connection_string;

    QString server_name{"DESKTOP-VI43NSN\\SQLEXPRESS"};
    QString database_name{"task_management"};

    // pointer !
    QSqlQuery * query_read_data;
    QSqlQuery * query_write_data;


    // read from a database - check for errors
    // load entries into the local vector or in a map
    // only write new entrys into the database when you finish the programm, db performance
    // option to see finished tasks under the button_details
    // optional - delete data from database ?


public:
    Data_processing();
    void read_data_from_database(QVector<Task> &vector_tasks);
    void write_data_into_database(const QVector<Task> &vector_tasks);
    void close_database();
};

#endif // DATA_PROCESSING_H
