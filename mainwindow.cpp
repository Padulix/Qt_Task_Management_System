// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QMessageBox>
#include <QInputDialog>
#include <QTimer>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //  form splash
    //  FormSplash * ui_splash = new FormSplash(this);
    //  ui_splash->show();
    //  QTimer::singleShot(5000, ui_splash, SLOT(close()));

    // needed for list_view
    unfinished_model = new QStandardItemModel(this);
    ui->listView_unfinished->setDragEnabled(true);
    ui->listView_unfinished->setAcceptDrops(true);
    ui->listView_unfinished->setDropIndicatorShown(true);
    ui->listView_unfinished->setDefaultDropAction(Qt::MoveAction);
    ui->listView_unfinished->setModel(unfinished_model);

    in_progress_model = new QStandardItemModel(this);   
    ui->listView_in_progress->setDragEnabled(true);
    ui->listView_in_progress->setAcceptDrops(true);
    ui->listView_in_progress->setDropIndicatorShown(true);
    ui->listView_in_progress->setDefaultDropAction(Qt::MoveAction);
    ui->listView_in_progress->setModel(in_progress_model);

    finished_model= new QStandardItemModel(this);   
    ui->listView_finished->setDragEnabled(true);
    ui->listView_finished->setAcceptDrops(true);
    ui->listView_finished->setDropIndicatorShown(true);
    ui->listView_finished->setDefaultDropAction(Qt::MoveAction);
    ui->listView_finished->setModel(finished_model);


    // database

    database.read_data_from_database(vector_tasks);
    update_unfinished_listView();
    update_in_progress_listView();

  //  connects
  //  connect(ui->listView_unfinished, &QListView::clicked, this, &MainWindow::on_listView_unfinished_clicked);

}

MainWindow::~MainWindow()
{

    database.write_data_into_database(vector_tasks);
    database.close_database();
    delete ui;
    delete add_details_window;
}

void MainWindow::on_button_exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Exit Program"), tr("Do you really want to exit the program?"),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        close();
    }
}


