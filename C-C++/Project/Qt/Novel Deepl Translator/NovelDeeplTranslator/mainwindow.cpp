#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow* MainWindow::instance = nullptr;
HHOOK MainWindow::hKeyboardHook = NULL;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setWindowFlags(Qt::WindowStaysOnTopHint);
    //setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground,true);
    setWindowTitle("Novel Toolkit");

    tDialog = new translationDialog();

    instance = this;
    InstallKeyboardHook(); // Installer le hook clavier global

    ui->tab_7->setLayout(ui->gridLayout_3);
    ui->tab_8->setLayout(ui->gridLayout_2);
    setCentralWidget(ui->tabWidget);
    ui->treeView->setMaximumWidth(0);

    dirModel = new QFileSystemModel(this); // permet de gérer les fichiers du systèmes

    ui->label->setText(QString("Font Size :"));

    /*page = new QWebEnginePage(this);
    QWebEngineSettings *settings = page->settings();
    settings->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    connect(page, &QWebEnginePage::loadFinished, this, &MainWindow::print);
    page->setUrl(QUrl(QString("https://www.deepl.com/translator#auto/fr/")));*/

    startProcess();
    //process->waitForFinished(-1);

    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(openQTreeViewFile(QModelIndex)));

}

MainWindow::~MainWindow()
{
    translateLabel("close", "close", "CLOSEAPP");
    process->terminate();
    translateLabel("close", "close", "CLOSEAPP");

    UninstallKeyboardHook();

    delete process;
    delete ui;
}

void MainWindow::openFile(QString filePath) // ouvre le fichier cible
{
    originalsTextsLabels.clear();

    while(ui->stackedWidget->count()>1)
    {
        for (int i = 0; i < ui->stackedWidget->count(); ++i) {
            ui->stackedWidget->removeWidget(ui->stackedWidget->widget(i));
        }
    }

    if(filePath.endsWith(".pdf"))
    {
        process = new QProcess(this);

        QString scriptPath = "python/pdfToTxt.py";
        QList<QString> argList;
        argList.push_back(filePath);

        process->start("python/python311/python.exe", QStringList() << scriptPath << argList);
        process->waitForFinished(-1);

        filePath += ".txt";
    }

    QFile file(filePath);
    QFileInfo fileName(filePath);
    ui->label_3->setText(fileName.fileName());

    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }

    QTextStream in(&file);

    scrollArea = new QScrollArea(this); // crée un widget de type 'QScrollArea'
    // il permet de gérer automatiquement les barres de défilement quand le contenue dépasse la taille de la zone d'affichage
    //pageFrame = new QFrame(scrollArea); // crée le cadre de la page

    pageFrame = new QFrame(scrollArea); // crée le cadre de la page
    pageFrame->setFixedWidth(this->width()*3);

    pageLayout = new QVBoxLayout(pageFrame); // layout qui contiendra les phrases
    pageLayout->setAlignment(Qt::AlignHCenter);

    QLabel* text = new QLabel(pageFrame);
    text->setObjectName("Text");
    QFont font = text->font();
    font.setPointSize(fontSize);
    text->setFont(font);

    int i = 0;
    bool quit = false;
    QString page;

    while (!in.atEnd())
    {
        if(quit == true)
        {
            scrollArea = new QScrollArea(this); // crée un widget de type 'QScrollArea'
            // il permet de gérer automatiquement les barres de défilement quand le contenue dépasse la taille de la zone d'affichage
            //pageFrame = new QFrame(scrollArea); // crée le cadre de la page

            pageFrame = new QFrame(scrollArea); // crée le cadre de la page
            pageFrame->setFixedWidth(this->width()*3);

            pageLayout = new QVBoxLayout(pageFrame); // layout qui contiendra les phrases
            pageLayout->setAlignment(Qt::AlignHCenter);

            quit = false;
        }

        bool alreadyPushBack = false;

        QString line = in.readLine();

        //if((line.contains("Page") && line.contains(QString("%1").arg(i))) || line.contains("mp4directs.com"))
        if(line.contains("\x0c")) // si la line contient le charactère de saut de page '\x0c'
        {
            if(line.contains("mp4directs.com"))
            {
                QList<QString> lLine = line.split("mp4directs.com");
                line = lLine[1];
            }

            page.push_back(line);
            page.push_back('\n');

            QLabel* text = new QLabel(pageFrame);
            text->setObjectName("Text");
            QFont font = text->font();
            font.setPointSize(fontSize);
            text->setFont(font);

            QString sentence;

            page = page.replace("\n", "<br>");

            originalsTextsLabels.push_back(page);

            for (const auto& c : page)
            {
                sentence.push_back(c);
            }

            text->setOpenExternalLinks(true);
            text->setText(sentence);
            //listLabel.append(text);

            pageLayout->addWidget(text);
            page.clear();
            pageFrame->setLayout(pageLayout); // set le layout à la 'pageFrame'
            scrollArea->setWidget(pageFrame); // 'pageFrame' deviendra le widget défilable de 'scrollArea'
            ui->stackedWidget->addWidget(scrollArea);

            QScrollBar* hScrollBar = scrollArea->horizontalScrollBar();
            hScrollBar->setValue(this->width());

            //ui->stackedWidget->setCurrentWidget(scrollArea);
            ui->label_2->setText(QString("/%1").arg(ui->stackedWidget->count())); // affiche le nombre de page

            i++;
            quit = true;
            continue;
        }
        else if(alreadyPushBack == false)
        {
            if(line.contains("mp4directs.com"))
            {
                QList<QString> lLine = line.split("mp4directs.com");
                line = lLine[1];
            }

            page.push_back(line);
            page.push_back('\n');
            alreadyPushBack = true;
        }
    }

    file.close();
    ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
    ui->label_2->setText(QString("/%1").arg(ui->stackedWidget->count())); // affiche le nombre de page
    ui->lineEdit->setText(QString("%1").arg(ui->stackedWidget->currentIndex()+1)); // affiche le numéro de la page actuelle

    ui->lineEdit_2->setText(QString("%1").arg(fontSize));

    textBecomeSelectable();
}

