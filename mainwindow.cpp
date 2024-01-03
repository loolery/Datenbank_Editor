#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	qDebug() << "--> Programm Start!";
}

MainWindow::~MainWindow()
{
	qDebug() << "--> Stop Programm!";
	delete ui;
}

void MainWindow::save_slot()
{
	qDebug() << "  ->saveButton clicked!";
	ui->saveButton->setIcon(QIcon("://ressources/16x16/done.ico"));
}

