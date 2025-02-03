#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tabsWidget = new QTabWidget(this); // crée un gestionnaire d'onglet

    tabsWidget->setMovable(true); // permet de rendre les onglets déplaçable
    tabsWidget->setTabsClosable(true); // permet de fermer les onglets avec la croix

    connect(tabsWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int))); // permet à la croix de fermer un onglet

    setCentralWidget(tabsWidget); // centre les onglets dans la fenêtre

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Tab_triggered()
{
    tabFrame = new QFrame(this); // crée un cadre
    label = new QLabel(tabFrame); // crée un label qui contient du text

    label->setText("Hello World !"); // définie du text au label

    tabsWidget->addTab(tabFrame, "Untitled"); // un onglet à "tabsWidget", qui contiendra un cadre 'tabFrame'
}


void MainWindow::on_actionClose_Tab_triggered()
{
    tabsWidget->removeTab(tabsWidget->currentIndex()); // permet de fermer l'onglet courant, avec 'currentIndex()'
}

void MainWindow::closeTab(int index)
{
    tabsWidget->removeTab(index); // permet aussi de fermer un onglet qui n'est pas actif
}

