#ifndef TRANSLATIONDIALOG_H
#define TRANSLATIONDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QPointer>

namespace Ui {
class translationDialog;
}

class translationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit translationDialog(QWidget *parent = nullptr);
    ~translationDialog();

    Ui::translationDialog *ui;

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    QPoint cur_pos;
    QPoint new_pos;

};

#endif // TRANSLATIONDIALOG_H
