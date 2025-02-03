#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout> // inclus les layout verticaux
#include <QHBoxLayout> // inclus les layout horizontaux
#include <QGraphicsView>
#include <mascene.h>
#include <QTimer>

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

    QGraphicsView* m_view;
    QGraphicsView* m_view2;
    MaScene* m_scene;

    QVBoxLayout* m_layout;
    QWidget* m_central;

    QTimer m_timer;

private slots:
    void transformation();


    void on_actionDis_bonjour_triggered();
    void on_actionRotation_Gauche_triggered();
};
#endif // MAINWINDOW_H
