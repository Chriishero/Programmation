#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <areascene.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QSplitter>
#include <QFrame>
#include <QLabel>
#include <QThread>
#include <worker.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void stopThread();
    void deplacement();
    void check();

public slots:
    void startGame();
    void stopGame();
    void resetGame();
    void finishCondition();
    void checkWinCondition();

    void deplacementPNJ();

    void setAreaSize();
    void addEntity();
    void addEntityParameters(QString entityData);
    void setSizeStep(Entity* e);
    void setPV(Entity* e);
    void setAttackPoint(Entity* e);
    void setDeplacementFrequence(Entity* e);
    void setDeplacementPatern(Entity* e);
    void deleteEntity(int index);

    void addItem();
    void addItemParameters(QString itemData);
    void setItemColor(Item* i);
    void setItemEvent(Item *i);
    void setn_Event(Item *i);
    void deleteItem(int index);

    AreaScene* getm_scene();


private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

protected:
    Ui::MainWindow *ui;

    QGraphicsView* m_view;
    AreaScene* m_scene;

    QFrame* objectFrame;
    QVBoxLayout* frameLayout;

    // Entity
    QHBoxLayout* spinBoxLayout;
    QLabel* stepsSizeLabel;
    QSpinBox* m_stepsSizeSpinBox;

    QHBoxLayout* attackSpinBoxLayout;
    QLabel* attackLabel;
    QSpinBox* attackSpinBox;

    QHBoxLayout* PVSpinBoxLayout;
    QLabel* PVLabel;
    QSpinBox* PVSpinBox;

    QHBoxLayout* AFSpinBoxLayout;
    QLabel* AFLabel;
    QSpinBox* AFSpinBox;

    QHBoxLayout* APComboBoxLayout;
    QLabel* APLabel;
    QComboBox* APComboBox;
    ////////////////////////////////

    // Item
    QPushButton* colorButton;

    QHBoxLayout* eventLayout;
    QLabel* eventLabel;
    QComboBox* eventComboBox;

    QHBoxLayout* numberEventLayout;
    QLabel* numberEventLabel;
    QSpinBox* numberEventSpinBox;
    ///////////////////////////////
    // Win/Defeat Conditions
    QHBoxLayout* conditionLayout;
    QComboBox* ifComboBox;
    QComboBox* objectComboBox;
    QComboBox* parametersComboBox;
    QComboBox* comparaisonComboBox;
    QSpinBox* targetSpinBox;
    //////////////////////////////

    QSplitter* entitiesWindow;

    QList<QWidget*> widgetList;
    QList<QComboBox*> winConditionsComboboxList;
    QList<QSpinBox*> winConditionsSpinboxList;
    QList<QString> winConditionList;
    QList<QList<QString>> allWinConditionList;
    QList<QString> defeatConditionList;
    QList<QComboBox*> defeatConditionsComboboxList;
    QList<QSpinBox*> defeatConditionsSpinboxList;
    QList<QList<QString>> allDefeatConditionList;

    QThread* thread;

    QList<worker*> workerlist;

    bool gameStarted = false;
    bool random = false;
    bool test = false;

    int nRC = 0;
    int nWidgetWinCondition = 0;
    int nWidgetDefeatCondition = 0;
};
#endif // MAINWINDOW_H