void MainWindow::on_button_add_clicked()
{

    bool ok;
    QString text = QInputDialog::getText(this, tr("Add Task"),
                                         tr("Task description:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
        Task task;
        // ID will be initialized with a UUID
        task.set_task_id(QUuid::createUuid().toString(QUuid::WithoutBraces));
        task.set_task_description(text);
        // add the new task to the vector
        vector_tasks.push_back(task);
        update_unfinished_listView();
        qDebug() << "Task: " << task.get_task_description() << " added to unfinished. Status = " << task.get_task_status();
    }
}
/*
    int row = model->rowCount();
    model->insertRow(row,1);
    QModelIndex index = model->index(row);
    ui->listView->setCurrentIndex(index);
    ui->listView->edit(index);
*/

void MainWindow::on_button_unfinished_to_in_progress_clicked()
{
    QModelIndex index = ui->listView_unfinished->currentIndex();
    if (!index.isValid()) return;

    QString task_description = unfinished_model->data(index).toString();

    // Find the task in the vector_tasks and update its status
    for (Task &task : vector_tasks) {
        if (task.get_task_description() == task_description) {
            task.set_task_status(1);
            task.set_task_start_date(QDateTime::currentDateTime());
            qDebug() << "Task: " << task.get_task_description() << " moved to in_progress. Status = " << task.get_task_status();
            qDebug() << "Start Date is set to" << task.get_task_start_date();
            break;
        }
    }

    // Add task to in_progress_model
    int row = in_progress_model->rowCount();
    in_progress_model->insertRow(row);
    QModelIndex in_progress_index = in_progress_model->index(row, 0);
    in_progress_model->setData(in_progress_index, task_description);

    // Remove task from unfinished_model
    unfinished_model->removeRow(index.row());

    // Update the views
    update_unfinished_listView();
    update_in_progress_listView();

}

void MainWindow::on_button_in_progress_to_unfinished_clicked()
{
    QModelIndex index = ui->listView_in_progress->currentIndex();
    if (!index.isValid()) return;

    QString task_description = in_progress_model->data(index).toString();

    // Find the task in the vector_tasks and update its status
    for (Task &task : vector_tasks) {
        if (task.get_task_description() == task_description) {
            task.set_task_status(0); // Update status to unfinished
            // reset the start date
            task.set_task_start_date(QDateTime::currentDateTime());
            qDebug() << "Task: " << task.get_task_description() << " moved to unfinished. Status = " << task.get_task_status();
            break;
        }
    }

    // Add task to unfinished_model
    int row = unfinished_model->rowCount();
    unfinished_model->insertRow(row);
    QModelIndex unfinished_index = unfinished_model->index(row, 0);
    unfinished_model->setData(unfinished_index, task_description);

    // Remove task from in_progress_model
    in_progress_model->removeRow(index.row());

    // Update the views
    update_unfinished_listView();
    update_in_progress_listView();
}


void MainWindow::on_button_in_progress_to_finished_clicked()
{
    QModelIndex index = ui->listView_in_progress->currentIndex();
    if (!index.isValid()) return;

    QString task_description = in_progress_model->data(index).toString();

    // Find the task in the vector_tasks and update its status
    for (Task &task : vector_tasks) {
        if (task.get_task_description() == task_description) {
            task.set_task_status(2); // Update status to finished
            task.set_task_end_date(QDateTime::currentDateTime());
            qDebug() << "Task: " << task.get_task_description() << " moved to finished. Status = " << task.get_task_status();
            break;
        }
    }

    // Add task to finished_model
    int row = finished_model->rowCount();
    finished_model->insertRow(row);
    QModelIndex finished_index = finished_model->index(row, 0);
    finished_model->setData(finished_index, task_description);

    // Remove task from in_progress_model
    in_progress_model->removeRow(index.row());

    // Update the views
    update_in_progress_listView();
    update_finished_listView();
}


void MainWindow::on_button_finished_to_in_progress_clicked()
{
    QModelIndex index = ui->listView_finished->currentIndex();
    if (!index.isValid()) return;

    QString task_description = finished_model->data(index).toString();

    // Find the task in the vector_tasks and update its status
    for (Task &task : vector_tasks) {
        if (task.get_task_description() == task_description) {
            task.set_task_status(1); // Update status to in progress
            // reset the end_date
            task.set_task_end_date(task.get_task_start_date());
            qDebug() << "Task: " << task.get_task_description() << " moved to in_progress. Status = " << task.get_task_status();
            break;
        }
    }

    // Add task to in_progress_model
    int row = in_progress_model->rowCount();
    in_progress_model->insertRow(row);
    QModelIndex in_progress_index = in_progress_model->index(row, 0);
    in_progress_model->setData(in_progress_index, task_description);

    // Remove task from finished_model
    finished_model->removeRow(index.row());

    // Update the views
    update_in_progress_listView();
    update_finished_listView();
}


void MainWindow::update_unfinished_listView()
{
    unfinished_model->clear();
    for (const Task &task : vector_tasks) {
        if(task.get_task_status() == 0)
        {
            QStandardItem *item = new QStandardItem(task.get_task_description());
            unfinished_model->appendRow(item);
        }
    }
}

void MainWindow::update_in_progress_listView()
{
    in_progress_model->clear();
    for (const Task &task : vector_tasks)
    {
        if (task.get_task_status()== 1)
        {
            QStandardItem *item = new QStandardItem(task.get_task_description());
            in_progress_model->appendRow(item);
        }
    }
}

void MainWindow::update_finished_listView()
{
    finished_model->clear();
    for (const Task &task : vector_tasks) {
        if (task.get_task_status() == 2) {
            QStandardItem *item = new QStandardItem(task.get_task_description());
            finished_model->appendRow(item);
        }
    }
}

void MainWindow::on_button_details_clicked()
{
        QModelIndex index_unfinished = ui->listView_unfinished->currentIndex();
        QModelIndex index_in_progress = ui->listView_in_progress->currentIndex();

        if (!index_unfinished.isValid() && !index_in_progress.isValid()) {
            QMessageBox::information(this, tr("No Task Selected"), tr("Please select a task from 'unfinished' or 'in_progress' if you want to edit details."));
            return;
        }

        QString task_description;
        int selected_task_index = -1;

        if (index_unfinished.isValid()) {
            task_description = unfinished_model->data(index_unfinished).toString();
        } else
        {
            task_description = in_progress_model->data(index_in_progress).toString();
        }

        // searching in the vector for for the task
        for (int i = 0; i < vector_tasks.size(); ++i)
        {
            if (vector_tasks[i].get_task_description() == task_description) {
                selected_task_index = i;
                break;
            }
        }

        if (selected_task_index == -1) {
            QMessageBox::warning(this, tr("Task Not Found"), tr("The selected task could not be found."));
            return;
        }

        // open the details.ui
        if (!add_details_window) {
            add_details_window = new Details(this);
        }

        add_details_window->set_task(vector_tasks[selected_task_index]);

        if (add_details_window->exec() == QDialog::Accepted)
        {
            Task updated_task = add_details_window->get_task();
            vector_tasks[selected_task_index] = updated_task;
        }
        update_unfinished_listView();
        update_in_progress_listView();
    }

void MainWindow::on_listView_unfinished_clicked(const QModelIndex &index)
{
    current_task_index = index.row();

}


void MainWindow::on_listView_in_progress_clicked(const QModelIndex &index)
{
    current_task_index = index.row();

}



void MainWindow::on_button_delete_clicked()
{
        // Get the index of the selected task in your UI
        QModelIndex index_unfinished = ui->listView_unfinished->currentIndex();
        QModelIndex index_in_progress = ui->listView_in_progress->currentIndex();

        if (!index_unfinished.isValid() && !index_in_progress.isValid()) {
            QMessageBox::information(this, tr("Not allowed to delete a finished task"), tr("If you want to delete a task, you have to set it to unfinished or in progress."));
            return;
        }

        int selected_task_index = -1;
        QString task_description;

        // Determine which list the selected task belongs to
        if (index_unfinished.isValid()) {
            task_description = unfinished_model->data(index_unfinished).toString();
        } else {
            task_description = in_progress_model->data(index_in_progress).toString();
        }

        // Find the task in the vector_tasks and get its index
        for (int i = 0; i < vector_tasks.size(); ++i) {
            if (vector_tasks[i].get_task_description() == task_description) {
                selected_task_index = i;
                break;
            }
        }

        if (selected_task_index == -1) {
            QMessageBox::warning(this, tr("Task Not Found"), tr("The selected task could not be found."));
            return;
        }

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Delete Task"), tr("Do you really want to delete the task?"),
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            // Remove the selected task from the vector_tasks
            vector_tasks.erase(vector_tasks.begin() + selected_task_index);

            // Update your UI or any associated data structures if necessary
            if (index_unfinished.isValid()) {
                unfinished_model->removeRow(index_unfinished.row());
            } else {
                in_progress_model->removeRow(index_in_progress.row());
            }

        QMessageBox::information(this, tr("Task Deleted"), tr("The task has been deleted."));
    }
 }



