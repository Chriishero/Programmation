#include "mainwindow.h"
#include "qobjectdefs.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Simple GameEngine");

    ui->tabWidget_2->removeTab(1);
    ui->tabWidget_2->setTabsClosable(true);

    ui->tabWidget_3->removeTab(1);
    ui->tabWidget_3->setTabsClosable(true);

    m_view = new QGraphicsView(this);
    m_scene = new AreaScene(this, ui->spinBox->value());

    m_view->setScene(m_scene);

    m_view->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_view->centerOn(0,0);

    ui->verticalLayout->addWidget(m_view);

    widgetList.push_back(ui->pushButton);
    widgetList.push_back(ui->pushButton_2);
    widgetList.push_back(ui->pushButton_5);
    widgetList.push_back(ui->spinBox);
    widgetList.push_back(ui->comboBox);

    connect(ui->pushButton_2, SIGNAL(clicked(bool)), SLOT(startGame()));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), SLOT(stopGame()));
    connect(ui->pushButton_5, SIGNAL(clicked(bool)), SLOT(resetGame()));
    connect(ui->tabWidget_2, SIGNAL(tabCloseRequested(int)), this, SLOT(deleteEntity(int)));
    connect(ui->tabWidget_3, SIGNAL(tabCloseRequested(int)), this, SLOT(deleteItem(int)));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), SLOT(setAreaSize()));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), SLOT(setAreaSize()));
    connect(ui->pushButton, SIGNAL(clicked(bool)), SLOT(addEntity()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), SLOT(addItem()));

    thread = new QThread();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    ui->tabWidget->setDisabled(true);
    foreach (auto w, widgetList) {
        w->setDisabled(true);
    }
    foreach (auto e, m_scene->m_entities) {
        e->setData(1, e->pos().x());
        e->setData(2, e->pos().y());
        if(!e->data(0).toString().contains("Player"))
        {
            e->setFlag(QGraphicsItem::ItemIsMovable, false);
        }
    }
    foreach (auto i, m_scene->m_items) {
        i->setData(1, i->pos().x());
        i->setData(2, i->pos().y());
    }
    finishCondition();

    worker* workerCondition = new worker();

    connect(thread, &QThread::started, workerCondition, &worker::checkCondition);
    connect(thread, &QThread::finished, workerCondition, &worker::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(this, &MainWindow::stopThread, this, &MainWindow::stopGame);

    connect(workerCondition, &worker::check, this, &MainWindow::checkWinCondition);
    connect(workerCondition, &worker::deplacement, this, &MainWindow::deplacementPNJ);

    workerCondition->moveToThread(thread);
    thread->start();
    gameStarted = true;
}

void MainWindow::stopGame()
{
    gameStarted = false;
    nRC = 0;
    thread->quit();
    ui->tabWidget->setDisabled(false);
    foreach (auto w, widgetList) {
        w->setDisabled(false);
    }
    foreach (auto e, m_scene->m_entities) {
        if(!e->data(0).toString().contains("Player"))
        {
            e->setFlag(QGraphicsItem::ItemIsMovable, true);
        }
    }
}

void MainWindow::resetGame()
{
    foreach (auto e, m_scene->m_entities) {
        m_scene->removeItem(e);
        m_scene->QGraphicsScene::addItem(e);
        e->setPos(e->data(1).toInt(), e->data(2).toInt());
        e->setm_initialX(e->data(1).toInt());
        e->setm_initialY(e->data(2).toInt());
        e->setm_PV(e->getm_initialPV());
        e->setm_attackPoint(e->getm_initialAttackPoint());
    }
    foreach (auto i, m_scene->m_items) {
        m_scene->removeItem(i);
        m_scene->QGraphicsScene::addItem(i);
        i->setPos(i->data(1).toInt(), i->data(2).toInt());
    }
}

