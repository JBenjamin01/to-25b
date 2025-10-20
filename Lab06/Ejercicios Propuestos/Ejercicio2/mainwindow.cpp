#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Conectamos el botón a nuestro slot
    connect(ui->btnShow, &QPushButton::clicked,
            this, &MainWindow::updateLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateLabel()
{
    QString texto = ui->lineEdit->text();
    ui->labelResult->setText("Texto ingresado: " + texto);
}
