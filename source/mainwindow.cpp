#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTextCodec"
#include "qDebug"
#include "QClipboard"
#include "QString"
#include "string"
#include "unicodepresavedialog.h"
#include <QXmlStreamWriter>
#include <QFile>
#include <QMessageBox>
#include <convertor.h>
#include <dialogunicodexmlfileeditor.h>
#include <checkboxeditdelegate.h>
#include <qcheckbox.h>
#include "QFontDatabase"
#include "qtextedit.h"
#include "dialogabout.h"
#include "QDir"
#include "QFile"
#include "QFileDialog"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model=new QStandardItemModel(1,6);
//    ui->tableViewXmlData->setModel(model);
    model->insertColumn(model->columnCount());
    checkBoxEditDelegate *combo=new checkBoxEditDelegate();
//    ui->tableViewXmlData->setItemDelegateForColumn(6,combo);
//    ui->tableViewXmlData->setItemDelegateForColumn(7,combo);
    readSettingsFile();
    ui->comboBoxFont->insertItems(0,QFontDatabase().families());
    this->setCentralWidget(ui->gridLayoutWidget);
    ui->comboBoxFontSize->insertItems(0,QStringList()<<"8"<<"9"<<"10"<<"11"<<"12"<<"14"<<"16"<<"18"<<"20"<<"22"<<"24"<<"26"<<"28"<<"36"<<"48"<<"72");
    ui->comboBoxFont->setCurrentIndex(ui->comboBoxFont->findText("B Koodak"));
    ui->comboBoxFontSize->setCurrentIndex(ui->comboBoxFontSize->findText("20"));
    ui->textEdit->setFont(QFont("B Koodak",18));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(convertToUnicodeText().toAscii());
}
bool MainWindow::array_key_exists(const QChar array[],QChar ch)
{
    for(uint i=0;i<8;i++)
        if(array[i]==ch) return 1;
    return 0;
}

void MainWindow::on_pushButton_2_clicked()
{
}

void MainWindow::on_pushButton_3_clicked()
{

}

void MainWindow::on_actionUnicode_File_triggered()
{
    DialogUnicodeXmlFileEditor w;
    w.exec();
    readSettingsFile();
}
void MainWindow::readSettingsFile(){
    QFile xml("settings.xml");
    if (!xml.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Cannot read XML File.";
        return;
    }
    QString str;
    QXmlStreamReader stream(&xml);
    while(!stream.atEnd())
    {
        if(!stream.attributes().value("address").isEmpty()){
            str=stream.attributes().value("address").toString();
            qDebug()<<str;
        }
        if(stream.name()=="active-state"){
            if(stream.readElementText()=="1")
                convertor::XMLToModel(str,model);
        }
        stream.readNext();
    }
}



void MainWindow::on_comboBoxFont_currentIndexChanged(const QString &arg1)
{
    ui->textEdit->setFont(QFont(ui->comboBoxFont->currentText(),ui->comboBoxFontSize->currentText().toInt()));
}

void MainWindow::on_comboBoxFontSize_currentIndexChanged(const QString &arg1)
{
    ui->textEdit->setFont(QFont(ui->comboBoxFont->currentText(),ui->comboBoxFontSize->currentText().toInt()));
}

void MainWindow::on_actionAbout_triggered()
{
    DialogAbout w;
    w.exec();
}

void MainWindow::on_actionUnicode_triggered()
{
//    UnicodePresaveDialog dialg;
//    dialg.exec();
    QString fileDir = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::currentPath(),tr("Text File (*.txt);;All files (*.*)"));
    if(fileDir.isEmpty())
        return;
    QFile file(fileDir);
    file.open(QIODevice::WriteOnly/*| QIODevice::Text*/);
    QTextStream out(&file);
    QString ConvertedUnicode="";
    for (int i = 0; i < convertToUnicodeText().length(); ++i) {
        ConvertedUnicode.append("\\u").append(QString::number(convertToUnicodeText().at(i).unicode(),16));
    }
    out.setCodec("ISO-8859-1");
    qDebug()<<ConvertedUnicode;
    QStringList l=ConvertedUnicode.split("\\u");
//    qDebug()<<"list"<<l;
    QStringList lb;
    for (int i = 0; i < l.count(); ++i) {
        QString z="";
        for (int j = 0; j < 4-(l.at(i).toStdString().size()); ++j) {
            z.append("0");
        }
//        qDebug()<<"z"<<sizeof(l.at(i))<<z;
        lb.insert(i,QString("\\u"+z+l.at(i)));
    }
//    qDebug()<<lb;
    for (int i = 0; i < lb.count(); ++i) {
        out <<lb.at(i);
    }

    file.close();
}

void MainWindow::on_action_Open_triggered()
{

    QString fileDir = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(),tr("Text File (*.txt);;All files (*.*)"));
    if(!fileDir.isEmpty()){
        ui->textEdit->clear();
        QFile file(fileDir);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            while (!in.atEnd()) {
                ui->textEdit->append(in.readLine());
            }
        }
    }
}

