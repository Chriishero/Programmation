#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QObject>
#include <QPushButton>

class CustomButton : public QPushButton
{
    Q_OBJECT // défini la macro 'Q_OBJECT' qui s'occupera de généré du code pour que ces mécanismes (QPushButton)  fonctionnent automatiquement
    Q_PROPERTY(QString name READ getName WRITE setName) // macro qui permet d'implémenter des getter/setter
    // peut aussi notifier quand la propriété à changé avec : NOTIFY getNameChanged FINAL

public slots: // le slot doit être public sinon on ne peut pas l'appeler depuis une autre classe
    void MessageBox();

public:
    CustomButton(QString text, QWidget *parent = nullptr);
    ~CustomButton(); // créer un destructeur
    // ALT GR + 2

    QString getName() { return m_text; } // renvoie 'm_text', le text du bouton
    void setName(QString text) { m_text = text; }

private:
    QString m_text;
};

#endif // CUSTOMBUTTON_H
