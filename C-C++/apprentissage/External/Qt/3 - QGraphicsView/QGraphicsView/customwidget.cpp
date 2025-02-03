#include "customwidget.h"
#include <QPainter>
#include <QDebug>

/*
    Painter : objet qui permet de peindre sur quelque chose
 */

CustomWidget::CustomWidget(int time, QWidget *parent)
    : QWidget{parent}
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    setGeometry(0,300, 200,150); // définie le CustomWidget comme faison 200 de hauteur et 250 de largeur à la position 0,300(

    m_timer.setInterval(time); // set un interval au 'QTimer' (chronomètre)
    m_timer.start(); // démarre le QTimer
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(changeText())); // quand on fait une connexion, il faut passer des pointeurs, donc l'adresse
    // quand le QTimer sera terminé, la fonction 'changeText()' sera lancé, ce qui changera la couleur des boutons
}

void CustomWidget::paintEvent(QPaintEvent* event) // 'paintEvent' sera appelé lorsqu'on décide que l'objet doit être changé visuellement
{
    QPainter p(this); // 'paintEvent' récupère un 'painter'

    p.setPen(Qt::blue); // set sur le 'painter', le type de stylo utilisé : celui là va dessiné avec des contours noirs
    p.setBrush(m_isClicked ? Qt::red : (m_timerEnd ? Qt::blue : Qt::gray )); // 'setBrush' va faire un remplissage rouge SI m_isClicked est true, bleu SI SINON m_timerEnd est true, SINON en gris
    /* équivalent de :
        if(m_isClicked == true) { p.setBrush(Qt::red); }
        else if(m_timerEnd == true) { p.setBrush(Qt::blue); }
        else { p.setBrush(Qt::gray); }
*/

    p.drawRoundedRect(20,20, this->width()-40, this->height()-40, 20, 20); // en paramètre : x,y de la position du painter ; largeur ; hauteur ; rondeur ; rayon
    // les 4 premiers paramètre font une bordure de 100 pixels autour du widget

    p.setPen(Qt::green); // les modifications suivantes seront en rouge
    p.drawText(this->width() * 0.5f, this->height() * 0.5f, "Hello."); // paramètre : x ; y ; text
    // 'this->width() / 2, this->height() / 2' : mets le texte au milieu du widget

    updateGeometry(); // recalcule automatiquement l'espace que prend le widget

}

void CustomWidget::mousePressEvent(QMouseEvent *e)
{
    m_isClicked = true;
    repaint(); // rappelle automatiquement la fonction 'paintevent' : fais un update
}

void CustomWidget::mouseReleaseEvent(QMouseEvent *e)
{
    m_isClicked = false;
    repaint();
}

void CustomWidget::changeText()
{
    qDebug() << "Change text" << Qt::endl;

    m_timerEnd = true;

    m_timer.stop(); // arrête le QTimer

    repaint();
}