void MainWindow::translateFile(QString filePath) // traduis un fichier phrase par phrase
{
    if(filePath.endsWith(".pdf"))
    {
        process = new QProcess(this);

        QString scriptPath = "python/pdfToTxt.py";
        QList<QString> argList;
        argList.push_back(filePath);

        process->start("python/python311/python.exe", QStringList() << scriptPath << argList);
        process->waitForFinished(-1);

        filePath += ".txt";
    }

    QFile file(filePath);
    QFileInfo fileName(filePath);
    ui->label_3->setText(fileName.fileName());

    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }

    QTextStream in(&file);

    QString wholeFile = "";

    if(ui->comboBox_3->currentIndex() == 0)
    {
        wholeFile = in.readAll();
        qDebug() << wholeFile;

        wholeFile.replace(". ", ". SEPARATOR");
        wholeFile.replace(".\"\n", ".\"\nSEPARATOR");
        wholeFile.replace(".”\n", ".”\nSEPARATOR");
        wholeFile.replace(".\n", ".\nSEPARATOR");
    }
    else if(ui->comboBox_3->currentIndex() == 1)
    {
        wholeFile = in.readAll();

        wholeFile.replace("\n\n", "\n\nSEPARATOR");
    }
    else if(ui->comboBox_3->currentIndex() == 2)
    {
        /*QString wholeFile2 = "";
        while(!in.atEnd())
        {
            QString whole1500 = in.read(1500);
            wholeFile2.push_back(whole1500 + "SEPARATOR");
        }
        wholeFile = wholeFile2;*/

        QChar prevPrevC;
        QChar prevC;
        int sentenceIteration = 0;
        QString wholeFileSeparator;

        while(!in.atEnd()) {

            QChar c;
            in >> c;

            wholeFileSeparator.push_back(c);

            if(c == ' ' && prevC == '.')
            {
                sentenceIteration++;
                prevC = '\x0';
            }
            else if(c == '\n' && prevC == '.')
            {
                sentenceIteration++;
                prevC = '\x0';
            }
            else if((c == '"' || c == "”") && prevC == '.')
            {
                prevPrevC = c;
            }
            else
            {
                prevC = QChar::Null;
            }
            if(c == '\n' && (prevPrevC == '"' || prevPrevC == "”") && prevC == '.')
            {
                sentenceIteration++;
                prevC = QChar::Null;
            }
            else
            {
                prevC = QChar::Null;
                prevPrevC = QChar::Null;
            }
            if(sentenceIteration == 10)
            {
                sentenceIteration = 0;
                wholeFileSeparator.push_back("SEPARATOR");
            }

            if(prevC != '.' && (c != '"' || c != "”"))
            {
                prevC = c;
            }
        }
        wholeFile = wholeFileSeparator;
    }

    file.close();

    QList<QString> wholeParts = wholeFile.split("SEPARATOR");
    QString wholeTranslatedFile = wholeFile;
    qDebug() << wholeParts.length();

    for (auto& sentence : wholeParts) {
        i2++;
        if(sentence != "\f")
        {
            QString translation = translateLabel(ui->comboBox->currentText(), ui->comboBox_2->currentText(), sentence);

            QCoreApplication::processEvents(); // attend la fin de l'execution du code précédent 'translateLabel' avant de passer à la suite

            ui->plainTextEdit->appendPlainText(translation);
            int value = i2 / wholeParts.length() * 100;
            ui->progressBar->setValue(value);
            ui->label_8->setText(QString("%1/%2").arg(i2).arg(wholeParts.length()));

            wholeTranslatedFile = wholeTranslatedFile.replace(sentence, translation);
        }
    }

    QString savePath = QFileDialog::getSaveFileName(this, "Save as ..."); // ouvre une fenêtre de dialog permettant d'enregistrer le fichier sous
    QFile saveFile(savePath);

    if (!saveFile.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file : " + saveFile.errorString());
        return;
    }

    QTextStream out(&saveFile);
    out << wholeTranslatedFile;
    saveFile.close();
}

