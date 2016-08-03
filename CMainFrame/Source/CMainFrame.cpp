
#include "../../include/CMainFrame.h"

#include <QApplication>
#include <QPainter>
#include <QStyleOption>
#include <QDomDocument>
#include <QFile>

#include "TItemStruct.h"
#include "CNavigationToolBar.h"
#include "CPageTreeWidget.h"
#include "CSwitchPageToolBar.h"

CMainFrame::CMainFrame(QWidget *parent)
    :QWidget(parent)
{
    m_pMainLayout = new QHBoxLayout();
    this->setLayout(m_pMainLayout);

//    this->setObjectName("CMainFrame");
//    this->setStyleSheet("QWidget#CMainFrame{\
//                        border-left:1px solid #368ee0;\
//                        border-right:1px solid #368ee0;\
//                        }");

    m_pMainLayout->setContentsMargins(0,2,0,0);
    m_pMainLayout->setSpacing(0);


    m_pLeftTree = new CPageTreeWidget(this);
    connect(m_pLeftTree,SIGNAL(sigItemClick(QString)),this,SLOT(sltTabItemClicked(QString)));
    m_pLeftTree->setFixedWidth(150);


    m_pContentLayout = new QVBoxLayout();

    m_pNavigationBar = new CNavigationToolBar(this);
    connect(m_pNavigationBar,SIGNAL(sigAdd()),this,SIGNAL(sigAdd()));
    connect(m_pNavigationBar,SIGNAL(sigRemove()),this,SIGNAL(sigRemove()));
    connect(m_pNavigationBar,SIGNAL(sigShowList()),this,SIGNAL(sigShowList()));
    connect(m_pNavigationBar,SIGNAL(sigShowThumbnail()),this,SIGNAL(sigShowThumbnail()));    
    connect(m_pNavigationBar,SIGNAL(sigResearch(QString)),this,SIGNAL(sigResearch(QString)));

    connect(m_pNavigationBar,SIGNAL(sigTimeSelection(QString)),this,SLOT(sltTimeSelection(QString)));


    m_pSwitchPageBar = new CSwitchPageToolBar(this);
    connect(m_pSwitchPageBar,SIGNAL(sigGotoPage(int)),this,SLOT(sltGotoPage(int)));



    m_pContetWidget = new QWidget(this);
    m_pContetWidget->setStyleSheet("background-color:white");

    m_pContentLayout->addWidget(m_pNavigationBar);
    m_pContentLayout->addWidget(m_pContetWidget);
    m_pContentLayout->addWidget(m_pSwitchPageBar);


    m_pMainLayout->addWidget(m_pLeftTree,0,Qt::AlignLeft);
    m_pMainLayout->setSpacing(0);
    m_pMainLayout->addLayout(m_pContentLayout);

    m_bShowFirst = false;

    TItemSate state;
    state.strKey = "Single";
    state.nCurrentPage = 1;
    state.nTotalRecordCount = 0;
    state.strTime = "0-24";

    m_strCurrentKey = "Single";

    m_mapItemState.insert(m_strCurrentKey,state);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

CMainFrame::~CMainFrame()
{

}

void CMainFrame::showFirstItem()
{
    if(!m_bShowFirst)
    {
        m_bShowFirst = true;
        m_pLeftTree->showFirstItem();
    }
}

void CMainFrame::setCurrentItem(QString strKey)
{
    if(m_pLeftTree != NULL)
    {
        m_pLeftTree->setCurrentClicked(strKey);
    }
}

void CMainFrame::initSate()
{
    for(int i = 0; i < m_lstItemData.count(); i++)
    {
        TItemData data = m_lstItemData.at(i);
        TItemSate state;
        state.strKey = data.strKey;
        state.nCurrentPage = 1;
        state.nTotalRecordCount = 0;
        state.strTime = "0-24";

        m_mapItemState.insert(data.strKey,state);
    }
}

void CMainFrame::setLeftTreeVisible(bool bShow)
{
    if(bShow)
    {
        m_pLeftTree->show();
    }
    else
    {
        m_pLeftTree->hide();
    }
}

void CMainFrame::setNavigationBarVisible(bool bShow)
{
    if(bShow)
    {
        m_pNavigationBar->show();
    }
    else
    {
        m_pNavigationBar->hide();
    }
}

void CMainFrame::setSwitchPageBarVisible(bool bShow)
{
    if(bShow)
    {        
        m_pSwitchPageBar->show();
        TItemSate state = m_mapItemState.value(m_strCurrentKey);
        m_pSwitchPageBar->setTotalRecordNumber(state.nTotalRecordCount);
        m_pSwitchPageBar->setCurrentPage(state.nCurrentPage);
    }
    else
    {
        m_pSwitchPageBar->hide();
    }
}

void CMainFrame::setResearchVisible(bool bShow)
{
    m_pNavigationBar->setShowResearch(bShow);
}

void CMainFrame::setwAddRemoveVisible(bool bShow)
{
    m_pNavigationBar->setShowAddRemove(bShow);
}

void CMainFrame::setChoiceTimeVisible(bool bShow)
{
    m_pNavigationBar->setShowChoiceTime(bShow);
    if(bShow)
    {
        TItemSate state = m_mapItemState.value(m_strCurrentKey);
        m_pNavigationBar->setChoiceTimeCurrentIndex(state.strTime);
    }
}

void CMainFrame::setDisplayModeVisible(bool bShow)
{
    m_pNavigationBar->setShowDisplayMode(bShow);
}

void CMainFrame::resetChiceTime()
{
    m_pNavigationBar->resetChiceTime();
}

void CMainFrame::clearGotoPageNum()
{
    m_pSwitchPageBar->clearGoPageNum();
}

void CMainFrame::clearResearch()
{
    m_pNavigationBar->clearResearch();
}

void CMainFrame::setNavWidget(QWidget *pCustomWidget)
{
    m_pNavigationBar->setWidget(pCustomWidget);
}

void CMainFrame::insertNavToolButton(QToolButton *pToolButton, int option)
{
    m_pNavigationBar->insertToolButton(pToolButton,option);
}

QToolButton *CMainFrame::getNavAddButton()
{
    return m_pNavigationBar->getAddButton();
}

QToolButton *CMainFrame::getNavRemoveButton()
{
    return m_pNavigationBar->getRemoveButton();
}


void CMainFrame::resetSwitchPageBar()
{
    TItemSate state = m_mapItemState.value(m_strCurrentKey);
    state.nCurrentPage = 1;
    state.nTotalRecordCount = 0;
    m_mapItemState.insert(m_strCurrentKey,state);
    m_pSwitchPageBar->setTotalRecordNumber(state.nTotalRecordCount);
    m_pSwitchPageBar->setCurrentPage(state.nCurrentPage);
}

void CMainFrame::setRecordNumber(int nCount)
{
    TItemSate state = m_mapItemState.value(m_strCurrentKey);
    state.nTotalRecordCount = nCount;
    m_pSwitchPageBar->setTotalRecordNumber(nCount);
    m_pSwitchPageBar->setCurrentPage(state.nCurrentPage);
    state.nCurrentPage = m_pSwitchPageBar->getCurrentPage();

    m_mapItemState.insert(m_strCurrentKey,state);
}

void CMainFrame::getCurrentPage(int &nIndex, int &nCount)
{
    TItemSate state = m_mapItemState.value(m_strCurrentKey);
    nIndex = state.nCurrentPage - 1;
    nCount = 20;
}

QList<int> CMainFrame::getCurrentTime()
{
    QList<int> lstTime;
    TItemSate state = m_mapItemState.value(m_strCurrentKey);
    QString strTime = state.strTime;
    QStringList strListTime = strTime.split('-');
    if(strListTime.count() == 2)
    {
        lstTime.append(strListTime.at(0).toInt());
        lstTime.append(strListTime.at(1).toInt());
    }
    return lstTime;
}

void CMainFrame::setSwitchPageEnable(bool bEnable)
{
    m_pSwitchPageBar->setSwitchPageEnable(bEnable);
}

void CMainFrame::installLeftTreeWidget(QString strConfigFile)
{
    parseXML(strConfigFile);
    m_pLeftTree->setItemDataList(m_lstItemData);

    initSate();
}

QStringList CMainFrame::getTableHeadDataByKey(QString strKey)
{
    QStringList lstHeadData;
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
        lstHeadData = itemData.lstTableHead;
    }
    return lstHeadData;
}

