#include "dialogunicodexmlfileeditor.h"
#include "ui_dialogunicodexmlfileeditor.h"
#include "QMenu"
#include "QDebug"
#include"convertor.h"
#include "checkboxeditdelegate.h"
#include "QFile"
#include "QXmlStreamWriter"
#include "QFileDialog"
#include <QMainWindow>
#include "QItemSelectionModel"
DialogUnicodeXmlFileEditor::DialogUnicodeXmlFileEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUnicodeXmlFileEditor)
{
    ui->setupUi(this);
    ui->listViewAddress->setContextMenuPolicy(Qt::CustomContextMenu);

    model=new QStandardItemModel(1,6);
    modelAddress=new QStandardItemModel(1,3);
    ui->listViewAddress->setModel(modelAddress);

    ui->tableViewXmlData->setModel(model);
    checkBoxEditDelegate *comboBox=new checkBoxEditDelegate();
    ui->tableViewXmlData->setItemDelegateForColumn(6,comboBox);
    ui->tableViewXmlData->setItemDelegateForColumn(7,comboBox);
    readSettingsFile();
    connect(ui->listViewAddress,SIGNAL(pressed(QModelIndex)),this,SLOT(selectedAdressIschanged()));
    connect(ui->listViewAddress, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(ShowContextMenu(const QPoint&)));
    readSettingsFileInit();
    this->setLayout(ui->gridLayoutWidget->layout());

}

DialogUnicodeXmlFileEditor::~DialogUnicodeXmlFileEditor()
{
    delete ui;
}
void DialogUnicodeXmlFileEditor::ShowContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->listViewAddress->mapToGlobal(pos);

    QMenu myMenu(this);
    myMenu.addAction("Add XML File");
    myMenu.addAction("Remove selected XML File");
    myMenu.addAction("Save Adress List");
    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        if(!selectedItem->text().compare("Add XML File"))
        {
            on_pushButtonAdd_clicked();
        }
        else if(!selectedItem->text().compare("Remove selected XML File"))
        {
            on_pushButtonRemove_clicked();
        }
        else if(!selectedItem->text().compare("Save Adress List"))
        {
            on_pushButtonSave_2_clicked();
        }

    }
}

void DialogUnicodeXmlFileEditor::on_pushButtonAdd_clicked()
{
    QString fileDir = QFileDialog::getOpenFileName(this, tr("Add XML File"), QDir::currentPath(),tr("XML File (*.xml);;All files (*.*)"));
    if(!fileDir.isEmpty()){
        QStringList strList=fileDir.split('/');
        modelAddress->insertRow(modelAddress->rowCount());
        modelAddress->setData(modelAddress->index(modelAddress->rowCount()-1,0),strList.last());
        modelAddress->setData(modelAddress->index(modelAddress->rowCount()-1,1),fileDir.remove(strList.last()));
        modelAddress->setData(modelAddress->index(modelAddress->rowCount()-1,2),0);
    }
}

void DialogUnicodeXmlFileEditor::on_pushButtonSave_clicked()
{
    convertor::ModelToXML(modelAddress->data(modelAddress->index(ui->listViewAddress->currentIndex().row(),1)).toString()+modelAddress->data(modelAddress->index(ui->listViewAddress->currentIndex().row(),0)).toString(),model);
}

void DialogUnicodeXmlFileEditor::on_pushButtonActivator_clicked()
{


}
void DialogUnicodeXmlFileEditor::selectedAdressIschanged(){
    convertor::XMLToModel(modelAddress->data(modelAddress->index(ui->listViewAddress->currentIndex().row(),1)).toString()+modelAddress->data(modelAddress->index(ui->listViewAddress->currentIndex().row(),0)).toString(),model);

    qDebug()<<modelAddress->data(modelAddress->index(ui->listViewAddress->currentIndex().row(),1)).toString()+modelAddress->data(modelAddress->index(ui->listViewAddress->currentIndex().row(),0)).toString();
}
void DialogUnicodeXmlFileEditor::readSettingsFile(){
    QFile xml("settings.xml");
    if (!xml.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Cannot read XML File.";
        return;
    }
    modelAddress->clear();
    modelAddress->setColumnCount(3);
    modelAddress->insertRow(0);
    QXmlStreamReader stream(&xml);
    while(!stream.atEnd())
    {
        if(!stream.attributes().value("address").isEmpty()){
            QString str=stream.attributes().value("address").toString();
            QStringList strList=str.split('/');
            modelAddress->setData(modelAddress->index(modelAddress->rowCount()-1,0),strList.last());
            modelAddress->setData(modelAddress->index(modelAddress->rowCount()-1,1),str.remove(strList.last()));
        }
        if(stream.name()=="active-state"){
            modelAddress->setData(modelAddress->index(modelAddress->rowCount()-1,2),stream.readElementText());
            modelAddress->insertRow(modelAddress->rowCount());
        }
        stream.readNext();

    }
    modelAddress->removeRow(modelAddress->rowCount()-1);
}

void DialogUnicodeXmlFileEditor::on_pushButtonRemove_clicked()
{
    if (ui->listViewAddress->currentIndex().isValid()) {
        modelAddress->removeRow(ui->listViewAddress->currentIndex().row());

    }
}

void DialogUnicodeXmlFileEditor::on_pushButtonSave_2_clicked()
{
    QFile output("settings.xml");
        output.open(QIODevice::WriteOnly);
    //! [write output]
    //! [start stream]

        QXmlStreamWriter stream(&output);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();
    //! [start stream]
        stream.writeDTD("<!DOCTYPE Negar>");
        stream.writeStartElement("Negar");
        stream.writeAttribute("version", "1.0");
        stream.writeStartElement("Settings");
        stream.writeAttribute("files", "all");
    //! [write element]

        for(int row=0;row<modelAddress->rowCount();row++)
        {
            stream.writeStartElement("XMLUnicodeFiles");
            stream.writeAttribute("address", modelAddress->data(modelAddress->index(row,1)).toString()+modelAddress->data(modelAddress->index(row,0)).toString());
            stream.writeTextElement("active-state",modelAddress->data(modelAddress->index(row,2)).toString());
        //! [write element]
         stream.writeEndElement();
        }
    //! [write element]

        stream.writeEndElement();
    //! [finish stream]
        stream.writeEndDocument();
    //! [finish stream]
    //! [write output]
        output.close();

}

void DialogUnicodeXmlFileEditor::on_pushButtonAddRow_clicked()
{
    model->insertRow(model->rowCount());
    ui->tableViewXmlData->setCurrentIndex(model->index(model->rowCount(),0));
}

void DialogUnicodeXmlFileEditor::on_pushButtonRemoveRow_clicked()
{
    if(ui->tableViewXmlData->currentIndex().isValid())
        model->removeRow(ui->tableViewXmlData->currentIndex().row());
}

void DialogUnicodeXmlFileEditor::on_pushButtonActivator_2_clicked()
{
    for (int row = 0; row < modelAddress->rowCount(); ++row)
        if(ui->listViewAddress->currentIndex().row()==row)
            modelAddress->setData(modelAddress->index(row,2),1);
        else
            modelAddress->setData(modelAddress->index(row,2),0);
}
void DialogUnicodeXmlFileEditor::readSettingsFileInit(){
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
        }
        if(stream.name()=="active-state"){
            if(stream.readElementText()=="1"){
                convertor::XMLToModel(str,model);
            }
        }
        stream.readNext();
    }
}
