#include "translationdialog.h"
#include "ui_translationdialog.h"

translationDialog::translationDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::translationDialog)
{
    ui->setupUi(this);

    setWindowTitle("OCR Translation Dialog");

    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint); // supprime les bordures de la fenêtre
    // la fenêtre restera à l'écran inactivement si elle n'est pas utilisé
}

translationDialog::~translationDialog()
{
    delete ui;
}

void translationDialog::mousePressEvent(QMouseEvent *event)
{
    cur_pos = event->globalPosition().toPoint(); // position actuelle de la souris

}

void translationDialog::mouseMoveEvent(QMouseEvent *event)
{
    new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
    move(x() + new_pos.x(), y() + new_pos.y()); // déplace la fenêtre à la nouvelle position
    cur_pos = event->globalPosition().toPoint(); // redéfinie la position actuelle
}
