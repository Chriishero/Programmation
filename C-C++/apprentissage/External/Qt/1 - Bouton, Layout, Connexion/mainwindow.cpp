#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSignalMapper>

/*
    Spacer Item : item intelligent permettant de déterminer automatiquement quelle espace à ajouter
    Connexions (connect()) : permettent de connecter un signal avec un SLOT qui est la réponse à ce signal

    item->move(x, y) : permet de dépla cer un item horizontalement ou verticalement
    i1->addItem(i2)  : ajoute dans l'item 'i1', l'item 'i2'
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Mon app !"); // définie un titre à la fenêtre

    m_mainWidget = new QWidget(this);

    m_vLayout = new QVBoxLayout(this);
    m_hLayout = new QHBoxLayout(this); // défini le pointeur nulle 'm_hLayout' comme étant un nouveau Layout avec comme paramètre le parent, 'this'
    // le pointeur de la fenêtre 'this' est utilisé pour le parent, car le parent n'a pas été spécifié, si on utilise 'parent', on passera 'nulle' comme parent
    // le Layout m_hLayout sera automatiquement 'delete', supprimé de la mémoire à la fermeture de la fenêtre

    CustomButton* test = new CustomButton("Bouton Droite", m_mainWidget); // définie un nouveau bouton 'test', avec comme parent, le widget principal 'm_mainWidget'

    connect(test, SIGNAL(clicked(bool)), this, SLOT(DireBonjour())); // établie une connexion, les paramètres : objet, signal à écouter (clique ici), l'objet où se trouve la fonction, fonction à appeler
    // les connect() peuvent uniquement appeler des fonctions définis dans des 'slots'

    m_hLayout->addLayout(m_vLayout); // ajoute dans le layout 'm_hLayout', le layout 'm_vLayout'
    m_hLayout->addWidget(test); // ajoute dans le layout 'm_hLayout', le widget 'test'

    // Le contenu du layout 'm_vLayout' sera agencé verticalement
    // Le layout 'm_vLayout' et le widget 'test' seront agencé horizontalement

    m_mainWidget->setLayout(m_hLayout); // le Layout de 'm_mainWidget', sa manière de s'organiser, sera avec le 'm_hLayout'

    for (int i = 0; i < 4; ++i)
    {
        CustomButton* btn = new CustomButton(QString("Bouton Gauche %1, %2").arg(i).arg("oui"), m_mainWidget); // le parent des boutons est 'm_mainWidget'
        // 'QString()' définie un objet de type string, '%1' récupère le premier argument, '.arg()' implémente un argument

        m_listBtn.append(btn); // ajoute un nouveau 'CustomButton' dans la liste à chaque itération
        m_vLayout->addWidget(btn); // ajoute dans le widget 'btn' dans le Layout

        connect(btn, SIGNAL(clicked(bool)), btn, SLOT(MessageBox())); // la fonction se trouve dans l'objet 'btn', donc on utilise 'btn' au lieu de 'this'

        if(i == 2)
        {
            m_vLayout->addSpacing(100); // ajoute un espace de 100, après le 3ème bouton, à la 2ème itération
        }
    }

    setCentralWidget(m_mainWidget); // définie le widget principale comme étant 'm_mainWidget'
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DireBonjour() // lorsqu'on clique sur le bouton, la fonction se lance
{
    qDebug() << "Bonjour : " << ((CustomButton*)sender())->getName() << Qt::endl; // en utlisant l'adresse de l'objet 'CustomButton' avec 'sender()', on utilise la fonction 'getName()'
}
