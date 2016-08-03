
#include "../CItemDelegate.h"

#include <QPainter>
#include <QMouseEvent>
#include <QStyledItemDelegate>
#include <QToolTip>

CItemDelegate::CItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void CItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem  viewOption(option);
    if (viewOption.state & QStyle::State_HasFocus)
    {
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
    }

    QStyledItemDelegate::paint(painter, viewOption, index);
}
