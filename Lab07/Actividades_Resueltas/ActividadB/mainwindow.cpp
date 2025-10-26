#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mTasks()
{
    ui->setupUi(this);

    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask()
{
    Task* task = new Task(this);
    mTasks.append(task);

    connect(task, &Task::removed, this, &MainWindow::removeTask);

    ui->tasksLayout->addWidget(task);

    qDebug() << "Tarea agregada. Total:" << mTasks.size();
}

void MainWindow::removeTask(Task* task)
{
    mTasks.removeOne(task);    // quitar del vector
    task->deleteLater();       // liberar memoria
    qDebug() << "Tarea eliminada. Quedan:" << mTasks.size();
}