void MainWindow::on_pushButton_7_clicked() // lance la fenêtre de dialog
{
    ui->spinBox_2->setValue(tDialog->windowOpacity()*100);
    ui->spinBox->setValue(fontSizeDialog);

    tDialog->show();
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    tDialog->setWindowOpacity(ui->spinBox_2->text().toDouble()/100);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    fontSizeDialog = arg1;
    QFont font = tDialog->ui->label->font();
    font.setPointSize(fontSizeDialog);
    tDialog->ui->label->setFont(font);
}



void MainWindow::startOCR()
{
    if(ui->tabWidget->currentWidget() == ui->tab)
    {
        QString pcUserName = QDir::home().dirName(); // récupère le nom d'utilisateur de la sessions Windows
        QString directoryPath = QString("C:/Users/%1/Pictures/Screenshots").arg(pcUserName);
        QDir directory(directoryPath);

        // Récupère le nom de tous les captures d'écran enregistré dans le dossier 'directory'
        QStringList screenshots = directory.entryList(QStringList() << "*.png" << "*.PNG" << "*.jpg" << "*.JPG", QDir::Files);
        QString penultimateScreenShot = screenshots.last();
        QString lastScreenShot = penultimateScreenShot;

        while(lastScreenShot == penultimateScreenShot)
        {
            screenshots = directory.entryList(QStringList() << "*.png" << "*.PNG" << "*.jpg" << "*.JPG", QDir::Files);
            lastScreenShot = screenshots.last();
        }

        QString imagePath = directoryPath + QString("/%1").arg(lastScreenShot);
        qDebug() << "dernière capture : " << imagePath;

        process = new QProcess(this);

        QList<QString> argList;
        argList.push_back(imagePath);
        process->start("py", QStringList() << ".\\python\\preProcessText.py" << argList);

        /*argList.clear();
        process = new QProcess(this);
        argList.push_back("preProcessingText.png");
        argList.push_back("stdout");
        argList.push_back(" --psm 8");

        process->start("Tesseract-OCR/tesseract.exe", QStringList() << argList);*/

        connect(process, &QProcess::readyReadStandardOutput, [this]() {
            QByteArray output = process->readAllStandardOutput();
            QString ocrText = QString::fromLocal8Bit(output);
            qDebug() << "Output OCR :" << ocrText;
            tDialog->ui->label->setText(translateLabel(ui->comboBox->currentText(), ui->comboBox_2->currentText(), ocrText));
            connectToHost(); // se reconnecte juste après l'affichage de la traduction pour préparer la prochaine traduction
        });
    }
}

