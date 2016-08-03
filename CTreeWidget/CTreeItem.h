#ifndef CTREEITEM_H
#define CTREEITEM_H


#include <QList>
#include <QVariant>


class CTreeItem
{
public:
    explicit CTreeItem(const QList<QVariant> &data, CTreeItem *parent = 0);
    ~CTreeItem();

    void                appendChild(CTreeItem *child);
    CTreeItem           *child(int row);
    int                 childCount() const;
    int                 columnCount() const;
    QVariant            data(int column) const;
    int                 row() const;
    CTreeItem           *parent();

private:
    QList<CTreeItem*>   m_lstChildItems;
    QList<QVariant>     m_lstItemData;
    CTreeItem           *m_pParentItem;
};

#endif // CTREEITEM_H
