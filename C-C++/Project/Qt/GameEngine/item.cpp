#include "item.h"
#include <QPen>

Item::Item(QColor color, int Hsize, int Lsize, QString event) : m_color(color), m_Hsize(Hsize), m_Lsize(Lsize), m_event(event)
{
    setRect(0,0, Hsize, Lsize);
    setPen(QPen(Qt::black));
    setBrush(QBrush(color));
}

void Item::setm_color(QColor color)
{
    m_color = color;
    setBrush(QBrush(m_color));
}

QColor Item::getm_color()
{
    return m_color;
}

void Item::setm_Hsize(int size)
{
    m_Hsize = size;
    setRect(pos().x(), pos().y(), m_Hsize, m_Lsize);
}

int Item::getm_Hsize()
{
    return m_Hsize;
}

void Item::setm_Lsize(int size)
{
    m_Lsize = size;
    setRect(pos().x(), pos().y(), m_Hsize, m_Lsize);
}

int Item::getm_Lsize()
{
    return m_Lsize;
}

void Item::setm_event(QString e)
{
    m_event = e;
}

QString Item::getm_event()
{
    return m_event;
}

void Item::activateEvent(Entity *e)
{
    if(m_event == "Heal PV")
    {
        qDebug() << e << " a " << e->getm_PV() << "PV";
        e->setm_PV(e->getm_PV()+n_heal);
        qDebug() << e << " a " << e->getm_PV() << "PV";
    }
    else if(m_event == "Buff Attack")
    {
        qDebug() << e << " a " << e->getm_attackPoint() << "AP";
        e->setm_attackPoint(e->getm_attackPoint()+n_buffAttack);
        qDebug() << e << " a " << e->getm_attackPoint() << "AP";
    }
    else if(m_event == "Buff Step Size")
    {
        qDebug() << e << " a " << e->getm_sizeStep() << "SS";
        qDebug() << n_buffStepSize;
        e->setm_sizeStep(e->getm_sizeStep()/50+n_buffStepSize);
        qDebug() << e << " a " << e->getm_sizeStep() << "SS";
    }
    else if(m_event == "Inflicts Damage")
    {
        qDebug() << e << " a " << e->getm_PV() << "PV";
        e->setm_PV(e->getm_PV()-n_inflictsDamage);
        qDebug() << e << " a " << e->getm_PV() << "PV";
    }
    else if(m_event == "Debuff Attack")
    {
        qDebug() << e << " a " << e->getm_attackPoint() << "AP";
        e->setm_attackPoint(e->getm_attackPoint()-n_debuffAttack);
        qDebug() << e << " a " << e->getm_attackPoint() << "AP";
    }
    else if(m_event == "Debuff Step Size")
    {
        if(e->getm_sizeStep() > 50 && e->getm_sizeStep()-n_debuffStepSize >= 50)
        {
            qDebug() << e << " a " << e->getm_sizeStep() << "SS";
            e->setm_sizeStep(e->getm_sizeStep()/50-n_debuffStepSize);
            qDebug() << e << " a " << e->getm_sizeStep() << "SS";
        }
    }
}

void Item::setn_Event(int n)
{
    if(m_event == "Heal PV")
    {
        n_heal = n;
    }
    else if(m_event == "Buff Attack")
    {
        n_buffAttack = n;
    }
    else if(m_event == "Buff Step Size")
    {
        n_buffStepSize = n;
    }
    else if(m_event == "Inflicts Damage")
    {
        n_inflictsDamage = n;
    }
    else if(m_event == "Debuff Attack")
    {
        n_debuffAttack = n;
    }
    else if(m_event == "Debuff Step Size")
    {
        n_debuffStepSize = n;
    }
}

int Item::getn_Event()
{
    int n = 0;
    if(m_event == "Heal PV")
    {
        n = n_heal;
    }
    else if(m_event == "Buff Attack")
    {
        n = n_buffAttack;
    }
    else if(m_event == "Buff Step Size")
    {
        n = n_buffStepSize;
    }
    else if(m_event == "Inflicts Damage")
    {
        n = n_inflictsDamage;
    }
    else if(m_event == "Debuff Attack")
    {
        n = n_debuffAttack;
    }
    else if(m_event == "Debuff Step Size")
    {
        n = n_debuffStepSize;
    }
    return n;
}


