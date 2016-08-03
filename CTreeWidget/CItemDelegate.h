#ifndef CITEMDELEGATE_H
#define CITEMDELEGATE_H


#include <QStyledItemDelegate>
#include <QTreeView>

class CItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CItemDelegate(QObject * parent=0);
    virtual ~CItemDelegate(){}

public:
    void    paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;

};

#endif // CITEMDELEGATE_H