void CMainFrame::setLocation(QStringList lstLocaltion)
{
    m_pNavigationBar->setTitle(lstLocaltion);
}

void CMainFrame::setContentWidget(QWidget *pContent)
{
    m_pContentLayout->removeWidget(m_pNavigationBar);
    m_pContentLayout->removeWidget(m_pContetWidget);
    m_pContentLayout->removeWidget(m_pSwitchPageBar);
    m_pContetWidget->hide();

    m_pContetWidget = pContent;
    m_pContentLayout->addWidget(m_pNavigationBar);
    m_pContentLayout->addWidget(m_pContetWidget);
    m_pContentLayout->addWidget(m_pSwitchPageBar);
    m_pContetWidget->show();

}

void CMainFrame::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

QStringList CMainFrame::getLocationPath(QString strLocation)
{
    return m_pLeftTree->getFullPathByKey(strLocation);
}

void CMainFrame::parseXML(QString strFilePath)
{
    if(strFilePath.isEmpty())
    {
        return;
    }

    QFile file(strFilePath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }

   QDomDocument document;
   QString error;
   int row = 0, column = 0;
   if(!document.setContent(&file, false, &error, &row, &column))
   {
       return;
   }

   if(document.isNull())
   {
       return;
   }

   QDomElement root = document.documentElement();
   QDomNodeList list = root.childNodes();
   int count = list.count();
   for(int i=0; i < count; ++i)
   {
       QDomNode dom_node = list.item(i);
       QDomElement element = dom_node.toElement();

       QDomNodeList child_list = element.childNodes();
       int child_count = child_list.count();

       TItemData data;

       for(int j=0; j<child_count; ++j)
       {
           QDomNode child_dom_node = child_list.item(j);
           QDomElement child_element = child_dom_node.toElement();
           QString child_tag_name = child_element.tagName();
           QString child__tag_value = child_element.text();
           if(QString::compare(child_tag_name, "parentID") == 0)
           {
                data.parentId = child__tag_value.toInt();
           }
           else if(QString::compare(child_tag_name, "ID") == 0)
           {
                data.id = child__tag_value.toInt();
           }
           else if(QString::compare(child_tag_name, "key") == 0)
           {
                data.strKey = child__tag_value;
           }
           else if(QString::compare(child_tag_name, "text") == 0)
           {
                data.text = child__tag_value;
           }
           else if(QString::compare(child_tag_name, "normalicon") == 0)
           {
                data.strNormalIcon = child__tag_value;
           }
           else if(QString::compare(child_tag_name, "checkedicon") == 0)
           {
                data.strCheckedIcon = child__tag_value;
           }
           else if(QString::compare(child_tag_name, "fontname") == 0)
           {
                data.strFontName = child__tag_value;
           }
           else if(QString::compare(child_tag_name, "fontsize") == 0)
           {
                data.nFontSize = child__tag_value.toInt();
           }
           else if(QString::compare(child_tag_name, "expandicon") == 0)
           {
               data.strExpandIcon = child__tag_value;
           }
           else if(QString::compare(child_tag_name, "collapseicon") == 0)
           {
               data.strCollapseIcon = child__tag_value;
           }
           else if(QString::compare(child_tag_name, "fontbold") == 0)
           {
                data.bBold = child__tag_value.toInt();
           }
           else if(QString::compare(child_tag_name, "hasbottomborder") == 0)
           {
                data.bHasBottomBorder = child__tag_value.toInt();
           }
           else if(QString::compare(child_tag_name, "fullpath") == 0)
           {
               QString strFullPath = child__tag_value;
               data.lstFullPath = strFullPath.split(";");
           }
           else if(QString::compare(child_tag_name, "tablehead") == 0)
           {
               QString strTableHead = child__tag_value;
               data.lstTableHead = strTableHead.split(";");
           }
      }
#if defined Q_OS_LINUX
      if(data.strKey != "USBAccessControl")
      {
          m_lstItemData.append(data);
      }
#else
       m_lstItemData.append(data);
#endif
   }
}

void CMainFrame::sltTabItemClicked(QString strKey)
{
    QStringList lstPath = getLocationPath(strKey);
    m_pNavigationBar->setTitle(lstPath);

    m_strCurrentKey = strKey;

    emit sigTabItemClick(strKey);
}

void CMainFrame::sltGotoPage(int nPageNumber)
{
    m_pSwitchPageBar->clearFocus();
    TItemSate state = m_mapItemState.value(m_strCurrentKey);
    state.nCurrentPage = nPageNumber;
    m_mapItemState.insert(m_strCurrentKey,state);

    emit sigGotoPage(m_strCurrentKey);
}

void CMainFrame::sltTimeSelection(QString strTime)
{
    TItemSate state = m_mapItemState.value(m_strCurrentKey);
    state.strTime = strTime;
    m_mapItemState.insert(m_strCurrentKey,state);

    emit sigTimeSelection(m_strCurrentKey);
}
