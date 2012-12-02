#include "dialogabout.h"
#include "ui_dialogabout.h"
#include "QtGui"

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

DialogAbout::~DialogAbout()
{
    delete ui;
}
