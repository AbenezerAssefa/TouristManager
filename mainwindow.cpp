#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrAddPackge = new AddPackage();
    ptrRegisterTourist = new RegisterTourist();
    ptrFindPackage = new FindPackage();
    ptrFindTourist = new FindTourist();
}

MainWindow::~MainWindow()
{
    delete ptrAddPackge;
    delete ptrRegisterTourist;
    delete ptrFindPackage;
    delete ptrFindTourist;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ptrAddPackge->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    ptrRegisterTourist->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    ptrFindPackage->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    ptrFindTourist->show();
}

