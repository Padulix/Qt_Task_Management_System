#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QDebug>
#include <QFont>
#include <QLabel>
#include <QListView>
#include <QTableView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QWidget>
#include <QStringListModel>
#include <QDragMoveEvent>
#include <QList>

#include "data_processing.h"
#include "task.h"
#include "details.h"
#include"formsplash.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_add_clicked();
    // changed the name Details to Edit
    void on_button_details_clicked();
    void on_button_exit_clicked();
    void on_button_unfinished_to_in_progress_clicked();
    void on_button_in_progress_to_unfinished_clicked();
    void on_button_in_progress_to_finished_clicked();
    void on_button_finished_to_in_progress_clicked();
    void on_listView_unfinished_clicked(const QModelIndex &index);
    void on_listView_in_progress_clicked(const QModelIndex &index);
//  void drag_move_event(QDragMoveEvent *event);
    void on_button_delete_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Task> vector_tasks;
    Details *add_details_window = nullptr;
    QFont font_label_task_planer;
    Data_processing database;

    QStandardItemModel *unfinished_model;
    QStandardItemModel *in_progress_model;
    QStandardItemModel *finished_model;

    void update_unfinished_listView();
    void update_in_progress_listView();
    void update_finished_listView();

    Task get_selected_task() const;
    int current_task_index{-1};
};
#endif // MAINWINDOW_H
