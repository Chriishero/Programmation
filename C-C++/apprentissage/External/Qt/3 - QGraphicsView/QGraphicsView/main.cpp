#include "mainwindow.h"
#include <QApplication> // inclue la classe de point d'entré de l'application
#include <QPushButton> // chaque classe de type Qt commençant par 'Q' doivent être inclus
// inclus les boutons

/*  QPushButton btn("hello world ! ");
    btn.show();
    Si un widget sans parent est affiché, il sera automatiquement créé dans une nouvelle fenêtre

    QPushButton btn("Boutton 1", &w); // le bouton a comme paramètre un label, et '&w' : l'adresse du Qwidet 'MainWindow'
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    MainWindow w; // déclare une instance de la classe 'MainWindow'

    w.show(); // affiche la fenêtre



    return a.exec(); // run loop, boucle d'évennement qui attend que des évenemments soit executé
    // boucle qui se terminera que lorsque l'application sera arrêté
}
