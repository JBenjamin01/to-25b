#include "task.h"
#include "ui_task.h"
#include <QDebug>

Task::Task(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Task)
{
    ui->setupUi(this);

    // Cuando se hace clic en el botón "remove", emitir la señal 'removed'
    connect(ui->removeButton, &QPushButton::clicked, [this]() {
        emit removed(this);
        qDebug() << "Botón de eliminar presionado.";
    });
}

Task::~Task()
{
    delete ui;
}
