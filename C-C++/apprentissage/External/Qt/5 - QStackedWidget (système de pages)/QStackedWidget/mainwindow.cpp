#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0); // récupère l'index de la Page 1 du 'stackedWidget'
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1); // récupère l'index de la Page 2 du 'stackedWidget'
}


void MainWindow::on_pushButton_3_clicked()
{
    frame = new QFrame(this);
    label = new QLabel(frame);
    label->setText("New Page");

    ui->stackedWidget->addWidget(frame); // ajoute une nouvelle page
    ui->stackedWidget->setCurrentWidget(frame); // nous redirige vers la nouvelle page
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1); // récupère l'index de la page précédente du 'stackedWidget'
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1); // récupère l'index de la page suivante du 'stackedWidget'
}

