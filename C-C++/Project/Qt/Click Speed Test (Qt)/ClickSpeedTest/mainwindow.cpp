#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Click Speed Test");

    m_central = new QWidget(this);
    m_layout = new QVBoxLayout(this);

    m_view = new QGraphicsView(this);
    m_scene = new MaScene(this);

    m_view->setScene(m_scene);

    m_view->setAlignment(Qt::AlignTop);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_layout->addWidget(m_view);
    m_central->setLayout(m_layout);

    setCentralWidget(m_central);
}

MainWindow::~MainWindow()
{
    delete ui;
}
