#ifndef UNICODEPRESAVEDIALOG_H
#define UNICODEPRESAVEDIALOG_H

#include <QDialog>

namespace Ui {
    class UnicodePresaveDialog;
}

class UnicodePresaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UnicodePresaveDialog(QWidget *parent = 0);
    ~UnicodePresaveDialog();

private:
    Ui::UnicodePresaveDialog *ui;

private slots:
    void on_pushButtonSave_clicked();
    void on_pushButton_clicked();
};

#endif // UNICODEPRESAVEDIALOG_H