LRESULT CALLBACK MainWindow::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            KBDLLHOOKSTRUCT *pKeyboard = (KBDLLHOOKSTRUCT *)lParam;
            if (pKeyboard->vkCode == VK_SNAPSHOT) { // VK_SNAPSHOT est le code virtuel pour Print Screen
                qDebug() << "Print Screen key pressed!";
                if (instance) {
                    // Appeler une méthode non statique sur l'instance
                    instance->startOCR(); // Utiliser l'instance pour appeler startOCR
                }
            }
        }
    }
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

void MainWindow::InstallKeyboardHook()
{
    if (!hKeyboardHook) {
        hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    }
}

void MainWindow::UninstallKeyboardHook()
{
    if (hKeyboardHook) {
        UnhookWindowsHookEx(hKeyboardHook);
        hKeyboardHook = NULL;
    }
}

void MainWindow::on_actionOpen_FIle_triggered()
{

    QString filePath = QFileDialog::getOpenFileName(this, "Open File");

    if(ui->tabWidget->currentWidget() == ui->tab_7)
    {
        openFile(filePath);
        if(filePath.endsWith(ui->label_3->text()))
        {
            searchBookmark();
        }
    }
    else if(ui->tabWidget->currentWidget() == ui->tab_8)
    {
        translateFile(filePath);
    }
}

void MainWindow::on_actionOpen_Folder_triggered() // permet d'afficher un dossier dans le QTreeView
{
    QUrl dirPath = QFileDialog::getExistingDirectory(this, "Open Folder", "/", QFileDialog::ShowDirsOnly);
    // ouvre une fenêtre de dialogue pour les dossiers

    dirModel->setRootPath(dirPath.toString()); // initialise le chemin racine
    ui->treeView->setModel(dirModel); // initialise le modèle à afficher pour 'treeView'
    ui->treeView->setRootIndex(dirModel->index(dirPath.toString())); // initialise le dossier racine à afficher

    ui->treeView->hideColumn(1); // cache la colone qui affiche le 'Size'
    ui->treeView->hideColumn(2); // cache la colone qui affiche le 'Type'
    ui->treeView->hideColumn(3); // cache la colone qui affiche le 'Date Modified'

    ui->treeView->setMinimumWidth(120);
    ui->treeView->setMaximumWidth(250);
}

void MainWindow::openQTreeViewFile(QModelIndex index) // ouvre un fichier séletionné à partir du QTreeView
{
    QString filePath = dirModel->fileInfo(index).absoluteFilePath(); // récupère le chemin du fichier à partir de son index dans 'treeView'
    openFile(filePath);
}

void MainWindow::on_pushButton_5_clicked() // ajouter un marque page
{
    addBookmark(ui->label_3->text(), ui->stackedWidget->currentIndex());
}

void MainWindow::addBookmark(QString name, int page)
{
    QFile file(QString("bookmark/bookmarks.nbm"));
    QTextStream in(&file);
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open bookmark file : " + file.errorString());
        return;
    }
    QString content = in.readAll();
    file.close();

    QTextStream out(&file);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save bookmark : " + file.errorString());
        return;
    }

    QString bookmark = QString("\n%1::%2").arg(name).arg(page);
    if(!content.contains(bookmark))
    {
        content.push_back(bookmark);
        out << content;
    }

    file.close();
    searchBookmark();
}

void MainWindow::on_pushButton_6_clicked() // suprime le marque page actuel
{
    if(ui->comboBox_4->currentIndex() != 0)
    {
        QFile file(QString("bookmark/bookmarks.nbm"));
        QTextStream in(&file);
        if(!file.open(QIODevice::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "Warning", "Cannot open bookmark file : " + file.errorString());
            return;
        }
        QString content = in.readAll();
        file.close();

        QTextStream out(&file);

        if (!file.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::warning(this, "Warning", "Cannot save bookmark : " + file.errorString());
            return;
        }

        QList<QString> currentBookmark = ui->comboBox_4->currentText().split(" ");
        content.remove(QString("\n%1::%2").arg(ui->label_3->text()).arg(currentBookmark[1].toInt()-1));
        out << content;

        file.close();

        ui->comboBox_4->removeItem(ui->comboBox_4->currentIndex());
        searchBookmark();
    }
}

