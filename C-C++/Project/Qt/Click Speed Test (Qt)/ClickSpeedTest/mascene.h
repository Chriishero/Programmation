#ifndef MASCENE_H
#define MASCENE_H

#include <QGraphicsScene>
#include <QObject>
#include "textbox.h"
#include <QPushButton>
#include <QTimer>

class MaScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MaScene(QObject *parent = nullptr);

private slots:
    void changeButtonTextToWait();
    void changeButtonTextToGo();
    void firstClick();
    void newClick();
    void set_false();

private:
    QPushButton* m_buttonClick;
    TextBox* m_timer;
    TextBox* m_cps;

    bool m_isClicked = false;
    bool m_timerEnd = false;

    int m_nCps = 0;
    int m_nTimer = 10;

    QTimer m_Qtimer;

    QString m_buttonText;
};

#endif // MASCENE_H
