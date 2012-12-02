#include "checkboxeditdelegate.h"
#include "qcheckbox.h"
#include <QtGui/QApplication>
#include <QtGui/QMouseEvent>
#include <QtGui>

checkBoxEditDelegate::checkBoxEditDelegate(QObject *parent) :
    QItemDelegate(parent)
{

}
static QRect CheckBoxRect(const QStyleOptionViewItem &view_item_style_options) {
  QStyleOptionButton check_box_style_option;
  QRect combo_box_rect = QApplication::style()->subElementRect(
      QStyle::SE_CheckBoxIndicator,
      &check_box_style_option);
  QPoint combo_box_point(view_item_style_options.rect.x() +
                         view_item_style_options.rect.width() / 2 -
                         combo_box_rect.width() / 2,
                         view_item_style_options.rect.y() +
                         view_item_style_options.rect.height() / 2 -
                         combo_box_rect.height() / 2);
  return QRect(combo_box_point, combo_box_rect.size());
}

void checkBoxEditDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    bool checked = index.model()->data(index, Qt::DisplayRole).toBool();

      QStyleOptionButton combo_box_style_option;
//      combo_box_style_option.state |= QStyle::State_Enabled;
//      if (checked) {
//        combo_box_style_option.state |= QStyle::State_On;
//      } else {
//        combo_box_style_option.state |= QStyle::State_Off;
//      }
      combo_box_style_option.rect = CheckBoxRect(option);

      QApplication::style()->drawControl(QStyle::CE_ComboBoxLabel,
                                         &combo_box_style_option,
                                         painter);
      if(index.model()->data(index, Qt::DisplayRole).toString()=="0")
        painter->drawText(option.rect.x()+3,option.rect.y(),option.rect.width(),option.rect.height(),Qt::AlignVCenter,"Non-Joinor");
      else
          painter->drawText(option.rect.x()+3,option.rect.y(),option.rect.width(),option.rect.height(),Qt::AlignVCenter,"Joinor");
}
QWidget *checkBoxEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *comboBox=new QComboBox(parent);
    comboBox->insertItems(0,QStringList()<<"Non-Joinor"<<"Joinor");
    return comboBox;
}
void checkBoxEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    editor->setGeometry(option.rect);
}

void checkBoxEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    QComboBox *comboBox=static_cast<QComboBox*>(editor);
    comboBox->setCurrentIndex(index.model()->data(index, Qt::EditRole).toInt());
}
void checkBoxEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox=static_cast<QComboBox*>(editor);
    model->setData(index,comboBox->currentIndex() , Qt::EditRole);
}

bool checkBoxEditDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    if ((event->type() == QEvent::MouseButtonRelease) ||(event->type() == QEvent::MouseButtonPress) ||
      (event->type() == QEvent::MouseButtonDblClick)) {
    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
    if (mouse_event->button() != Qt::LeftButton ||
        !CheckBoxRect(option).contains(mouse_event->pos())) {
      return false;
    }
    if (event->type() == QEvent::MouseButtonDblClick) {qDebug()<<"asdas";
      return true;
    }
  } else if (event->type() == QEvent::KeyPress) {
    if (static_cast<QKeyEvent*>(event)->key() != Qt::Key_Space &&
        static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select) {
      return false;
    }
  } else {
    return false;
  }

  return model->setData(index, model->data(index).toString(), Qt::EditRole);
}
