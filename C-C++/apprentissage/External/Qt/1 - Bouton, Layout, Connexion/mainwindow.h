#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "custombutton.h" // inclus la classe 'CustomButton
#include <QMainWindow>
#include <QVBoxLayout> // inclus les layout verticaux
#include <QHBoxLayout> // inclus les layout horizontaux

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

private slots: // permet à Qt de définir des fonctions particulières qui vont être visible par le système de connexion
// les connect() peuvent uniquement appeler des fonctions définis dans des 'slots'
    void DireBonjour();

private:
    Ui::MainWindow *ui;

    QWidget* m_mainWidget; // crée un widget principale qui contient tous les autres layouts et widgets

    QList<CustomButton*> m_listBtn; // crée une liste de 'CustomButton'
    QVBoxLayout* m_vLayout; // 'm' est souvent utilisé dans le nom, pour spécifié qu'il s'agit d'un membre de la classe privé
    QHBoxLayout* m_hLayout;
};
#endif // MAINWINDOW_H
