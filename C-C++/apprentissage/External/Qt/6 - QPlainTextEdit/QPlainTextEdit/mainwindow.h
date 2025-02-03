#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QPlainTextEdit>

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

private slots:
    void on_actionNew_Tab_triggered();
    void on_actionClose_Tab_triggered();
    void closeTab(int index);
    void createTab(); // méthode qui permettra de créer des onglets

private:
    Ui::MainWindow *ui;

    QTabWidget* tabsWidget;
    QFrame* tabFrame;
    QLabel* label;
    QVBoxLayout* tabLayout;
    QPlainTextEdit* tabEdit;

};
#endif // MAINWINDOW_H
