#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::miSlotPersonalizado);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::miSlotPersonalizado()
{
    qDebug() << "Slot corresponde al clic en el boton ...";
}
