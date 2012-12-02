#ifndef CHECKBOXEDITDELEGATE_H
#define CHECKBOXEDITDELEGATE_H

#include <QObject>
#include <QItemDelegate>

class checkBoxEditDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit checkBoxEditDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
    const QModelIndex &index) const;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
//    static QRect CheckBoxRect(const QStyleOptionViewItem &view_item_style_options);

    bool editorEvent(QEvent *event,QAbstractItemModel *model,const QStyleOptionViewItem &option,const QModelIndex &index);
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:

};

#endif // CHECKBOXEDITDELEGATE_H
