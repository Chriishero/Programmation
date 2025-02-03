#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSignalMapper>

/*
    Spacer Item : item intelligent permettant de déterminer automatiquement quelle espace à ajouter
    Connexions (connect()) : permettent de connecter un signal avec un SLOT qui est la réponse à ce signal

    item->move(x, y) : permet de déplacer un item horizontalement ou verticalement
    i1->addItem(i2)  : ajoute dans l'item 'i1', l'item 'i2'
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Mon app Custom Widget!"); // définie un titre à la fenêtre

    m_central = new QWidget(this);  // crée un nouveau 'QWidget' de parent this, moi-même
    m_vLayout = new QVBoxLayout(this);

    m_central->setLayout(m_vLayout); // le widget central contient le layout 'm_vLayout'

    for (int i = 0; i < 4; ++i) // crée 4 'CustomWidget', et les implémentes dans le layout 'm_vLayout'
    {
        m_customWidget = new CustomWidget(i * 1000, this); // le bouton 1 prendra 1sec à passer de gris à bleu, le bouton 2 prendra 2sec etc...
        m_vLayout->addWidget(m_customWidget); // 'm_vLayout' contient le 'CustomWidget
    }

    setCentralWidget(m_central);
}

MainWindow::~MainWindow()
{
    delete ui;
}
