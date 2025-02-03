#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSignalMapper>
#include <QMessageBox>

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
    ui->setupUi(this); // place tous les boutons définie dans le designer

    setWindowTitle("Mon app QGraphicsView !"); // définie un titre à la fenêtre

    m_view = new QGraphicsView(this); // définie l'un des 'view', qui va afficher la scène
    m_view2 = new QGraphicsView(this);

    m_scene = new MaScene(this); // définie la scène

    m_view->setScene(m_scene); // la vue 'm_view' doit afficher la scène 'm_scene'
    m_view2->setScene(m_scene); // la vue 'm_view' va aussi regarder la scène 'm_scene'
    // il y aura les 2 vues d'affiché dans la fenêtre, les deux afficheront la même chose et pourront être intéragie de la même manière

    m_view->setAlignment(Qt::AlignLeft | Qt::AlignTop); // aligne la vue en haut à gauche de la fenêtre
    m_view->centerOn(0,0);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // permet de retirer la scroll bar horizontale
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // permet de retirer la scoll bar verticale

    m_central = new QWidget(this);

    m_layout = new QVBoxLayout(m_central); // définie le layout 'm_layout' comme étant enfant de 'm_central'
    m_central->setLayout(m_layout); // set le layout 'm_layout' au widget central 'm_central'

    m_layout->addWidget(m_view); // ajoute 'm_view' au layout 'm_layout'
    m_layout->addWidget(m_view2);

    m_timer.setInterval(30); // applique un interval de 30ms
    m_timer.start(); // démarre le timer

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(transformation())); // connecte le 'm_timer' (par référence), quand il s'arrête (timeout), à l'objet 'this', à la fonction 'tranformation()'

    QTransform transform; // initiale une variable de transformation

    transform.rotate(50); // fais une rotation de 50°
    transform.scale(1.5, 1.5); // fais un zoom de x1.5

    // m_view2->rotate(50°); // fais une rotation de 50° de la vue 'm_view2'
    m_view2->setTransform(transform); // applique toutes les transformations à 'm_view2'

    setCentralWidget(m_central); // le central Widget est la vue
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::transformation()
{
    m_view2->rotate(1); // fais un rotation de 1° à la vue, à chaque fois que la fonction est appélé, soit quand le 'm_timer' est timeout
}

void MainWindow::on_actionDis_bonjour_triggered()
{
    QMessageBox::information(this, "BonjourTitre", "Hello World !");
}

void MainWindow::on_actionRotation_Gauche_triggered()
{
    m_view->rotate(-45);
}

