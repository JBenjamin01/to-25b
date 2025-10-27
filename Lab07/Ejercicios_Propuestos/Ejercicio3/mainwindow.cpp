#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // País -> (Idioma, Capital)
    paises.insert("Perú", {"Español", "Lima"});
    paises.insert("México", {"Español", "Ciudad de México"});
    paises.insert("Francia", {"Francés", "París"});
    paises.insert("Japón", {"Japonés", "Tokio"});
    paises.insert("Alemania", {"Alemán", "Berlín"});

    // Llenar lista de países
    ui->listWidgetPaises->addItems(paises.keys());

    // Conectar selección con slot
    connect(ui->listWidgetPaises, &QListWidget::itemClicked, this, &MainWindow::mostrarInfo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mostrarInfo()
{
    QString pais = ui->listWidgetPaises->currentItem()->text();
    auto datos = paises.value(pais);
    QString texto = QString("Idioma: %1\nCapital: %2").arg(datos.first, datos.second);
    ui->labelInfo->setText(texto);

    qDebug() << "Seleccionado:" << pais << "-" << texto;
}
