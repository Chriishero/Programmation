#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>

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

    QFontDatabase::addApplicationFont("font/SourceCodePro-VariableFont_wght.ttf"); // ajoute une police d'écriture à l'application

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Tab_triggered()
{
    createTab();
}

void MainWindow::on_actionClose_Tab_triggered()
{
    tabsWidget->removeTab(tabsWidget->currentIndex()); // permet de fermer l'onglet courant, avec 'currentIndex()'
}

void MainWindow::closeTab(int index)
{
    tabsWidget->removeTab(index); // permet aussi de fermer un onglet qui n'est pas actif
}

void MainWindow::createTab()
{
    tabFrame = new QFrame(this); // crée un cadre
    tabLayout = new QVBoxLayout(tabFrame);
    tabEdit = new QPlainTextEdit(); // widget qui permet d'éditer du text
    //tabEdit->setReadOnly(true);
    for (int i = 0; i < 100; ++i) {
        label = new QLabel(tabEdit);
        label->setText("HelloWorld");
        label->move(0, 20*i);

    }


    QFont font = tabEdit->document()->defaultFont(); // crée une varialbe permettant au widget 'tabEdit' d'utiliser la police par défaut de l'application définie avec QFontDatabase
    font.setFamily("Source Code Pro Extralight"); // ajoute le nom de la font
    tabEdit->setFont(font); // 'tabEdit' utilisera la police d'écriture 'font'

    tabEdit->setTabStopDistance(QFontMetrics(tabEdit->font()).horizontalAdvance(' ') * 4); // définie la taille de la tabulation, ici 4 espaces

    tabLayout->addWidget(tabEdit); // ajoute ce widget au layout, ça nous permettra d'entrer du texte dans les onglets

    int tab_index = tabsWidget->addTab(tabFrame, "Untitled"); // crée un onglet à "tabsWidget", qui contiendra un cadre 'tabFrame' et récupère son index
    tabsWidget->setCurrentIndex(tab_index); // initialise la page actuel comme étant celle qui vient d'être créé
}

