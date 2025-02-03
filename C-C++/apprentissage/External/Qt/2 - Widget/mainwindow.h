#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "custombutton.h" // inclus la classe 'CustomButton
#include <QMainWindow>
#include <QVBoxLayout> // inclus les layout verticaux
#include <QHBoxLayout> // inclus les layout horizontaux
#include "customwidget.h" // inclus la classe 'CustomWidget'

/*
    Layout : règles d'organisation automatique de widget, permette d'adapter les widgets automatiquement à la taille de la fenêtre
    Les layouts ne sont pas des widgets
*/

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); // ce constructeur prend un 'widget' en parent
    // si le widget parent est détruit, l'enfant sera automatiquement détruit
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    CustomWidget* m_customWidget;
    QWidget* m_central;
    QVBoxLayout* m_vLayout;

};
#endif // MAINWINDOW_H
