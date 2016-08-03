
#include "../CTreeItem.h"


CTreeItem::CTreeItem(const QList<QVariant> &data, CTreeItem *parent)
{
    m_pParentItem = parent;
    m_lstItemData = data;
}

CTreeItem::~CTreeItem()
{
    qDeleteAll(m_lstChildItems);
}

void CTreeItem::appendChild(CTreeItem *child)
{
    m_lstChildItems.append(child);
}

CTreeItem *CTreeItem::child(int row)
{
    return m_lstChildItems.value(row);
}

int CTreeItem::childCount() const
{
    return m_lstChildItems.count();
}

int CTreeItem::columnCount() const
{
    return m_lstItemData.count();
}

QVariant CTreeItem::data(int column) const
{
    return m_lstItemData.value(column);
}

int CTreeItem::row() const
{
    if(m_pParentItem)
    {
        return m_pParentItem->m_lstChildItems.indexOf(const_cast<CTreeItem*>(this));
    }
}

CTreeItem *CTreeItem::parent()
{
    return m_pParentItem;
}
