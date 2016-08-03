
#include "../CPageTreeWidgetItem.h"

#include "../CItemButton.h"


CPageTreeWidgetItem::CPageTreeWidgetItem(TItemData data, QWidget *parent)
    :QWidget(parent)
{
    m_tItemData = data;

    m_pVBoxLayout = new QVBoxLayout();
    m_pVBoxLayout->setContentsMargins(0,0,0,0);
    m_pVBoxLayout->setSpacing(0);
    m_pVBoxLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    this->setLayout(m_pVBoxLayout);

    m_bHasChild = false;
    m_bIsShow = true;


    m_pMainButton = new CItemButton(this);

    m_pMainButton->setText(m_tItemData.text);
    m_pMainButton->setNormalIcon(m_tItemData.strNormalIcon);
    m_pMainButton->setCheckedIcon(m_tItemData.strCheckedIcon);
    if(m_tItemData.strExpandIcon != "")
    {
        m_pMainButton->setDirectIcon(m_tItemData.strExpandIcon,m_tItemData.strCollapseIcon);
    }
    m_pMainButton->setKey(m_tItemData.strKey);
    m_pMainButton->sethasbottomBorder(m_tItemData.bHasBottomBorder);

    QFont font;
    font.setBold(m_tItemData.bBold);
    font.setFamily(m_tItemData.strFontName);
    font.setPixelSize(m_tItemData.nFontSize);
    m_pMainButton->setTextFont(font);

    connect(m_pMainButton,SIGNAL(clicked()),this,SLOT(sltMainButtonClicked()));


    m_pVBoxLayout->addWidget(m_pMainButton);
}

CPageTreeWidgetItem::~CPageTreeWidgetItem()
{

}

void CPageTreeWidgetItem::addSubItem(CPageTreeWidgetItem *pWidget)
{
    m_bHasChild = true;
    m_lstSubItems.append(pWidget);
    m_pVBoxLayout->addWidget(pWidget);
}

void CPageTreeWidgetItem::showSubItems()
{
    m_bIsShow = true;
    for(int i = 0; i < m_lstSubItems.count(); i++)
    {
       QWidget *pWidget = m_lstSubItems.at(i);
       pWidget->show();
    }
    m_pMainButton->expand();
}

void CPageTreeWidgetItem::hideSubItems()
{
    m_bIsShow = false;
    for(int i = 0; i < m_lstSubItems.count(); i++)
    {
        QWidget *pWidget = m_lstSubItems.at(i);
        pWidget->hide();
    }
    m_pMainButton->collapse();
}

bool CPageTreeWidgetItem::hasChild()
{
    return m_bHasChild;
}

bool CPageTreeWidgetItem::isParent(int nParentID)
{
    return m_tItemData.id == nParentID;
}

bool CPageTreeWidgetItem::isShow()
{
    return m_bIsShow;
}

void CPageTreeWidgetItem::setIsPressState(bool bPress)
{
    if(m_bHasChild)
    {
        m_pMainButton->setIsPressed(false);
    }
    else
    {
        m_pMainButton->setIsPressed(bPress);
    }
}

bool CPageTreeWidgetItem::isItemByKey(QString strKey)
{
    if(strKey == m_tItemData.strKey)
    {
        return true;
    }
    return false;
}

QString CPageTreeWidgetItem::getKey()
{
    return m_tItemData.strKey;
}

void CPageTreeWidgetItem::sltMainButtonClicked()
{    
    QString strKey = m_pMainButton->getKey();
    emit sigItemClicked(strKey);
}
