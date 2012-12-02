#ifndef CONVERTOR_H
#define CONVERTOR_H

#include <QObject>
#include <QStandardItem>

class convertor : public QObject
{
    Q_OBJECT
public:
    explicit convertor(QObject *parent = 0);
    static void XMLToModel(QString url,QStandardItemModel *model);
    static void ModelToXML(QString url,QStandardItemModel *model);

signals:

public slots:


};

#endif // CONVERTOR_H
