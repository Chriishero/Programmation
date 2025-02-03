#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QScrollArea>
#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QProcess>
#include <QList>
#include <QTextDocument>
#include <QtNetwork/QtNetwork>
#include <QEventLoop>
#include <QScrollBar>
#include <QFileSystemModel>
#include <QUrl>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <windows.h>
#include <QImage>
#include <QPainter>
#include <QColor>

#include "translationdialog.h"
#include "ui_translationdialog.h"


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
    void openFile(QString filePath); // ouvre le fichier cible

    void translateFile(QString filePath); // traduis un fichier phrase par phrase

    void on_pushButton_7_clicked(); // ouvre la fenêtre de dialog pour afficher la traduction de l'OCR et permet son utilisaton

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_valueChanged(int arg1);

    void startOCR();

    static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam); // Déclaration de la fonction de callback du hook

    void InstallKeyboardHook();

    void UninstallKeyboardHook();

    void on_actionOpen_FIle_triggered();

    void on_actionOpen_Folder_triggered(); // permet d'afficher un dossier dans le QTreeView

    void openQTreeViewFile(QModelIndex index); // ouvre un fichier séletionné à partir du QTreeView

    void on_pushButton_5_clicked(); // ajoute un marque page

    void addBookmark(QString name, int page);

    void on_pushButton_6_clicked(); // supprime le marque page actuel

    void searchBookmark();

    void on_comboBox_4_activated(int index); // utilise le bookmark choisi

    void startProcess();

    void on_pushButton_4_clicked(); // page précédente

    void on_pushButton_3_clicked(); // page suivante

    void on_lineEdit_returnPressed(); // va à la page cible

    void changeFontSize(); // change la taille de la police d'éciture

    void on_pushButton_2_clicked(); // police d'écriture + grande

    void on_pushButton_clicked(); // police d'écriture + petite

    void on_lineEdit_2_returnPressed(); // initialise la taille cible de la police d'écriture

    void textBecomeSelectable(); // permet au text de devenir sélectionnable et installe le filtre de détection de clique

    bool eventFilter(QObject *watched, QEvent *event); // détecte s'il y a eu un clique sur un label

    bool connectToHost(); // se connect au serveur

    bool sendTranslationData(QString sourceLang, QString targetLang, QString text); // envoie le text a traduire au serveur

    QString translateLabel(QString sourceLang, QString targetLang, QString text); // récupère la traduction reçu par le serveur

    void on_comboBox_currentTextChanged(const QString &arg1); // change la langue source si la valeur de la combo box a changé

    void on_comboBox_2_currentTextChanged(const QString &arg1); // change la langue cible si la valeur de la combo box a changé

    void resizeEvent(QResizeEvent* event); // détecte quand la fenêtre change de taille

    void returnTranslatedText();

    void injectText();

    void on_comboBox_8_currentTextChanged(const QString &arg1);

    void on_comboBox_7_currentTextChanged(const QString &arg1);

    void on_comboBox_9_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    QFrame* pageFrame;
    QWidget* scrollWidget;
    QVBoxLayout* pageLayout;
    QScrollArea* scrollArea;
    QList<QVBoxLayout*> listLayout;

    //QWebEnginePage* page;

    int testfontSize = 100;
    int initialfontSize = 25;
    int fontSize = initialfontSize;
    int i = 0;
    int i2 = 0;
    int numberTranslation = 0;
    int fontSizeDialog = 30;
    int initialFontSizeDialog = 30;

    QList<QLabel*> listLabel;
    QList<QString> originalsTextsLabels;

    QProcess* process;

    QTcpSocket* socket;
    QByteArray* response;
    bool translationReady = false;

    QVBoxLayout* splitterLayout;

    QFileSystemModel* dirModel;

    bool wereMaximised = false;
    bool wereMinimised = false;
    bool closeOSR = false;

    // Variable pour stocker le handle du hook
    static HHOOK hKeyboardHook;

    // Variable pour stocker l'instance de MainWindow
    static MainWindow* instance;

    translationDialog* tDialog;

};
#endif // MAINWINDOW_H
