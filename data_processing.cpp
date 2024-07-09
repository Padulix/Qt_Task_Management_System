// data_processing.cpp
#include "data_processing.h"

Data_processing::Data_processing()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    connection_string = QString("Driver={SQL Server};Server=%1;Database=%2;Trusted_Connection=Yes;")
                            .arg(server_name).arg(database_name);

    db.setConnectOptions();
    db.setDatabaseName(connection_string);

    if(!db.open())
    {
        qDebug() <<db.lastError().text();
        return;
    }else
    {
        qDebug() <<"Database opened";
    }
}


void Data_processing::read_data_from_database(QVector<Task> &vector_tasks)
{
    query_read_data = new QSqlQuery(db);

    if (!query_read_data->exec("select * from tasks")) {
        qDebug() << "Error executing:" << query_read_data->lastError().text();
        return;
    }

    // Prepare the SELECT statement to retrieve tasks with status 0 or 1
    query_read_data->prepare("SELECT * FROM tasks WHERE task_status IN (0, 1)");

    // Execute the query
    if (!query_read_data->exec()) {
        qDebug() << "Error executing query:" << query_read_data->lastError().text();
        return;
    }

    while (query_read_data->next())
    {
        Task task;
        task.set_task_id(query_read_data->value("task_id").toString());
        task.set_task_description(query_read_data->value("task_description").toString());
        task.set_task_duration(query_read_data->value("task_duration").toInt());
        task.set_task_start_date(query_read_data->value("task_start_date").toDateTime());
        task.set_task_end_date(query_read_data->value("task_end_date").toDateTime());
        task.set_task_status(query_read_data->value("task_status").toInt());
        task.set_task_comments(query_read_data->value("task_comments").toString());

        // add to the vector
        vector_tasks.push_back(task);
    }
}

void Data_processing::write_data_into_database(const QVector<Task> &vector_tasks)
{
    query_write_data = new QSqlQuery(db);

   //  query_write_data->exec("SET IDENTITY_INSERT tasks ON");

    // Prepare the update statement
    query_write_data->prepare(
        "MERGE INTO tasks AS target "
        "USING (SELECT :task_id AS task_id, :task_description AS task_description, :task_duration AS task_duration, "
        ":task_start_date AS task_start_date, :task_end_date AS task_end_date, :task_status AS task_status, "
        ":task_comments AS task_comments) AS source "
        "ON (target.task_id = source.task_id) "
        "WHEN MATCHED THEN "
        "UPDATE SET "
        "task_description = source.task_description, "
        "task_duration = source.task_duration, "
        "task_start_date = source.task_start_date, "
        "task_end_date = source.task_end_date, "
        "task_status = source.task_status, "
        "task_comments = source.task_comments "
        "WHEN NOT MATCHED THEN "
        "INSERT (task_id, task_description, task_duration, task_start_date, task_end_date, task_status, task_comments) "
        "VALUES (source.task_id, source.task_description, source.task_duration, source.task_start_date, source.task_end_date, source.task_status, source.task_comments);"
        );

    for (const Task &task : vector_tasks)
    {
        query_write_data->bindValue(":task_id", task.get_task_id());
        query_write_data->bindValue(":task_description", task.get_task_description());
        query_write_data->bindValue(":task_duration", task.get_task_duration());
        query_write_data->bindValue(":task_start_date", task.get_task_start_date());
        query_write_data->bindValue(":task_end_date", task.get_task_end_date());
        query_write_data->bindValue(":task_status", task.get_task_status());
        query_write_data->bindValue(":task_comments", task.get_task_comments());


        if (!query_write_data->exec()) {
            qDebug() << "Error inserting task:" << query_write_data->lastError().text();
            throw std::runtime_error("Data could not be written into the database");
        }
    }
  //  query_write_data->exec("SET IDENTITY_INSERT tasks OFF");

    qDebug() << "Data written into database successfully";
}

void Data_processing::close_database()
{

    db.close();
    qDebug() << "Database closed";
    // delete pointers
    delete query_read_data;
    delete query_write_data;
}

