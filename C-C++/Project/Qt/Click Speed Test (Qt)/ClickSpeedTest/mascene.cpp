#include "mascene.h"
#include <QThread>

MaScene::MaScene(QObject *parent)
    : QGraphicsScene{parent}
{
    setBackgroundBrush(Qt::gray);


    m_buttonText = "Start Here";
    m_buttonClick = new QPushButton(m_buttonText);
    m_buttonClick->setGeometry(0, 50, 500,300);

    if(m_isClicked == false && m_buttonText == "Start Here")
    {
       connect(m_buttonClick, SIGNAL(clicked(bool)), this, SLOT(firstClick()));
    }
    else if(m_isClicked == true && m_buttonText == "Click Here")
    {
        connect(m_buttonClick, SIGNAL(clicked(bool)), this, SLOT(newClick()));
        m_Qtimer.setInterval(3000);
        m_Qtimer.start();
        connect(&m_Qtimer, SIGNAL(timeout()), this, SLOT(set_false()));
    }

    m_timer = new TextBox(m_nTimer, "s");
    m_timer->move(220,25);

    m_cps = new TextBox(m_nCps, " cps");
    m_cps->move(220,350);

    addWidget(m_timer);
    addWidget(m_buttonClick);
    addWidget(m_cps);
}

void MaScene::changeButtonTextToWait()
{
    m_buttonText = "Wait...";
    m_buttonClick->setText(m_buttonText);
}

void MaScene::changeButtonTextToGo()
{
    m_buttonText = "Click Here";
    m_buttonClick->setText(m_buttonText);

}

void MaScene::firstClick()
{
    if(m_buttonText == "Start Here")
    {
        m_isClicked = true;
        changeButtonTextToWait();
        m_Qtimer.setInterval(3000);
        m_Qtimer.start();
        connect(&m_Qtimer, SIGNAL(timeout()), this, SLOT(changeButtonTextToGo()));
        qDebug() << "go " << Qt::endl;
    }
    else if(m_buttonText == "Click Here" && m_isClicked == true)
    {
        newClick();
    }

}

void MaScene::newClick()
{
    m_nCps++;
    m_cps->setN(m_nCps);
}

void MaScene::set_false()
{
    qDebug() << "set faqlse " << Qt::endl;
    m_isClicked = false;
    changeButtonTextToWait();
    m_nCps = 0;
    m_cps->setN(m_nCps);
}
