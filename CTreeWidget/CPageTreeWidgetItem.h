#ifndef CPAGETREEWIDGETITEM_H
#define CPAGETREEWIDGETITEM_H

#include "stdafx.h"
#include "TItemStruct.h"

class CItemButton;

class CPageTreeWidgetItem : public QWidget
{
    Q_OBJECT
public:
    CPageTreeWidgetItem(TItemData data,QWidget *parent = NULL);
    ~CPageTreeWidgetItem();

    void                            addSubItem(CPageTreeWidgetItem *pWidget);
    void                            showSubItems();
    void                            hideSubItems();

    bool                            hasChild();
    bool                            isParent(int nParentID);
    bool                            isShow();

    void                            setIsPressState(bool bPress);
    bool                            isItemByKey(QString strKey);

    QString                         getKey();
private:
    QVBoxLayout                     *m_pVBoxLayout;

    CItemButton                     *m_pMainButton;

    TItemData                       m_tItemData;

    QList<CPageTreeWidgetItem *>    m_lstSubItems;
    bool                            m_bHasChild;
    bool                            m_bIsShow;

private slots:
    void                            sltMainButtonClicked();

signals:
    void                            sigItemClicked(QString);
};

#endif // CPAGETREEWIDGETITEM_H
