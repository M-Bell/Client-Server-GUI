#include "changeamountwindow.h"
#include "ui_changeamountwindow.h"

ChangeAmountWindow::ChangeAmountWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeAmountWindow)
{
    ui->setupUi(this);
}

ChangeAmountWindow::~ChangeAmountWindow()
{
    delete ui;
}
