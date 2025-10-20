#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidgetItem>
#include <QColor>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Agregamos algunos colores más
    ui->listWidget->addItems({"Rojo", "Verde", "Azul", "Amarillo", "Negro", "Blanco", "Cyan", "Magenta"});

    // Conectamos
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
    if (!item)
        return;

    QString nombreColor = item->text();

    // Convertimos el nombre en un QColor válido
    QColor color;

    if (nombreColor.compare("Rojo", Qt::CaseInsensitive) == 0)
        color = Qt::red;
    else if (nombreColor.compare("Verde", Qt::CaseInsensitive) == 0)
        color = Qt::green;
    else if (nombreColor.compare("Azul", Qt::CaseInsensitive) == 0)
        color = Qt::blue;
    else if (nombreColor.compare("Amarillo", Qt::CaseInsensitive) == 0)
        color = Qt::yellow;
    else if (nombreColor.compare("Negro", Qt::CaseInsensitive) == 0)
        color = Qt::black;
    else if (nombreColor.compare("Blanco", Qt::CaseInsensitive) == 0)
        color = Qt::white;
    else if (nombreColor.compare("Cyan", Qt::CaseInsensitive) == 0)
        color = Qt::cyan;
    else if (nombreColor.compare("Magenta", Qt::CaseInsensitive) == 0)
        color = Qt::magenta;
    else
        color = Qt::gray;

    // Cambiamos el texto del QLabel
    ui->labelColor->setText("Color seleccionado: " + nombreColor);

    // Cambiamos el color de fondo con StyleSheet
    QString estilo = QString("background-color: %1; color: %2; border-radius: 8px; padding: 6px;")
                         .arg(color.name())
                         // Texto blanco para fondos oscuros y negro para fondos claros
                         .arg(color.lightness() < 128 ? "white" : "black");

    ui->labelColor->setStyleSheet(estilo);
}
