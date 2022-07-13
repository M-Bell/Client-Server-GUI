#ifndef CHANGEAMOUNTWINDOW_H
#define CHANGEAMOUNTWINDOW_H

#include <QDialog>

namespace Ui {
class ChangeAmountWindow;
}

class ChangeAmountWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeAmountWindow(QWidget *parent = nullptr);
    ~ChangeAmountWindow();

private:
    Ui::ChangeAmountWindow *ui;
};

#endif // CHANGEAMOUNTWINDOW_H
