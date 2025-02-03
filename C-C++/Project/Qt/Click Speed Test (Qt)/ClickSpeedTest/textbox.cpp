#include "textbox.h"
#include <QPainter>

TextBox::TextBox(int n, QString text, QWidget *parent)
    : QWidget{parent}, m_n(n), m_text(text)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setGeometry(0,0, 75,25);
}

void TextBox::setN(int n)
{
    m_n = n;
    repaint();
}

void TextBox::paintEvent(QPaintEvent *e)
{
    QPainter p(this);

    p.setPen(Qt::white);

    p.drawRoundedRect(0,0 , this->width()-200, this->height()-150, 0,0);
    p.drawText(this->width() * 0.5f, this->height() * 0.5f+5, QString("%1" + m_text).arg(m_n));
}