void MainWindow::searchBookmark()
{
    ui->comboBox_4->clear();
    ui->comboBox_4->addItem("-- Choose Bookmark --");

    QFile file(QString("bookmark/bookmarks.nbm"));
    QTextStream in(&file);

    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open bookmark file : " + file.errorString());
        return;
    }

    while(!in.atEnd())
    {
        QString line = in.readLine();
        qDebug() << line;

        if(line.contains(ui->label_3->text()))
        {
            QList<QString> bookmarkInfo = line.split("::");
            ui->comboBox_4->addItem(QString("Page %1").arg(bookmarkInfo[1].toInt()+1));
        }
    }
}

void MainWindow::on_comboBox_4_activated(int index) // utilise le bookmark choisi
{
    if(ui->comboBox_4->currentText() != "" && ui->comboBox_4->currentText() != "-- Choose Bookmark --")
    {
        QList<QString> bookmarkPage = ui->comboBox_4->currentText().split(" ");

        ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(bookmarkPage[1].toInt()-1)); // la page deviendra le numéro entré
        ui->lineEdit->setText(QString("%1").arg(ui->stackedWidget->currentIndex()+1)); // affiche le numéro de la page actuelle

        QFrame* frame = ui->stackedWidget->currentWidget()->findChild<QFrame*>();
        frame->adjustSize();
    }
}

void MainWindow::startProcess()
{
    process = new QProcess(this);

    QString scriptPath = "python/serv.py";
    QList<QString> argList;
    argList.push_back(ui->comboBox->currentText());
    argList.push_back(ui->comboBox_2->currentText());

    process->start("python/python311/python.exe", QStringList() << scriptPath << argList);

    connectToHost();

}

void MainWindow::on_pushButton_4_clicked() // page précédente
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
    ui->lineEdit->setText(QString("%1").arg(ui->stackedWidget->currentIndex()+1)); // affiche le numéro de la page actuelle

    QFrame* frame = ui->stackedWidget->currentWidget()->findChild<QFrame*>();
    frame->adjustSize();
}


void MainWindow::on_pushButton_3_clicked() // page suivante
{
    //pressButton();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    ui->lineEdit->setText(QString("%1").arg(ui->stackedWidget->currentIndex()+1)); // affiche le numéro de la page actuelle

    QFrame* frame = ui->stackedWidget->currentWidget()->findChild<QFrame*>();
    frame->adjustSize();
}

void MainWindow::on_lineEdit_returnPressed() // va à la page cible
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(ui->lineEdit->text().toInt()-1)); // la page deviendra le numéro entré
    ui->lineEdit->setText(QString("%1").arg(ui->stackedWidget->currentIndex()+1)); // affiche le numéro de la page actuelle

    QFrame* frame = ui->stackedWidget->currentWidget()->findChild<QFrame*>();
    frame->adjustSize();
}

void MainWindow::changeFontSize() // change la taille de la police d'éciture
{
    ui->lineEdit_2->setText(QString("%1").arg(fontSize));

    QList<QLabel*> listLabel = ui->stackedWidget->findChildren<QLabel*>();
    QFrame* frame = ui->stackedWidget->currentWidget()->findChild<QFrame*>();

    for (const auto& l : listLabel) {
        QFont font = l->font();
        font.setPointSize(fontSize);
        l->setFont(font);
    }

    frame->adjustSize();

    on_pushButton_3_clicked();
    on_pushButton_4_clicked();
}

void MainWindow::on_pushButton_2_clicked() // police d'écriture + grande
{
    fontSize-=initialfontSize*0.1;

    changeFontSize();
}


void MainWindow::on_pushButton_clicked() // police d'écriture + petite
{
    fontSize+=initialfontSize*0.1;

    changeFontSize();
}


void MainWindow::on_lineEdit_2_returnPressed() // initialise la taille cible de la police d'écriture
{
    fontSize = ui->lineEdit_2->text().toInt();
    qDebug() << fontSize;

    changeFontSize();
}

