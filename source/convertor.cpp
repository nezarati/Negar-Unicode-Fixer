#include "convertor.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QDebug>

convertor::convertor(QObject *parent) :
    QObject(parent)
{
//    this->
}
void convertor::ModelToXML(QString url, QStandardItemModel *model){
    QFile output(url);
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
        stream.writeStartElement("alphabets");
        stream.writeAttribute("alphabet", "all");
    //! [write element]

        for(int row=0;row<model->rowCount();row++)
        {
            stream.writeStartElement("alphabet");
            stream.writeAttribute("name", model->data(model->index(row,0)).toString());
            stream.writeTextElement("normal",/* QString("0x").append*/(model->data(model->index(row,1)).toString()));
            stream.writeTextElement("medial", /*QString("0x").append*/(model->data(model->index(row,2)).toString()));
            stream.writeTextElement("initial", /*QString("0x").append*/(model->data(model->index(row,3)).toString()));
            stream.writeTextElement("final", /*QString("0x").append*/(model->data(model->index(row,4)).toString()));
            stream.writeTextElement("isolated",/*QString("0x").append*/(model->data(model->index(row,5)).toString()));
            stream.writeTextElement("joined-after",/*QString("0x").append*/(model->data(model->index(row,6)).toString()));
            stream.writeTextElement("joined-before",/*QString("0x").append*/(model->data(model->index(row,7)).toString()));
            stream.writeEndElement(); //
        //! [write element]
        }
    //! [write element]
        stream.writeEndElement();
        stream.writeEndElement();
    //! [finish stream]
        stream.writeEndDocument();
    //! [finish stream]
    //! [write output]
        output.close();
}
void convertor::XMLToModel(QString url, QStandardItemModel *model){
    QFile xml(url);

    if (!xml.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        QMessageBox::critical(main,"Cannot read XML File.", QMessageBox::Ok);
        qDebug()<<"Cannot read XML File.";
        return;
    }
    model->clear();
    model->setColumnCount(8);
    model->insertRow(0);
    QXmlStreamReader stream(&xml);
    while(!stream.atEnd())
    {
        if(!stream.attributes().value("name").isEmpty())
            model->setData(model->index(model->rowCount()-1,0),stream.attributes().value("name").toString());
         if(stream.name()=="normal")
            model->setData(model->index(model->rowCount()-1,1),stream.readElementText());
        else if(stream.name()=="medial")
            model->setData(model->index(model->rowCount()-1,2),stream.readElementText());
        else if(stream.name()=="initial")
            model->setData(model->index(model->rowCount()-1,3),stream.readElementText());
        else if(stream.name()=="final")
            model->setData(model->index(model->rowCount()-1,4),stream.readElementText());
        else if(stream.name()=="isolated")
        {
            model->setData(model->index(model->rowCount()-1,5),stream.readElementText());

         }else if(stream.name()=="joined-after"){
             model->setData(model->index(model->rowCount()-1,6),stream.readElementText());
         }else if(stream.name()=="joined-before"){
             model->setData(model->index(model->rowCount()-1,7),stream.readElementText());
             model->insertRow(model->rowCount());
         }
        stream.readNext();
    }
    model->removeRow(model->rowCount()-1);
}
