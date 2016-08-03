
#include "../../include/CPageTreeWidget.h"

#include "../CPageTreeWidgetItem.h"


CPageTreeWidget::CPageTreeWidget(QWidget *parent)
    :QWidget(parent)
{
    m_pMainLayout = new QVBoxLayout();
    m_pMainLayout->setContentsMargins(0,1,0,0);
    m_pMainLayout->setSpacing(0);
    m_pMainLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    this->setLayout(m_pMainLayout);

    this->setObjectName("CPageTreeWidget");
    this->setStyleSheet("QWidget#CPageTreeWidget{\
                        background-color:#f6fafd;\
                        border-right: 1px solid #d7e6eb;\
                        border-top: 1px solid #d7e6eb;\
                        }");
}

CPageTreeWidget::~CPageTreeWidget()
{

}

void CPageTreeWidget::showFirstItem()
{
    QString strKey = findFirstItemKey();
    emit sigItemClick(strKey);
    updatePressState(strKey);
}

void CPageTreeWidget::setItemDataList(QList<TItemData> lstItemData)
{
    m_lstItemData = lstItemData;

    installTreeWidget();

}

QStringList CPageTreeWidget::getFullPathByKey(QString strKey)
{
    QStringList lstFullPath;
    TItemData itemData;
    bool bFind = false;
    for (int i = 0; i < m_lstItemData.count(); ++i)
    {
        itemData = m_lstItemData.at(i);
        if (itemData.strKey == strKey)
        {
            bFind = true;
            break;
        }
    }

    if(bFind)
    {
        lstFullPath = itemData.lstFullPath;
    }
    return lstFullPath;
}

void CPageTreeWidget::setCurrentClicked(QString strKey)
{
    emit sigItemClick(strKey);
    updatePressState(strKey);
}

void CPageTreeWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void CPageTreeWidget::installTreeWidget()
{
    for(int i = 0; i < m_lstItemData.count(); i++)
    {
        TItemData data = m_lstItemData.at(i);
        CPageTreeWidgetItem *pItem = new CPageTreeWidgetItem(data,this);
        connect(pItem,SIGNAL(sigItemClicked(QString)),this,SLOT(sltItemClick(QString)));

        if(data.parentId == -1)
        {
            m_pMainLayout->addWidget(pItem);
            m_lstTreeItem.append(pItem);
        }
        else
        {
            CPageTreeWidgetItem *pParentItem = findParentByID(data.parentId);
            if(pParentItem)
            {
                pParentItem->addSubItem(pItem);
                m_lstTreeItem.append(pItem);
            }
        }
    }
    m_pMainLayout->addStretch(1);
}

CPageTreeWidgetItem *CPageTreeWidget::findParentByID(int nParentID)
{
    CPageTreeWidgetItem *parent = NULL;
    for(int i= 0; i < m_lstTreeItem.count(); i++)
    {
        CPageTreeWidgetItem *pItem = m_lstTreeItem.at(i);
        if(pItem->isParent(nParentID))
        {
            parent = pItem;
            break;
        }
    }
    return parent;
}

void CPageTreeWidget::updatePressState(QString strKey)
{
    for(int i = 0; i < m_lstTreeItem.count(); i++)
    {
        CPageTreeWidgetItem *pItem = m_lstTreeItem.at(i);

        if(pItem->isItemByKey(strKey))
        {
            pItem->setIsPressState(true);
        }
        else
        {
            pItem->setIsPressState(false);
        }
    }
}

QString CPageTreeWidget::findFirstItemKey()
{
    QString strKey;
    for(int i = 0; i < m_lstTreeItem.count(); i++)
    {
        CPageTreeWidgetItem *pItem = m_lstTreeItem.at(i);
        if(!pItem->hasChild())
        {
            strKey = pItem->getKey();
            break;
        }
    }
    return strKey;
}

void CPageTreeWidget::sltItemClick(QString strKey)
{
    CPageTreeWidgetItem *sender = qobject_cast<CPageTreeWidgetItem *>(this->sender());
    if(sender->hasChild())
    {
        if(sender->isShow())
        {
            sender->hideSubItems();
        }
        else
        {
            sender->showSubItems();
        }
    }
    else
    {        
        emit sigItemClick(strKey);
        updatePressState(strKey);
    }
}