void MainWindow::on_action_Exit_triggered()
{
    this->close();
}
QString MainWindow::convertToUnicodeText(){
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QString text;
    QString ConvertedText="";
    QString ConvertedUnicode="";
    text=" ";
    text.append(ui->textEdit->toPlainText().toUtf8());
    text.append("  ");
    QChar letters[model->rowCount()][7];
    bool ok;
    for (int i = 0; i < model->rowCount(); ++i) {
        for (int j = 1; j < model->columnCount(); ++j) {
            letters[i][j-1]=model->data(model->index(i,j)).toString().toInt(&ok,16);

        }
    }
    QChar sp_letters[model->rowCount()];
    int c=0;
    for (int i = 0; i < model->rowCount(); ++i) {
        if(letters[i][5]==0){
            sp_letters[c]=letters[i][0];
            c++;
        }
    }
//    const QChar sp_letters[]={0x0627/*alef*/,0x622/*alef*/,0x062F/*dal*/,0x0630/*zal*/,0x0631/*re*/,0x0632/*ze*/,0x0698/*zhe*/,0x0648/*vav*/};
    for(int i=1;i<text.length()-1;i++)
    {
        for(int j=0;j<model->rowCount();j++)
        {
            if(letters[j][0]==text.at(i))
            {
                if(((text.at(i+1)!=' '&&text.at(i-1)==' ')|| (text.at(i+1)!=' '&&array_key_exists(sp_letters,text.at(i-1))))&&text.at(i+1)!=10)
                {
                    qDebug()<<"1"<<letters[j][1];
                    ConvertedText.append(letters[j][1]);

                    ConvertedUnicode.append("\\u");
                    if(letters[j][1]==0x20)
                        ConvertedUnicode.append("00");
                    if(letters[j][1]==0xa)
                        ConvertedUnicode.append("000");
                    ConvertedUnicode.append(QString::number(letters[j][1].unicode(),16));
                }
                if((text.at(i+1)!=' '&&text.at(i-1)!=' '&&!array_key_exists(sp_letters,text.at(i-1)))&&text.at(i+1)!=10)
                {
                    qDebug()<<"2"<<letters[j][2];
                    ConvertedText.append(letters[j][2]);

                    ConvertedUnicode.append("\\u");
                    if(letters[j][2]==0x20)//additional charecter 00 '' \n\r=10
                        ConvertedUnicode.append("00");
                    if(letters[j][2]==0xa)
                        ConvertedUnicode.append("000");
                    ConvertedUnicode.append(QString::number(letters[j][2].unicode(),16));
                }
                if((text.at(i+1)==' '&&text.at(i-1)!=' '&& (i<text.length()-2)&&!(array_key_exists(sp_letters,text.at(i-1))))||(!(array_key_exists(sp_letters,text.at(i-1)))&&text.at(i+1)==10))
                {
                    qDebug()<<"3"<<letters[j][3];
                    ConvertedText.append(letters[j][3]);

                    ConvertedUnicode.append("\\u");
                    ConvertedUnicode.append(QString::number(letters[j][3].unicode(),16));
                }
                if(((text.at(i+1)==' '&&text.at(i-1)==' ')||( text.at(i+1)==' '&&array_key_exists(sp_letters,text.at(i-1))))||((array_key_exists(sp_letters,text.at(i-1)))&&text.at(i+1)==10))
                {
                    qDebug()<<"4"<<letters[j][4];
                    ConvertedText.append(letters[j][4]);

                    ConvertedUnicode.append("\\u");
                    ConvertedUnicode.append(QString::number(letters[j][4].unicode(),16));

                }
            }
        }
    }
    if (ui->checkBoxRevLetter->isChecked()) {
        QString text="";
        QStringList lineText= ConvertedText.split('\\n');
        for (int i = 0; i < lineText.count(); ++i) {
            QStringList lineWords=lineText.at(i).split(' ');
            for (int j = 0; j < lineWords.count(); ++j) {
                for (int k = lineWords.at(j).length()-1; k >=0 ; --k) {

                    text.append(lineWords.at(j).at(k));
                }
                text.append(' ');
            }
            text.remove(text.count()-1,1);
            text.append('\\n');
            qDebug()<<text;
        }
        text.remove(text.count()-1,1);
        ConvertedText=text;
    }
    if (ui->checkBoxRevWord->isChecked()) {
        QString text="";
        QStringList lineText= ConvertedText.split('\\n');
        for (int i = 0; i < lineText.count(); ++i) {
            QStringList lineWords=lineText.at(i).split(' ');
            for (int j = lineWords.count()-1; j >=0 ; --j) {
                text.append(lineWords.at(j));
                text.append(' ');
            }
            text.remove(text.count()-1,1);
            text.append('\\n');
        }
        text.remove(text.count()-1,1);
        ConvertedText=text;
    }

    qDebug()<<ConvertedUnicode;
    return ConvertedText;
}
