#include "custombutton.h"
#include <QDebug> // inclus le debug
#include <QMessageBox> // inclus les messages box

CustomButton::CustomButton(QString text, QWidget *parent) : QPushButton(parent), m_text(text) // la classe fille 'CustomButton' récupère le parent
{
    setText(text); // inclus du text dans le bouton, un 'label'
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum); // spécifie à Qt comment l'item doit réagir horizontalement et verticalement
    // QSizePolicy::Maximum permet de considérer les valeurs maximums nécessaires pour afficher le contenu du bouton
    // QSizePolicy::Minumum étire le bouton de manière à ce que le bouton prenne l'espace total
}

CustomButton::~CustomButton()
{
    qDebug() << "Destruction ! " << Qt::endl; // affiche un message lors de la suppression, 'delete' du bouton et autre widget
}

void CustomButton::MessageBox()
{
    QMessageBox::information(this, "Titre", "Hello my friend, c'est un text"); // permet d'ouvrir une fenêtre de message
}
