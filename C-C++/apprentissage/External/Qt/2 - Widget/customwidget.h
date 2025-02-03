#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTimer>

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(int time, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* e); // évenement de clique de souris
    void mouseReleaseEvent(QMouseEvent* e); // événement de clique de souris relaché

private slots:
    void changeText();

private:
    bool m_isClicked = false;
    bool m_timerEnd = false;

    QTimer m_timer; // un QTimer est un chronomètre

signals:
};

#endif // CUSTOMWIDGET_H
