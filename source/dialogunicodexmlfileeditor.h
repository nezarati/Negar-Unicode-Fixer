#ifndef DIALOGUNICODEXMLFILEEDITOR_H
#define DIALOGUNICODEXMLFILEEDITOR_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
    class DialogUnicodeXmlFileEditor;
}

class DialogUnicodeXmlFileEditor : public QDialog
{
    Q_OBJECT

public:
    QStandardItemModel *model,*modelAddress;
    explicit DialogUnicodeXmlFileEditor(QWidget *parent = 0);
    ~DialogUnicodeXmlFileEditor();

private:
    Ui::DialogUnicodeXmlFileEditor *ui;

public slots:
    void ShowContextMenu(const QPoint& pos);
    void selectedAdressIschanged();
private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonActivator_clicked();
    void readSettingsFile();
    void on_pushButtonRemove_clicked();
    void on_pushButtonSave_2_clicked();
    void on_pushButtonAddRow_clicked();
    void on_pushButtonRemoveRow_clicked();
    void on_pushButtonActivator_2_clicked();
    void readSettingsFileInit();
};

#endif // DIALOGUNICODEXMLFILEEDITOR_H