void MainWindow::finishCondition()
{
    winConditionList.clear();
    defeatConditionList.clear();
    allWinConditionList.clear();
    allDefeatConditionList.clear();
    QString condition;
    int i = 0;
    int ispin = 0;
    foreach (auto w, winConditionsComboboxList) {
        if(i <= 2)
        {
            if(w->currentText().contains("else"))
            {
                allWinConditionList.push_back(winConditionList);
                winConditionList.clear();
            }
            condition.push_back(w->currentText());
            condition.push_back('|');
            i++;
        }
        else
        {
            condition.push_back(w->currentText());
            condition.push_back('|');
            if(ispin < winConditionsSpinboxList.size())
            {
               condition.push_back(winConditionsSpinboxList[ispin]->text());
            }
            winConditionList.push_back(condition);
            condition.clear();
            ispin++;
            i = 0;
        }
    }
    allWinConditionList.push_back(winConditionList);

    foreach (auto a, allWinConditionList) {
        qDebug("début list");
        QString test;
        foreach (auto e, a) {
            test.push_back(e);
        }
        qDebug() << test;
    }

    i = 0;
    ispin = 0;
    foreach (auto w, defeatConditionsComboboxList) {
        if(i <= 2)
        {
            if(w->currentText().contains("else"))
            {
                allDefeatConditionList.push_back(defeatConditionList);
                defeatConditionList.clear();
            }
            condition.push_back(w->currentText());
            condition.push_back('|');
            i++;
        }
        else
        {
            condition.push_back(w->currentText());
            condition.push_back('|');
            if(ispin < defeatConditionsSpinboxList.size())
            {
                condition.push_back(defeatConditionsSpinboxList[ispin]->text());
            }
            defeatConditionList.push_back(condition);
            condition.clear();
            ispin++;
            i = 0;
        }
    }
    allDefeatConditionList.push_back(defeatConditionList);

    foreach (auto a, allDefeatConditionList) {
        qDebug("début list");
        QString test;
        foreach (auto e, a) {
            test.push_back(e);
        }
        qDebug() << test;
    }
}

