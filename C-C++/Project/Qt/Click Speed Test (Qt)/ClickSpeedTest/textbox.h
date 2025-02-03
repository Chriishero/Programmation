#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QObject>
#include <QWidget>

class TextBox : public QWidget
{
    Q_OBJECT
public:
    explicit TextBox(int n, QString text, QWidget *parent = nullptr);

    void setN(int n);

protected:
    void paintEvent(QPaintEvent* e);

private:
    QString m_text;

    int m_n = 0;
};

#endif // TEXTBOX_H