void MainWindow::textBecomeSelectable() // permet au text de devenir sélectionnable et installe le filtre de détection de clique
{
    QList<QLabel*> listLabel = ui->stackedWidget->findChildren<QLabel*>();

    for (const auto& l : listLabel) { // pour tous les 'QLabel' de la liste
        i++;
        l->setTextInteractionFlags(Qt::TextSelectableByMouse); // rend le 'QLabel' selectionnable
        l->installEventFilter(this); // filtre intercepte les évennements de la souris
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) // détecte s'il y a eu un clique sur un label
{
    if (event->type() == QEvent::MouseButtonRelease) { // si il y a un évennement de clique relaché, on saura que c'est sur un 'QLabel' grâce au filtre
        QLabel *label = qobject_cast<QLabel*>(watched); // 'watched' renvoie un pointeur de type 'QObjet' du label précis sur lequel l'évennement est déclenché
        // 'qobject_cast' convertie le 'QObject*' en 'QLabel*'

        int index = ui->stackedWidget->currentIndex();
        label->setText(originalsTextsLabels[index]);

        if (label && label->hasSelectedText()) { // si 'label' n'est pas vide et si du texte est sélectionné
            QString selectedText = label->selectedText();

            QString prevC;

            selectedText = selectedText.replace("\u2028", "<br>"); // remplace les séparateurs de ligne par des sauts de lignes
            selectedText = selectedText.replace("\u2029", "<br>"); // remplace les séparateurs de paragraphes par des sauts de lignes

            qDebug() << "Texte sélectionné : " << selectedText;

            QString selectedTextToTranslate = selectedText; // text à traduire uniquement
            selectedTextToTranslate = selectedTextToTranslate.replace("<br><br>", " ");
            selectedTextToTranslate = selectedTextToTranslate.replace("<br>", " ");
            QString translatedText = translateLabel(ui->comboBox->currentText(), ui->comboBox_2->currentText(), selectedTextToTranslate);
            // color la traduction en rouge

            QString selectedText2 = selectedText; // pour que ça ne remplace pas les caractères de la variables 'selectedText'
            QString newSelectedText = selectedText2.replace("<br><br>", " <br><br>");
            newSelectedText = newSelectedText.replace("<br>", " <br>");
            QString newTranslatedText = translatedText.replace("<br>", " ");

            QList<QString> wordsSelected = selectedText2.split(' ');
            QList<QString> wordsTranslated = newTranslatedText.split(' ');

            newTranslatedText.clear();

            int i_word = 0;

            if(selectedText.contains("<br>"))
            {
                if(wordsTranslated.length() >= wordsSelected.length())
                {
                    for (auto word : wordsSelected)
                    {
                        if(i > 0)
                        {
                            newTranslatedText.push_back(' ');
                        }
                        if(word.contains("<br>"))
                        {
                            newTranslatedText.push_back("<br>");
                        }
                        if(word.contains("<br><br>"))
                        {
                            newTranslatedText.push_back("<br>");
                        }
                        newTranslatedText.push_back(wordsTranslated[i_word]);

                        i_word++;
                    }
                    if(wordsSelected.length() < wordsTranslated.length())
                    {
                        int i2 = 0;
                        for (auto word : wordsTranslated) {
                            if(i2 >= wordsSelected.length())
                            {
                                newTranslatedText.push_back(" ");
                                newTranslatedText.push_back(word);
                            }
                            i2++;
                        }
                    }
                }
                else
                {
                    for (auto word : wordsTranslated)
                    {
                        i2++;
                        newTranslatedText.push_back(" ");
                        newTranslatedText.push_back(word);
                        if(i2 == wordsTranslated.length()-1)
                        {
                            if(selectedText.contains("<br><br>"))
                            {
                                newTranslatedText.push_back("<br>");
                            }
                            newTranslatedText.push_back("<br>");
                        }
                    }
                }
            }
            else
            {
                newTranslatedText.push_back(translatedText);
            }

            QString RedtranslatedText = QString("<font color=\"red\">%1</font>").arg(newTranslatedText);

            qDebug() << "traduction en rouge : " << RedtranslatedText;

            label->setOpenExternalLinks(true); // Permettre le traitement du texte comme du HTML
            QString textWithN = label->text().replace("\n", "<br>"); // garde les sauts de ligne en les replaçant par des balises html de saut de ligne
            textWithN = textWithN.replace('\t', ' ');
            textWithN = textWithN.replace("  ", " ");

            //QString newText = "<span style=\"white-space: pre;\">" + textWithN.replace(selectedText, translatedText) + "</span>"; // garde les enchaînement d'espace
            QString newText = textWithN.replace(selectedText, RedtranslatedText);
            label->setText(newText);
            connectToHost(); // se reconnecte juste après l'affichage de la traduction pour préparer la prochaine traduction
        }
    }
    return QMainWindow::eventFilter(watched, event); // return true si l'évennement est traité, return false si non
}

bool MainWindow::connectToHost() // se connect au serveur
{
    socket = new QTcpSocket(this);
    socket->connectToHost("localhost", 12345);

    //return socket->waitForConnected();
    return true;
}

bool MainWindow::sendTranslationData(QString sourceLang, QString targetLang, QString text) // envoie le text a traduire au serveur
{
    qDebug() << "Sending translation request...";
    QString message = QString("%1/%2/%3").arg(sourceLang, targetLang, text);
    qDebug() << message;
    socket->write(message.toUtf8());


    return socket->waitForReadyRead();
}

QString MainWindow::translateLabel(QString sourceLang, QString targetLang, QString text) // récupère la traduction reçu par le serveur
{
    /*page = new QWebEnginePage(this);
    QWebEngineSettings *settings = page->settings();
    settings->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    connect(page, &QWebEnginePage::loadFinished, this, &MainWindow::pageload);
    page->load(QUrl(QString("https://www.deepl.com/translator#%1/%2/%3").arg(sourceLang).arg(targetLang).arg(text)));*/

    QString translation;


        if(sendTranslationData(sourceLang, targetLang, text))
        {
            QByteArray response = socket->readAll();
            qDebug() << "Server response:" << response;
            translation = QString::fromUtf8(response);
        }


    numberTranslation++;
    qDebug() << numberTranslation;

    if(numberTranslation == 20 && ui->tabWidget->currentWidget() == ui->tab_8)
    {
        numberTranslation = 0;
        translateLabel("close", "close", "REFRESHAPP");
        /*process->terminate();
        startProcess();
        QTimer::singleShot(5000, []{
            qDebug("Timer while the Deepl loading");
        });*/
    }
    else if(numberTranslation == 45)
    {
        numberTranslation = 0;
        translateLabel("close", "close", "REFRESHAPP");
        /*process->terminate();
        startProcess();
        QTimer::singleShot(5000, []{
            qDebug("Timer while the Deepl loading");
        });*/
    }

    return QString(translation);
}

void MainWindow::on_comboBox_7_currentTextChanged(const QString &arg1) // change la langue source de l'OCR
{
    translateLabel("close", "close", "CLOSEAPP");
    process->close();

    process = new QProcess(this);

    QString scriptPath = "python/serv.py";
    QList<QString> argList;
    argList.push_back(arg1);
    argList.push_back(ui->comboBox_8->currentText());

    process->start("python/python311/python.exe", QStringList() << scriptPath << argList);
}

void MainWindow::on_comboBox_8_currentTextChanged(const QString &arg1) // change la langue cible de l'OCR
{
    translateLabel("close", "close", "CLOSEAPP");
    process->close();

    process = new QProcess(this);

    QString scriptPath = "python/serv.py";
    QList<QString> argList;
    argList.push_back(ui->comboBox_7->currentText());
    argList.push_back(arg1);

    process->start("python/python311/python.exe", QStringList() << scriptPath << argList);
}

void MainWindow::on_comboBox_9_currentIndexChanged(int index) // affiche ou cache Deepl
{
    translateLabel("close", "close", "CLOSEAPP");
    process->close();

    process = new QProcess(this);
    QString scriptPath = "python/serv.py";
    QList<QString> argList;
    argList.push_back(ui->comboBox_7->currentText());
    argList.push_back(ui->comboBox_8->currentText());

    if(index == 1)
    {
        argList.push_back("HIDE");
    }
    process->start("python/python311/python.exe", QStringList() << scriptPath << argList);
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1) // change la langue source si la valeur de la combo box a changé
{
    translateLabel("close", "close", "CLOSEAPP");
    process->close();

    process = new QProcess(this);

    QString scriptPath = "python/serv.py";
    QList<QString> argList;
    argList.push_back(arg1);
    argList.push_back(ui->comboBox_2->currentText());

    process->start("python/python311/python.exe", QStringList() << scriptPath << argList);
}

void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1) // change la langue cible si la valeur de la combo box a changé
{
    translateLabel("close", "close", "CLOSEAPP");
    process->close();

    process = new QProcess(this);

    QString scriptPath = "python/serv.py";
    QList<QString> argList;
    argList.push_back(ui->comboBox->currentText());
    argList.push_back(arg1);

    process->start("python/python311/python.exe", QStringList() << scriptPath << argList);
}

