#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    tabsWidget = new QTabWidget(this); // crée un gestionnaire d'onglet

    tabsWidget->setMovable(true); // permet de rendre les onglets déplaçable
    tabsWidget->setTabsClosable(true); // permet de fermer les onglets avec la croix

    setCentralWidget(window); // centre les onglets dans la fenêtre

    treeView->setMaximumWidth(0); // fais en sorte qu'il n'apparaisse pas au lancement de l'application en mettant sa largeur max à 0

    window->addWidget(treeView);
    window->addWidget(tabsWidget);

    connect(tabsWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int))); // permet à la croix de fermer un onglet
    connect(treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(openTreeViewFile(QModelIndex))); // permet d'ouvrir un fichier affiché par l'explorateur de fichier de l'application

    QFontDatabase::addApplicationFont("font/SourceCodePro-VariableFont_wght.ttf"); // ajoute une police d'écriture à l'application

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Tab_triggered()
{
    createTab();
}

void MainWindow::on_actionClose_Tab_triggered()
{
    tabsWidget->removeTab(tabsWidget->currentIndex()); // permet de fermer l'onglet courant, avec 'currentIndex()'
}

void MainWindow::closeTab(int index)
{
    tabsWidget->removeTab(index); // permet aussi de fermer un onglet qui n'est pas actif
}

void MainWindow::createTab()
{
    tabFrame = new QFrame(this); // crée un cadre
    tabLayout = new QVBoxLayout(tabFrame);
    fileEdit = new QPlainTextEdit(); // widget qui permet d'éditer du text
    fileEdit->setObjectName("textEdit"); // ajoute un nom à l'objet 'QPlainTextEdit'

    QFont font = fileEdit->document()->defaultFont(); // crée une variable permettant au widget 'fileEdit' d'utiliser la police par défaut de l'application définie avec QFontDatabase
    font.setFamily("Source Code Pro Extralight"); // ajoute le nom de la font
    fileEdit->setFont(font); // 'fileEdit' utilisera la police d'écriture 'font'

    fileEdit->setTabStopDistance(QFontMetrics(fileEdit->font()).horizontalAdvance(' ') * 4); // définie la taille de la tabulation, ici 4 espaces

    QLabel* status = new QLabel(this);
    status->setText("Line 1, Column 1");
    status->setObjectName("status");

    tabLayout->addWidget(fileEdit); // ajoute ce widget au layout, ça nous permettra d'entrer du texte dans les onglets
    tabLayout->addWidget(status);

    int tab_index = tabsWidget->addTab(tabFrame, "Untitled"); // crée un onglet à "tabsWidget", qui contiendra un cadre 'tabFrame' et récupère son index
    tabsWidget->setCurrentIndex(tab_index); // initialise la page actuel comme étant celle qui vient d'être créé

    tabsWidget->setTabToolTip(tabsWidget->currentIndex(), "Untitled");

    connect(currentTextEdit(), SIGNAL(textChanged()), this, SLOT(textEditChange())); // si le le texte actuel retourné par 'currentTextEdit()' a été changé, alors la fonction 'textEditChange()' sera appelé
    connect(currentTextEdit(), SIGNAL(cursorPositionChanged()), this, SLOT(updateStatus()));
}

void MainWindow::openTabFile(QString filePath)
{
    QFile file(filePath); // récupère le fichier à partir de 'filePath'
    QFileInfo fileName(filePath); // récupère le nom du fichier

    if(!file.open(QIODevice::ReadOnly | QFile::Text)) // si ce n'est pas un fichier en lecture seul et de type text
    {
        QMessageBox::warning(this, "Warning," , "Cannot open file : " + file.errorString()); // fais un message box si le fichier ne peut pas être ouvert, avec l'erreur
        return; // ferme la fonction
    }

    tabsWidget->setTabToolTip(tabsWidget->currentIndex(), filePath); // modifie le tool tip de l'onglet (chemin qui mène au fichier en passant la souris sur le nom de l'onglet'

    QTextStream in(&file); // lis le contenue du fichier
    QString text = in.readAll(); // récupère toutes les lignes du fichiers

    currentTextEdit()->setPlainText(text); // remplace le text de l'onglet courant, par le contenue du fichier

    file.close(); // ferme le fichier


    tabsWidget->setTabText(tabsWidget->currentIndex(), fileName.fileName()); // le nom de l'onglet (tabsWidget->currentIndex()) aura le nom du fichier importé (fileName)
    // le paramètre doit être un 'string' est non un 'QFileInfo', on utlise donc '.fileName()'
}

QPlainTextEdit* MainWindow::currentTextEdit()
{
    QList<QPlainTextEdit*> fileEditList = tabsWidget->findChildren<QPlainTextEdit*>("textEdit"); // 'findChildren<QPlainTextEdit*>' récupère tous les éléments de type 'QPlainTextEdit' avec le nom 'textEdit'
    for (int i = 0; i < fileEditList.count(); ++i) // instancie une boucle qui va vérifier si l'index du parent = index courant
    {
        if(tabsWidget->indexOf(fileEditList[i]->parentWidget()) == tabsWidget->currentIndex()) // si l'index du parent = l'index courant
        {
            return fileEditList[i]; // retourne le texte de l'onglet courant
        }
    }

    return new QPlainTextEdit;
}

