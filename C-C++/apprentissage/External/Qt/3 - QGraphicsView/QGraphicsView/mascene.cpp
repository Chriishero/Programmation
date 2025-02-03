#include "mascene.h"
#include <QPushButton>
#include "custombutton.h"
#include "customwidget.h"

MaScene::MaScene(QObject* parent) : QGraphicsScene(parent)
{
    // Qt peut automatiquement définir la taille de la scène, selon les composants qu'elle contient
    setBackgroundBrush(Qt::white); // définie un fond blanc à ma scène

    for (int i = 0; i < 10; ++i)
    {
        addLine(0,i * 50, 450, i*50, QPen(Qt::gray)); // affiche une ligne horizontal, qui part de x,y et arrive en x,y, de couleur gris
        addLine(i * 50,0, i * 50, 450, QPen(Qt::gray)); // affiche une ligne vertical
    }

    for (int i = 0; i < 4; ++i) // crée 4 nouveau objet 'item'
    {
        MonRectItem* item = new MonRectItem(); // crée un nouveau objet 'item'
        item->setPos(i*50,0); // définie la position de l'item
        m_items.append(item); // ajoute l'objet 'item' dans la liste 'm_items'
        addItem(item); // ajoute l''item' à la scène
        // c'est donc la scène qui s'occupe de la destruction de l'item
    }

    CustomButton* cb = new CustomButton("0RIR"); // crée un CustomButton
    cb->move(0,100); // déplace le bouton de 100 pixel verticalement

    CustomWidget* cw = new CustomWidget(1000); // crée un CustomWidget

    addWidget(cb); // ajoute le bouton 'cb' à la scène
    addWidget(cw); // ajoute le bouton 'cb' à la scène



}

MaScene::~MaScene()
{
}