void MainWindow::resizeEvent(QResizeEvent *event) // détecte quand la fenêtre change de taille
{
    QMainWindow::resizeEvent(event);

    QList<QScrollArea*> scrollAreaList = ui->stackedWidget->findChildren<QScrollArea*>();
    if(!MainWindow::isMinimized() && !MainWindow::isMaximized())
    {
        qDebug() << "fenetre resize : max";
        for (const auto& s : scrollAreaList) {
            QScrollBar* hScrollBar = s->horizontalScrollBar();
            hScrollBar->setValue(this->width()); // mets la scroll bar horizontal au milieu
        }

        wereMaximised = true;
    }

    else if(!MainWindow::isMinimized() && wereMaximised == true)
    {
        qDebug("fenetre resize : min");
        for (const auto& s : scrollAreaList) {
            QScrollBar* hScrollBar = s->horizontalScrollBar();
            hScrollBar->setValue(this->width()); // mets la scroll bar horizontal au milieu
        }
    }


    /*if(MainWindow::isMaximized())
    {
        wereMaximised = true;
        for (const auto& s : scrollAreaList) {
            QScrollBar* hScrollBar = s->horizontalScrollBar();
            hScrollBar->setValue(this->width()/2); // mets la scroll bar horizontal au milieu
        }
    }
    if(!MainWindow::isMinimized() && wereMaximised == true)
    {
        QMainWindow::resizeEvent(event);
        // Your code here.
        qDebug() << "fenetre resize";
        QList<QScrollArea*> scrollAreaList = ui->stackedWidget->findChildren<QScrollArea*>();

        for (const auto& s : scrollAreaList) {
            QScrollBar* hScrollBar = s->horizontalScrollBar();
            hScrollBar->setValue(this->width()); // mets la scroll bar horizontal au milieu
        }

        wereMaximised = false;
    }*/
}