QLabel* MainWindow::currentStatus()
{
    QList<QLabel*> statusList = tabsWidget->findChildren<QLabel*>("status"); // 'findChildren<QLabel*>' récupère tous les éléments de type 'QLabel' avec le nom 'status'
    for (int i = 0; i < statusList.count(); ++i) // instancie une boucle qui va vérifier si l'index du parent = index courant
    {
        if(tabsWidget->indexOf(statusList[i]->parentWidget()) == tabsWidget->currentIndex()) // si l'index du parent = l'index courant
        {
            return statusList[i]; // retourne la barre de status de l'onglet courant
        }
    }

    return new QLabel;
}

void MainWindow::textEditChange() // cette méthode ajoute un asterisque au début du nom de l'onglet si le texte contenue a été modifié
{
    QString tabName = tabsWidget->tabText(tabsWidget->currentIndex());

    if(tabName.at(0) != '*')
    {
        tabsWidget->setTabText(tabsWidget->currentIndex(), "*" + tabName); // ajoute un asterisque
    }
}


void MainWindow::on_actionOpen_File_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File"); // permet de récupérer le chemin du fichier

    createTab();
    openTabFile(filePath);
}


void MainWindow::on_actionSave_File_triggered()
{
    QString fileName = tabsWidget->tabToolTip(tabsWidget->currentIndex()); // récupère le tooltip de l'onglet courant

    if(fileName == "Untitled")
    {
        on_actionSave_File_as_triggered();
        return;
    }

    QFile file(fileName); // créer une instance 'QFile' à partir du chemin du fichier (fileName)

    if(!file.open(QFile::WriteOnly | QFile::Text)) // si on a pas le droit d'écriture et que le fichier n'est pas de type texte :
    {
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }

    QTextStream out(&file); // permet d'écrire dans un fichier
    QString text = currentTextEdit()->toPlainText(); // récupère le texte de l'onglet courant de type 'QPlainTextEdit' puis le convertie en 'QString' avec 'toPlainText()'

    out << text; // enregistre le contenue du fichier texte

    file.close();

    QString newTabText = tabsWidget->tabText(tabsWidget->currentIndex()).remove(0, 1); // retire 1 caractère à l'index 0 (l'asterisque)
    tabsWidget->setTabText(tabsWidget->currentIndex(), newTabText); // remplace le nom de l'onglet actuelle avec le nouveau sans l'asterisque

}


void MainWindow::on_actionSave_File_as_triggered()
{
    if (tabsWidget->count() == 0)
    {
        QMessageBox::warning(this, "Warning", "Cannot save file !");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(this, "Save as ..."); // ouvre une fenêtre de dialog permettant d'enregistrer le fichier sous
    QFile file(filePath);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }

    QTextStream out(&file); // permet d'écrire dans un fichier
    QString text = currentTextEdit()->toPlainText(); // récupère le texte de l'onglet courant de type 'QPlainTextEdit' puis le convertie en 'QString' avec 'toPlainText()'

    out << text; // enregistre le contenue du fichier texte

    file.close();

    openTabFile(filePath); // ouvre un onglet avec le chemin du fichier

}

void MainWindow::updateStatus()
{
    QString line = QString::number(currentTextEdit()->textCursor().blockNumber()+1); // compte le numéro de la ligne actuelle et convertie ce nombre en 'QString'
    QString column = QString::number(currentTextEdit()->textCursor().columnNumber()+1); // compte le numéro de la colonne actuelle et convertie ce nombre en 'QString'

    QString newStatus = "Line " + line + ", Column " + column;

    currentStatus()->setText(newStatus); // remplace la barre de status actuelle par la nouvelle 'newStatus'
}


void MainWindow::on_actionOpen_Folder_triggered()
{
    QUrl dirPath = QFileDialog::getExistingDirectory(this, "Open Folder", "/", QFileDialog::ShowDirsOnly); // permet d'ouvrir une fenêtre de diologue pour les dossiers
    dirModel->setRootPath(dirPath.toString()); // initialise un chemin racine
    treeView->setModel(dirModel); // initialise un modèle à afficher pour 'treeView'
    treeView->setRootIndex(dirModel->index(dirPath.toString())); // initialise le dossier racine à afficher
    treeView->hideColumn(1); // cache la colone qui affiche le 'Size'
    treeView->hideColumn(2); // cache la colonne qui affiche le 'Type'
    treeView->hideColumn(3); // cache la colone qui affiche le 'Date Modified'

    treeView->setMinimumWidth(width() * 20/100); // initiliase une largeur minimum au 'treeView' de 20%
    treeView->setMaximumWidth(width() * 30/100); // initiliase une largeur maximum au 'treeView' de 30%
}

void MainWindow::openTreeViewFile(QModelIndex index)
{
    createTab(); // crée un nouvel onglet
    QString filePath = dirModel->fileInfo(index).absoluteFilePath(); // récupère le chemin du fichier à partir de son index dans 'treeView'
    openTabFile(filePath); // ouvre le fichier dans l'onglet créé
}

