#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QListWidgetItem>
#include<QFile>
#include<QStandardPaths>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file(path);

    if(!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(0,"error",file.errorString());
    }

    QTextStream in(&file);
    while(!in.atEnd())
    {
        QListWidgetItem* item = new QListWidgetItem(in.readLine(), ui->listWidget);
        ui->listWidget->addItem(item);
        item->setFlags(item->flags( ) | Qt::ItemIsEditable);
    }
    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
    QFile file(path);

    if(!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(0,"error",file.errorString());
    }

    QTextStream out(&file);

    for(int i = 0;i<ui->listWidget->count();++i)
    {
        out<<ui->listWidget->item(i)->text()<<"\n";
    }

    file.close();

}

void MainWindow::on_pushButtonAdd_clicked()
{
    QListWidgetItem* item = new QListWidgetItem(ui->tasktodo->text(),ui->listWidget);
    ui->listWidget->addItem(item);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->tasktodo->clear();
    ui->tasktodo->setFocus();
}


void MainWindow::on_pushButton_Remove_clicked()
{
    QListWidgetItem* item = ui->listWidget->takeItem((ui->listWidget->currentRow()));
    delete item;
}


void MainWindow::on_pushButton_RemoveAll_clicked()
{
    ui->listWidget->clear();
}
