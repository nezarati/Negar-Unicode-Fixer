#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool array_key_exists(const QChar array[],QChar ch);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;

private slots:
    void on_actionUnicode_File_triggered();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void readSettingsFile();
    void on_comboBoxFont_currentIndexChanged(const QString &arg1);
    void on_comboBoxFontSize_currentIndexChanged(const QString &arg1);
    void on_actionAbout_triggered();
    void on_actionUnicode_triggered();
    void on_action_Open_triggered();
    void on_action_Exit_triggered();
    QString convertToUnicodeText();
};

#endif // MAINWINDOW_H