void MainWindow::returnTranslatedText()
{
    // Script JavaScript pour récupérer le texte d'un élément spécifique sur la page
    // [data-testid="translator-target-input"]
    /*QString jsScript = R"(
        var specificElement = document.querySelector('[id="textareasContainer"]');
        if (specificElement) {
            specificElement.innerText.trim();
        } else {
            'Élément spécifié non trouvé';
        }
    )";
    // Exécuter le script JavaScript et récupérer le résultat

    QTimer::singleShot(1000, [this, jsScript]() {
        page->runJavaScript(jsScript, [](const QVariant &result){
            if (result.isValid()) {
                QString specificText = result.toString();
                if (!specificText.isEmpty()) {
                    qDebug() << "Texte spécifique récupéré avec succès:";
                    qDebug().noquote() << specificText; // Afficher le texte récupéré
                } else {
                    qDebug() << "Le texte spécifique est vide.";
                }
            } else {
                qDebug() << "Échec de la récupération du texte spécifique.";
            }
        });
    });*/
}

void MainWindow::injectText()
{
    /*qDebug() << "page chargée";
    QString jsScript = R"(
            (function() {
                var textarea = document.querySelector('[data-testid="translator-source-input"]');
                if (textarea) {
                    textarea.value = 'Hello World'; // Injecter le texte dans le champ de texte
                    return true;
                }
                return false;
            })();
        )";
    //page->runJavaScript(QString("document.querySelector('[data-testid=\"translator-source-input\"]').value = 'hello world'"));
    page->runJavaScript(jsScript, [this](const QVariant &result){
        if(result.toBool())
        {
            qDebug() << "java script injecté";
            // Après avoir injecté du texte, ajoutez un espace pour déclencher un événement
            returnTranslatedText();
        }

        else {
            qDebug() << "no";
        }
    });*/
}

