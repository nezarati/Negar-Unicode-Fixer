#include "unicodepresavedialog.h"
#include "ui_unicodepresavedialog.h"
#include "QSettings"
#include "qDebug"

UnicodePresaveDialog::UnicodePresaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnicodePresaveDialog)
{
    ui->setupUi(this);


}

UnicodePresaveDialog::~UnicodePresaveDialog()
{
    delete ui;
}

void UnicodePresaveDialog::on_pushButton_clicked()
{

}

void UnicodePresaveDialog::on_pushButtonSave_clicked()
{
    QSettings settings("settings.ini",QSettings::IniFormat);
    settings.beginGroup("unicodeFile");
    settings.setValue("startFileString", ui->textEditStartFileString->toPlainText());
    settings.setValue("endFileString", ui->textEditEndFileString->toPlainText());
    settings.setValue("splitterCharecter", ui->lineEditSplitterCharecter->text());
    settings.setValue("lineDataCount", ui->spinBoxLineDataCount->text());
    settings.endGroup();
}
