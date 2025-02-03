#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QFontDatabase>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QList>
#include <QTreeView>
#include <QSplitter>
#include <QFileSystemModel>

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
    void on_actionOpen_File_triggered();
    void openTabFile(QString filePath);
    QPlainTextEdit* currentTextEdit();
    QLabel* currentStatus();
    void textEditChange();
    void on_actionSave_File_triggered();
    void on_actionSave_File_as_triggered();
    void updateStatus();
    void on_actionOpen_Folder_triggered();
    void openTreeViewFile(QModelIndex index);

private:
    Ui::MainWindow *ui;

    QTabWidget* tabsWidget;
    QFrame* tabFrame;
    QLabel* label;
    QVBoxLayout* tabLayout;
    QPlainTextEdit* fileEdit;
    QTreeView* treeView = new QTreeView; // permet de faire un explorateur de fichier en affichant graphiquement 'QFileSystemModel'
    QSplitter* window = new QSplitter(this); // permet de séparer des widgets dans une seule fenêtre
    QFileSystemModel* dirModel = new QFileSystemModel(this); // permet de gérer les fichiers du systèmes

};
#endif // MAINWINDOW_H
