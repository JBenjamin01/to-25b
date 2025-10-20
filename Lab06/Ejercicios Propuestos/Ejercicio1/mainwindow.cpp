#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Los colores para la lista
    ui->listWidget->addItems({"Rojo", "Verde", "Azul", "Amarillo", "Negro"});

    // Aqui hago esto para conectar la señal del QListWidget con el slot personalizado
    connect(ui->listWidget, &QListWidget::itemClicked,
            this, &MainWindow::onColorSelected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onColorSelected()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    if (item) {
        ui->labelColor->setText("Color seleccionado: " + item->text());
    }
}