void MainWindow::checkWinCondition()
{
    if(gameStarted == true)
    {
        foreach (auto l, allWinConditionList)
        {
            for (int i = 0; i < l.size(); ++i) {
                if(i == 0)
                {
                    nRC = 0;
                }
                if(l[i] == "")
                {
                    allWinConditionList.pop_back();
                    nRC--;
                }
                QList<QString> condition = l[i].split("|");
                Entity* entity;
                int attribut;
                int target = condition[4].toInt();
                foreach (auto e, condition) {
                    qDebug() << e;
                }

                foreach (auto o, m_scene->m_entities) {
                    if(o->data(0).toString().contains(condition[1]))
                    {
                        entity = o;
                    }
                }
                if(condition[2] == "PV")
                {
                    attribut = entity->getm_PV();
                }
                else if(condition[2] == "Attack Point")
                {
                    attribut = entity->getm_attackPoint();
                }
                if(condition[3] == "==")
                {
                    if(attribut == target)
                    {
                        nRC++;
                        qDebug() << "nRightCondition : " << nRC << " / " << l.size();
                        if(nRC == l.size())
                        {
                            qDebug() << "You Win";
                            emit stopThread();
                        }
                    }
                }
                else if (condition[3] == ">") {
                    if(attribut > target)
                    {
                        nRC++;
                        qDebug() << "nRightCondition : " << nRC << " / " << l.size();
                        if(nRC == l.size())
                        {
                            qDebug() << "You Win";
                            emit stopThread();
                        }
                    }
                }
                else if (condition[3] == "<") {
                    if(attribut < target)
                    {
                        nRC++;
                        qDebug() << "nRightCondition : " << nRC << " / " << l.size();
                        if(nRC == l.size())
                        {
                            qDebug() << "You Win";
                            emit stopThread();
                        }
                    }
                }
                else if (condition[3] == ">=") {
                    if(attribut >= target)
                    {
                        nRC++;
                        qDebug() << "nRightCondition : " << nRC << " / " << l.size();
                        if(nRC == l.size())
                        {
                            qDebug() << "You Win";
                            emit stopThread();
                        }
                    }
                }
                else if (condition[3] == "<=") {
                    if(attribut <= target)
                    {
                        nRC++;
                        qDebug() << "nRightCondition : " << nRC << " / " << l.size();
                        if(nRC == l.size())
                        {
                            qDebug() << "You Win";
                            emit stopThread();
                        }
                    }
                }
                else if (condition[3] == "!=") {
                    if(attribut != target)
                    {
                        nRC++;
                        qDebug() << "nRightCondition : " << nRC << " / " << l.size();
                        if(nRC == l.size())
                        {
                            qDebug() << "You Win";
                            emit stopThread();
                        }
                    }
                }
            }
        }
        foreach (auto l, allDefeatConditionList)
        {
            int nRC = 0;
            for (int i = 0; i < l.size(); ++i) {
                if(i == 0)
                {
                    nRC = 0;
                }
                QList<QString> condition = l[i].split("|");
                Entity* entity;
                int attribut;
                int target = condition[4].toInt();
                foreach (auto e, condition) {
                    qDebug() << e;
                }

                foreach (auto o, m_scene->m_entities) {
                    if(o->data(0).toString().contains(condition[1]))
                    {
                        entity = o;
                    }
                }
                if(condition[2] == "PV")
                {
                    attribut = entity->getm_PV();
                }
                if(condition[2] == "Attack Point")
                {
                    attribut = entity->getm_attackPoint();
                }
                if(condition[2] == "Step Size")
                {
                    attribut = entity->getm_sizeStep()/50;
                }
                if(condition[3] == "==")
                {
                    if(attribut == target)
                    {
                        nRC++;
                        qDebug() << "nRightCondition : " << nRC << " / " << l.size();
                        if(nRC == l.size())
                        {
                            qDebug() << "Game Over.";
                            emit stopThread();
                        }
                    }
                }
                else if (condition[3] == ">") {
                    if(attribut > target)
                    {
                        nRC++;
                        qDebug() << "nRightCondition : " << nRC << " / " << l.size();
                        if(nRC == l.size())
                        {
                            qDebug() << "Game Over.";
                            emit stopThread();
                        }
                    }
                }
                else if (condition[3] == "<") {
                    if(attribut < target)
                    {
                        nRC++;
                        qDebug() << "nRightCondition : " << nRC << " / " << l.size();
                        if(nRC == l.size())
                        {
                            qDebug() << "Game Over.";
                            emit stopThread();
                        }
                    }
                }
                else if (condition[3] == ">=") {
                    if(attribut >= target)
                    {
                        nRC++;
                        qDebug() << "nRightCondition : " << nRC << " / " << l.size();
                        if(nRC == l.size())
                        {
                            qDebug() << "Game Over.";
                            emit stopThread();
                        }
                    }
                }
                else if (condition[3] == "<=") {
                    if(attribut <= target)
                    {
                        nRC++;
                        qDebug() << "nRightCondition : " << nRC << " / " << l.size();
                        if(nRC == l.size())
                        {
                            qDebug() << "Game Over.";
                            emit stopThread();
                        }
                    }
                }
                else if (condition[3] == "!=") {
                    if(attribut != target)
                    {
                        nRC++;
                        qDebug() << "nRightCondition : " << nRC << " / " << l.size();
                        if(nRC == l.size())
                        {
                            qDebug() << "Game Over.";
                            emit stopThread();
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::deplacementPNJ()
{
    if(gameStarted == true)
    {
        foreach (auto &e, m_scene->m_entities) {
            QString entityName;
            random = false;
            if(!e->data(0).toString().contains("Player") && e->getdeplacement_frequence() > 0 && (e->getcoutdownDeplacement() == 0 ||
                e->getcoutdownDeplacement() == e->getdeplacement_frequence()))
            {
                e->setcoutdownDeplacement(1);
                if(e->data(0).toString().contains("PNJ"))
                {
                    entityName = "PNJ";
                }
                else
                {
                    entityName = "Ennemie";
                }
                qDebug() << entityName << " : " << e->getdeplacement_patern();
                if(e->getdeplacement_patern() == "Random")
                {
                    random = true;
                    srand(QTime::currentTime().msec()); // initialise le générateur à l'heure courante
                    int randomMove = rand() % 4 + 1;
                    if(randomMove == 1)
                    {
                        e->setdeplacement_patern("Up");
                    }
                    else if(randomMove == 2)
                    {
                        e->setdeplacement_patern("Down");
                    }
                    else if(randomMove == 3)
                    {
                        e->setdeplacement_patern("Left");
                    }
                    else if(randomMove == 4)
                    {
                        e->setdeplacement_patern("Right");
                    }
                }
                if(e->getdeplacement_patern() == "Up")
                {
                    if(e->pos().y()-50 >= 0)
                    {
                        e->setPos(e->pos().x(), e->pos().y()-50);
                        m_scene->deplacementObject(entityName);
                        qDebug() << e->pos();
                    }
                    else
                    {
                        e->setdeplacement_patern("Down");
                    }
                }
                if(e->getdeplacement_patern() == "Down")
                {
                    if(e->pos().y()+50 >= 0 && e->pos().y()+50 <= (m_scene->getSceneSize()-2)*50)
                    {
                        e->setPos(e->pos().x(), e->pos().y()+50);
                        m_scene->deplacementObject(entityName);
                        qDebug() << e->pos();
                    }
                    else
                    {
                        e->setdeplacement_patern("Up");
                    }
                }
                if(e->getdeplacement_patern() == "Left")
                {
                    if(e->pos().x()-50 >= 0)
                    {
                        e->setPos(e->pos().x()-50, e->pos().y());
                        m_scene->deplacementObject(entityName);
                        qDebug() << e->pos();
                    }
                    else
                    {
                        e->setdeplacement_patern("Right");
                    }
                }
                if(e->getdeplacement_patern() == "Right")
                {
                    if(e->pos().x()+50 >= 0 && e->pos().x()+50 <= (m_scene->getSceneSize()-2)*50)
                    {
                        e->setPos(e->pos().x()+50, e->pos().y());
                        m_scene->deplacementObject(entityName);
                        qDebug() << e->pos();
                    }
                    else
                    {
                        e->setdeplacement_patern("Left");
                    }
                }
                if(random == true)
                {
                    e->setdeplacement_patern("Random");
                }
            }
            else if(!e->data(0).toString().contains("Player"))
            {
                e->setcoutdownDeplacement(e->getcoutdownDeplacement()+1);
            }
            else
            {
                qDebug() << e->data(0).toString();
            }
        }
    }
}

void MainWindow::setAreaSize()
{
    qDebug() << ui->spinBox->value();
    m_scene->setSceneSize(ui->spinBox->value());
    m_view->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_view->centerOn(0,0);
}

void MainWindow::addEntity()
{
    if(ui->comboBox->currentText() == "Player")
    {
        m_scene->addPlayer();
    }
    else if(ui->comboBox->currentText() == "Ennemie")
    {
       m_scene->addPnj(true);
    }
    else if(ui->comboBox->currentText() == "PNJ")
    {
        m_scene->addPnj(false);
    }

    QVariant data = m_scene->m_entities.last()->data(0);

    objectFrame = new QFrame(this);
    int index = ui->tabWidget_2->addTab(objectFrame, data.toString());
    ui->tabWidget_2->setCurrentIndex(index);

    addEntityParameters(data.toString());

    if(ui->tabWidget_2->tabText(0) == "Tab 1")
    {
        ui->tabWidget_2->removeTab(0);
    }

    ui->tabWidget->setCurrentIndex(0);
    if(!winConditionsComboboxList.isEmpty())
    {
        objectComboBox->clear();
        foreach (auto o, m_scene->m_objects){
            objectComboBox->addItem(o->data(0).toString());
        }
    }
}

void MainWindow::addEntityParameters(QString entityData)
{
    foreach (auto e, m_scene->m_entities) {
        QVariant data = e->data(0);
        if(data.toString() == entityData)
        {
            frameLayout = new QVBoxLayout(objectFrame);

            spinBoxLayout = new QHBoxLayout(objectFrame);
            stepsSizeLabel = new QLabel("Steps Size : ", objectFrame);
            m_stepsSizeSpinBox = new QSpinBox(objectFrame);
            m_stepsSizeSpinBox->setObjectName("SS");

            PVSpinBoxLayout = new QHBoxLayout(objectFrame);
            PVLabel = new QLabel("PV : ", objectFrame);
            PVSpinBox = new QSpinBox(objectFrame);
            PVSpinBox->setObjectName("PV");

            attackSpinBoxLayout = new QHBoxLayout(objectFrame);
            attackLabel = new QLabel("Attack Point : ", objectFrame);
            attackSpinBox = new QSpinBox(objectFrame);
            attackSpinBox->setObjectName("APoint");

            m_stepsSizeSpinBox->setValue(1);
            connect(m_stepsSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [this, e]() {
                setSizeStep(e);
            });
            PVSpinBox->setValue(10);
            connect(PVSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [this, e]() {
                setPV(e);
            });
            attackSpinBox->setValue(1);
            connect(attackSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [this, e]() {
                setAttackPoint(e);
            });

            spinBoxLayout->addWidget(stepsSizeLabel);
            spinBoxLayout->addWidget(m_stepsSizeSpinBox);
            PVSpinBoxLayout->addWidget(PVLabel);
            PVSpinBoxLayout->addWidget(PVSpinBox);
            attackSpinBoxLayout->addWidget(attackLabel);
            attackSpinBoxLayout->addWidget(attackSpinBox);

            frameLayout->addLayout(spinBoxLayout);
            frameLayout->addLayout(PVSpinBoxLayout);
            frameLayout->addLayout(attackSpinBoxLayout);

            if(!entityData.contains("Player"))
            {
                AFSpinBoxLayout = new QHBoxLayout(objectFrame);
                AFLabel = new QLabel("Deplacement Frequence : ", objectFrame);
                AFSpinBox = new QSpinBox(objectFrame);
                AFSpinBox->setObjectName("AF");

                APComboBoxLayout = new QHBoxLayout(objectFrame);
                APLabel = new QLabel("Deplacement Paterne : ", objectFrame);
                APComboBox = new QComboBox(objectFrame);
                APComboBox->addItems(QStringList() << "Random" << "Up" << "Down" << "Left" << "Right");
                APComboBox->setObjectName("APatern");

                connect(AFSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [this, e]() {
                    setDeplacementFrequence(e);
                });
                connect(APComboBox, QOverload<const QString&>::of(&QComboBox::currentTextChanged), this, [this, e]() {
                    setDeplacementPatern(e);
                });

                APComboBoxLayout->addWidget(APLabel);
                APComboBoxLayout->addWidget(APComboBox);
                AFSpinBoxLayout->addWidget(AFLabel);
                AFSpinBoxLayout->addWidget(AFSpinBox);
                frameLayout->addLayout(AFSpinBoxLayout);
                frameLayout->addLayout(APComboBoxLayout);
            }
            break;
        }
    }
}

void MainWindow::setSizeStep(Entity *e)
{
    auto tab = ui->tabWidget_2->currentWidget();

    e->setm_sizeStep(tab->findChild<QSpinBox*>("SS")->value());
    qDebug() << e->data(0).toString() << "Step Size : " << e->getm_sizeStep();
}

void MainWindow::setPV(Entity *e)
{
    auto tab = ui->tabWidget_2->currentWidget();

    e->setm_PV(tab->findChild<QSpinBox*>("PV")->value());
    e->setm_initialPV(tab->findChild<QSpinBox*>("APoint")->value());
    qDebug() << e->data(0).toString() << "PV : " << e->getm_PV();
}

void MainWindow::setAttackPoint(Entity *e)
{
    auto tab = ui->tabWidget_2->currentWidget();

    e->setm_attackPoint(tab->findChild<QSpinBox*>("APoint")->value());
    e->setm_initialAttackPoint(tab->findChild<QSpinBox*>("APoint")->value());
    qDebug() << e->data(0).toString() << "attack point : " << e->getm_attackPoint();
}

void MainWindow::setDeplacementFrequence(Entity *e)
{
    auto tab = ui->tabWidget_2->currentWidget();

    e->setdeplacement_frequence(tab->findChild<QSpinBox*>("AF")->value());
    qDebug() << e->data(0).toString() << "Deplacement frequence : " << e->getdeplacement_frequence();
}

void MainWindow::setDeplacementPatern(Entity *e)
{
    auto tab = ui->tabWidget_2->currentWidget();

    e->setdeplacement_patern(tab->findChild<QComboBox*>("APatern")->currentText());
    qDebug() << e->data(0).toString() << "Deplacement patern : " << e->getdeplacement_patern();
}

void MainWindow::deleteEntity(int index)
{
    foreach (auto e, m_scene->m_entities) {
        QVariant data = e->data(0);
        if(data.toString() == ui->tabWidget_2->tabText(index))
        {
            auto listE = m_scene->m_entities;
            listE.clear();
            foreach (auto e2, m_scene->m_entities) {
                if(e2->data(0).toString() != ui->tabWidget_2->tabText(index))
                {
                    listE.append(e2);
                }
            }
            auto listO = m_scene->m_objects;
            listO.clear();
            foreach (auto e2, m_scene->m_objects) {
                if(e2->data(0).toString() != ui->tabWidget_2->tabText(index))
                {
                    listO.append(e2);
                }
            }
            m_scene->m_entities = listE;
            m_scene->m_objects = listO;

            m_scene->removeItem(e);
            qDebug() << data.toString() << ui->tabWidget_2->tabText(index);
            delete e;
        }
    }
    ui->tabWidget_2->removeTab(index);
    if(!winConditionsComboboxList.isEmpty())
    {
        objectComboBox->clear();
        foreach (auto o, m_scene->m_objects){
            objectComboBox->addItem(o->data(0).toString());
        }
    }
}

void MainWindow::addItem()
{
    m_scene->addPItem();

    QVariant data = m_scene->m_items.last()->data(0);

    objectFrame = new QFrame(this);
    int index = ui->tabWidget_3->addTab(objectFrame, data.toString());
    ui->tabWidget_3->setCurrentIndex(index);

    addItemParameters(data.toString());

    if(ui->tabWidget_3->tabText(0) == "Tab 1")
    {
        ui->tabWidget_3->removeTab(0);
    }
    ui->tabWidget->setCurrentIndex(1);

    if(!winConditionsComboboxList.isEmpty())
    {
        objectComboBox->clear();
        foreach (auto o, m_scene->m_objects){
            objectComboBox->addItem(o->data(0).toString());
        }
    }
}

void MainWindow::addItemParameters(QString itemData)
{
    foreach (auto i, m_scene->m_items) {
        QVariant data = i->data(0);
        if(data.toString() == itemData)
        {
            frameLayout = new QVBoxLayout(objectFrame);
            colorButton = new QPushButton("Change Color", objectFrame);

            eventLayout = new QHBoxLayout(objectFrame);
            eventLabel = new QLabel("Event : ", objectFrame);
            eventComboBox = new QComboBox(objectFrame);
            eventComboBox->addItem("--None--");
            eventComboBox->addItem("Heal PV");
            eventComboBox->addItem("Buff Attack");
            eventComboBox->addItem("Buff Step Size");
            eventComboBox->addItem("Inflicts Damage");
            eventComboBox->addItem("Debuff Attack");
            eventComboBox->addItem("Debuff Step Size");
            eventLayout->addWidget(eventLabel);
            eventLayout->addWidget(eventComboBox);

            connect(colorButton, &QPushButton::clicked, this, [this, i]() {
                setItemColor(i);
            });
            connect(eventComboBox, &QComboBox::currentTextChanged, this, [this, i]() {
                setItemEvent(i);
            });

            numberEventLayout = new QHBoxLayout(objectFrame);
            numberEventLabel = new QLabel("None : ", objectFrame);
            numberEventSpinBox = new QSpinBox(objectFrame);
            numberEventLayout->addWidget(numberEventLabel);
            numberEventLayout->addWidget(numberEventSpinBox);

            connect(numberEventSpinBox, &QSpinBox::valueChanged, this, [this, i](){
                setn_Event(i);
            });

            frameLayout->addWidget(colorButton);
            frameLayout->addLayout(eventLayout);
            frameLayout->addLayout(numberEventLayout);

            break;
        }
    }
}

void MainWindow::setItemColor(Item *i)
{
    QColor color = QColorDialog::getColor(Qt::yellow, this);
    i->setm_color(color);
}
void MainWindow::setItemEvent(Item *i)
{
    i->setm_event(eventComboBox->currentText());
    numberEventLabel->setText(eventComboBox->currentText());
    numberEventSpinBox->setValue(i->getn_Event());
}

void MainWindow::setn_Event(Item *i)
{
    i->setn_Event(numberEventSpinBox->value());
}

void MainWindow::deleteItem(int index)
{
    foreach (auto e, m_scene->m_items) {
        QVariant data = e->data(0);
        if(data.toString() == ui->tabWidget_3->tabText(index))
        {
            auto list = m_scene->m_items;
            list.clear();
            foreach (auto i, m_scene->m_items) {
                if(i->data(0).toString() != ui->tabWidget_3->tabText(index))
                {
                    list.append(i);
                }
            }
            auto listO = m_scene->m_objects;
            listO.clear();
            foreach (auto e2, m_scene->m_objects) {
                if(e2->data(0).toString() != ui->tabWidget_3->tabText(index))
                {
                    listO.append(e2);
                }
            }
            m_scene->m_objects = listO;
            m_scene->m_items = list;

            m_scene->removeItem(e);
            qDebug() << data.toString() << ui->tabWidget_3->tabText(index);
            delete e;
        }
    }
    ui->tabWidget_3->removeTab(index);
    if(!winConditionsComboboxList.isEmpty())
    {
        objectComboBox->clear();
        foreach (auto o, m_scene->m_objects){
            objectComboBox->addItem(o->data(0).toString());
        }
    }
}

AreaScene* MainWindow::getm_scene()
{
    return m_scene;
}

void MainWindow::on_pushButton_6_clicked()
{
    conditionLayout = new QHBoxLayout(ui->tab_8);
    conditionLayout->setObjectName(QString("Condition %1").arg(nWidgetWinCondition));
    ui->verticalLayout_3->addLayout(conditionLayout);

    ifComboBox = new QComboBox(ui->tab_8);
    ifComboBox->setObjectName(QString("Condition %1").arg(nWidgetWinCondition));
    ifComboBox->addItem("if");
    ifComboBox->addItem("else");

    objectComboBox = new QComboBox(ui->tab_8);
    objectComboBox->setObjectName(QString("Condition %1").arg(nWidgetWinCondition));
    foreach (auto o, m_scene->m_objects){
        objectComboBox->addItem(o->data(0).toString());
    }

    parametersComboBox = new QComboBox(ui->tab_8);
    parametersComboBox->setObjectName(QString("Condition %1").arg(nWidgetWinCondition));
    parametersComboBox->addItem("PV");
    parametersComboBox->addItem("Attack Point");
    parametersComboBox->addItem("Step Size");

    comparaisonComboBox = new QComboBox(ui->tab_8);
    comparaisonComboBox->setObjectName(QString("Condition %1").arg(nWidgetWinCondition));
    comparaisonComboBox->addItem("==");
    comparaisonComboBox->addItem(">");
    comparaisonComboBox->addItem(">");
    comparaisonComboBox->addItem(">=");
    comparaisonComboBox->addItem("<=");
    comparaisonComboBox->addItem("!=");

    targetSpinBox = new QSpinBox(ui->tab_8);
    targetSpinBox->setObjectName(QString("Condition %1").arg(nWidgetWinCondition));
    targetSpinBox->setValue(0);
    conditionLayout->addWidget(ifComboBox);
    conditionLayout->addWidget(objectComboBox);
    conditionLayout->addWidget(parametersComboBox);
    conditionLayout->addWidget(comparaisonComboBox);
    conditionLayout->addWidget(targetSpinBox);

    winConditionsComboboxList.append(ifComboBox);
    winConditionsComboboxList.append(objectComboBox);
    winConditionsComboboxList.append(parametersComboBox);
    winConditionsComboboxList.append(comparaisonComboBox);
    winConditionsSpinboxList.append(targetSpinBox);

    ui->comboBox_2->addItem(QString("Condition %1").arg(nWidgetWinCondition));
    nWidgetWinCondition++;
}

void MainWindow::on_pushButton_7_clicked()
{
    conditionLayout = new QHBoxLayout(ui->tab_9);
    conditionLayout->setObjectName(QString("Condition %1").arg(nWidgetDefeatCondition));
    ui->verticalLayout_4->addLayout(conditionLayout);

    ifComboBox = new QComboBox(ui->tab_9);
    ifComboBox->setObjectName(QString("Condition %1").arg(nWidgetDefeatCondition));
    ifComboBox->addItem("if");
    ifComboBox->addItem("else");

    objectComboBox = new QComboBox(ui->tab_9);
    objectComboBox->setObjectName(QString("Condition %1").arg(nWidgetDefeatCondition));
    foreach (auto o, m_scene->m_objects){
        objectComboBox->addItem(o->data(0).toString());
    }

    parametersComboBox = new QComboBox(ui->tab_9);
    parametersComboBox->setObjectName(QString("Condition %1").arg(nWidgetDefeatCondition));
    parametersComboBox->addItem("PV");
    parametersComboBox->addItem("Attack Point");
    parametersComboBox->addItem("Step Size");

    comparaisonComboBox = new QComboBox(ui->tab_9);
    comparaisonComboBox->setObjectName(QString("Condition %1").arg(nWidgetDefeatCondition));
    comparaisonComboBox->addItem("==");
    comparaisonComboBox->addItem(">");
    comparaisonComboBox->addItem(">");
    comparaisonComboBox->addItem(">=");
    comparaisonComboBox->addItem("<=");
    comparaisonComboBox->addItem("!=");

    targetSpinBox = new QSpinBox(ui->tab_9);
    targetSpinBox->setObjectName(QString("Condition %1").arg(nWidgetDefeatCondition));
    targetSpinBox->setValue(0);
    conditionLayout->addWidget(ifComboBox);
    conditionLayout->addWidget(objectComboBox);
    conditionLayout->addWidget(parametersComboBox);
    conditionLayout->addWidget(comparaisonComboBox);
    conditionLayout->addWidget(targetSpinBox);

    defeatConditionsComboboxList.append(ifComboBox);
    defeatConditionsComboboxList.append(objectComboBox);
    defeatConditionsComboboxList.append(parametersComboBox);
    defeatConditionsComboboxList.append(comparaisonComboBox);
    defeatConditionsSpinboxList.append(targetSpinBox);

    ui->comboBox_3->addItem(QString("Condition %1").arg(nWidgetDefeatCondition));
    nWidgetDefeatCondition++;
}


void MainWindow::on_pushButton_8_clicked()
{
    QString conditionName = ui->comboBox_2->currentText();
    QList<QComboBox*> tCombo;
    QList<QSpinBox*> tSpin;
    foreach (auto c, winConditionsComboboxList) {
        if(c->objectName() != conditionName)
        {
            tCombo.append(c);
        }
    }
    foreach (auto c, winConditionsSpinboxList) {
        if(c->objectName() != conditionName)
        {
            tSpin.append(c);
        }
    }
    winConditionsComboboxList = tCombo;
    winConditionsSpinboxList = tSpin;

    QList<QVBoxLayout*> layoutCondition = ui->tab_8->findChildren<QVBoxLayout*>(conditionName);
    foreach (auto l, layoutCondition) {
        delete l;
    }
    QList<QWidget*> widgetCondition = ui->tab_8->findChildren<QWidget*>(conditionName);
    foreach (auto w, widgetCondition) {
        delete w;
    }
    ui->comboBox_2->removeItem(ui->comboBox_2->currentIndex());
}


void MainWindow::on_pushButton_9_clicked()
{
    QString conditionName = ui->comboBox_3->currentText();
    QList<QComboBox*> tCombo;
    QList<QSpinBox*> tSpin;
    foreach (auto c, defeatConditionsComboboxList) {
        if(c->objectName() != conditionName)
        {
            tCombo.append(c);
        }
    }
    foreach (auto c, defeatConditionsSpinboxList) {
        if(c->objectName() != conditionName)
        {
            tSpin.append(c);
        }
    }
    defeatConditionsComboboxList = tCombo;
    defeatConditionsSpinboxList = tSpin;

    QList<QVBoxLayout*> layoutCondition = ui->tab_9->findChildren<QVBoxLayout*>(conditionName);
    foreach (auto l, layoutCondition) {
        delete l;
    }
    QList<QWidget*> widgetCondition = ui->tab_9->findChildren<QWidget*>(conditionName);
    foreach (auto w, widgetCondition) {
        qDebug() << w->objectName();
        delete w;
    }
    ui->comboBox_3->removeItem(ui->comboBox_3->currentIndex());
}

