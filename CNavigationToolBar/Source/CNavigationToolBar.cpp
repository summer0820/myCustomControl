
#include "../../include/CNavigationToolBar.h"


#include "../CLocationBar.h"
#include "../CSearchWidget.h"

CNavigationToolBar::CNavigationToolBar(QWidget *parent)
    :QWidget(parent)
{
    m_pMainLayout= new QHBoxLayout();
    m_pMainLayout->setContentsMargins(20,5,15,5);
    m_pMainLayout->setSpacing(5);

    this->setLayout(m_pMainLayout);
    this->setObjectName("CNavigationToolBar");
    this->setStyleSheet("QWidget#CNavigationToolBar{\
                        border-top:1px solid #d7e6eb;\
                        border-bottom:1px solid #d7e6eb;\
                        background-color:white;\
                        }");

    this->setFixedHeight(37);

    m_textFont.setPixelSize(12);
    m_textFont.setFamily(QString::fromLocal8Bit("微软雅黑"));

    m_pCustomWidget = NULL;
    m_lstHeadAddedWidget.clear();
    m_lstTailAddedWidget.clear();

    m_pLocationBar = new CLocationBar(this);
    m_pSearchWidget = new CSearchWidget(this);
    connect(m_pSearchWidget,SIGNAL(sigResearch(QString)),this,SIGNAL(sigResearch(QString)));

    initDisplayButton();
    initAddRemoveButton();
    initChoiceTimeUI();

    m_pMainLayout->addWidget(m_pLocationBar,1,Qt::AlignLeft);
    m_pMainLayout->addWidget(m_pBtnAdd,0,Qt::AlignRight);
    m_pMainLayout->addWidget(m_pBtnRemove,0,Qt::AlignRight);
    m_pMainLayout->addWidget(m_pBtnList,0,Qt::AlignRight);
    m_pMainLayout->addWidget(m_pBtnThumbnail,0,Qt::AlignRight);
    m_pMainLayout->addWidget(m_pLabelChoiceTime,0,Qt::AlignRight);
    m_pMainLayout->addWidget(m_pComboChoiceTime,0,Qt::AlignRight);
    m_pMainLayout->addWidget(m_pSearchWidget,0,Qt::AlignRight);

    m_bIsShowAddRemoveWidget = false;
    m_bIsShowChoiceTime = false;
    m_bIsShowDisplayMode = false;
    m_bIsShowSearchWidget = false;

    updateShowState();
}

CNavigationToolBar::~CNavigationToolBar()
{

}

void CNavigationToolBar::setTitle(QStringList lstTitle)
{
    m_pLocationBar->setTitle(lstTitle);
}

void CNavigationToolBar::setShowResearch(bool bShow)
{
    m_bIsShowSearchWidget = bShow;
    updateShowState();
}

void CNavigationToolBar::setShowAddRemove(bool bShow)
{
    m_bIsShowAddRemoveWidget = bShow;
    updateShowState();
}

void CNavigationToolBar::setShowChoiceTime(bool bShow)
{
    m_bIsShowChoiceTime = bShow;
    updateShowState();
}

void CNavigationToolBar::setShowDisplayMode(bool bShow)
{
    m_bIsShowDisplayMode = bShow;
    updateShowState();
}

void CNavigationToolBar::setChoiceTimeCurrentIndex(QString strData)
{
    int count = m_pComboChoiceTime->count();
    for(int index=0; index<count; ++index)
    {
        QString itemData = m_pComboChoiceTime->itemData(index).toString();
        if(itemData == strData)
        {
            m_pComboChoiceTime->setCurrentIndex(index);
            break;
        }
    }
}

void CNavigationToolBar::setWidget(QWidget *pCustomWidget)
{
    m_pMainLayout->removeWidget(m_pLocationBar);
    m_pLocationBar->setVisible(false);

    m_pMainLayout->removeWidget(m_pBtnAdd);
    m_pBtnAdd->setVisible(false);

    m_pMainLayout->removeWidget(m_pBtnRemove);
    m_pBtnRemove->setVisible(false);

    m_pMainLayout->removeWidget(m_pBtnList);
    m_pBtnList->setVisible(false);

    m_pMainLayout->removeWidget(m_pBtnThumbnail);
    m_pBtnThumbnail->setVisible(false);

    m_pMainLayout->removeWidget(m_pLabelChoiceTime);
    m_pLabelChoiceTime->setVisible(false);

    m_pMainLayout->removeWidget(m_pComboChoiceTime);
    m_pComboChoiceTime->setVisible(false);

    m_pMainLayout->removeWidget(m_pSearchWidget);
    m_pSearchWidget->setVisible(false);

    for(int i = 0; i < m_lstHeadAddedWidget.count(); i++)
    {
        m_pMainLayout->removeWidget(m_lstHeadAddedWidget.at(i));
        m_lstHeadAddedWidget.at(i)->setVisible(false);
    }
    for(int i = 0; i < m_lstTailAddedWidget.count(); i++)
    {
        m_pMainLayout->removeWidget(m_lstTailAddedWidget.at(i));
        m_lstTailAddedWidget.at(i)->setVisible(false);
    }

    if(m_pCustomWidget)
    {
        m_pMainLayout->removeWidget(m_pCustomWidget);
        m_pCustomWidget->setVisible(false);
    }

    m_pCustomWidget = pCustomWidget;
    m_pMainLayout->addWidget(m_pCustomWidget);
    m_pCustomWidget->setVisible(true);
}

void CNavigationToolBar::insertToolButton(QToolButton *pToolButton, int opt)
{
    pToolButton->setFixedSize(70,23);
    pToolButton->setIconSize(QSize(16,16));

    switch (opt) {
    case 0:
    {
        m_lstHeadAddedWidget.prepend(pToolButton);

        //clear layout
        m_pMainLayout->removeWidget(m_pLocationBar);
        m_pMainLayout->removeWidget(m_pBtnAdd);
        m_pMainLayout->removeWidget(m_pBtnRemove);
        m_pMainLayout->removeWidget(m_pBtnList);
        m_pMainLayout->removeWidget(m_pBtnThumbnail);
        m_pMainLayout->removeWidget(m_pLabelChoiceTime);
        m_pMainLayout->removeWidget(m_pComboChoiceTime);
        m_pMainLayout->removeWidget(m_pSearchWidget);

        for(int i = 0; i < m_lstHeadAddedWidget.count(); i++)
        {
            m_pMainLayout->removeWidget(m_lstHeadAddedWidget.at(i));
        }
        for(int i = 0; i < m_lstTailAddedWidget.count(); i++)
        {
            m_pMainLayout->removeWidget(m_lstTailAddedWidget.at(i));
        }


        //add widget
        m_pMainLayout->addWidget(m_pLocationBar,1,Qt::AlignLeft);
        for(int i = 0; i < m_lstHeadAddedWidget.count(); i++)
        {
            m_pMainLayout->addWidget(m_lstHeadAddedWidget.at(i),0,Qt::AlignRight);
        }

        m_pMainLayout->addWidget(m_pBtnAdd,0,Qt::AlignRight);
        m_pMainLayout->addWidget(m_pBtnRemove,0,Qt::AlignRight);
        m_pMainLayout->addWidget(m_pBtnList,0,Qt::AlignRight);
        m_pMainLayout->addWidget(m_pBtnThumbnail,0,Qt::AlignRight);
        m_pMainLayout->addWidget(m_pLabelChoiceTime,0,Qt::AlignRight);
        m_pMainLayout->addWidget(m_pComboChoiceTime,0,Qt::AlignRight);
        m_pMainLayout->addWidget(m_pSearchWidget,0,Qt::AlignRight);

        for(int i = 0; i < m_lstTailAddedWidget.count(); i++)
        {
            m_pMainLayout->addWidget(m_lstTailAddedWidget.at(i),0,Qt::AlignRight);
        }
    }
        break;
    case 1:
    {
        m_lstTailAddedWidget.append(pToolButton);
        m_pMainLayout->addWidget(pToolButton,0,Qt::AlignRight);
    }
        break;
    default:
        break;
    }

}

QToolButton *CNavigationToolBar::getAddButton()
{
    return m_pBtnAdd;
}

QToolButton *CNavigationToolBar::getRemoveButton()
{
    return m_pBtnRemove;
}

void CNavigationToolBar::resetChiceTime()
{
    if(m_pComboChoiceTime != NULL)
    {
        m_pComboChoiceTime->setCurrentIndex(0);
        sltCurrentCMBItem(0);
    }
}

void CNavigationToolBar::clearResearch()
{
    m_pSearchWidget->clearString();
}

void CNavigationToolBar::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void CNavigationToolBar::updateShowState()
{
    if(m_bIsShowAddRemoveWidget)
    {
        m_pBtnAdd->setVisible(true);
        m_pBtnRemove->setVisible(true);
    }
    else
    {
        m_pBtnAdd->setVisible(false);
        m_pBtnRemove->setVisible(false);
    }

    if(m_bIsShowChoiceTime)
    {
        m_pLabelChoiceTime->setVisible(true);
        m_pComboChoiceTime->setVisible(true);
    }
    else
    {
        m_pLabelChoiceTime->setVisible(false);
        m_pComboChoiceTime->setVisible(false);
    }

    if(m_bIsShowDisplayMode)
    {
        m_pBtnList->setVisible(true);
        m_pBtnThumbnail->setVisible(true);
    }
    else
    {
        m_pBtnList->setVisible(false);
        m_pBtnThumbnail->setVisible(false);
    }

    if(m_bIsShowSearchWidget)
    {
        m_pSearchWidget->setVisible(true);
    }
    else
    {
        m_pSearchWidget->setVisible(false);
    }
}

void CNavigationToolBar::initChoiceTimeUI()
{
    m_pLabelChoiceTime = new QLabel(this);
    m_pLabelChoiceTime->setText(QString::fromLocal8Bit("时间段选择："));
    m_pLabelChoiceTime->setFont(m_textFont);
    m_pLabelChoiceTime->setStyleSheet("QLabel{color:#368ee0;}");


    //QLineEdit *lineEdit = new QLineEdit;
    //lineEdit->setReadOnly(true);
    //lineEdit->setAlignment(Qt::AlignCenter);

    m_pComboChoiceTime = new QComboBox(this);
    //m_pComboChoiceTime->setLineEdit(lineEdit);
    m_pComboChoiceTime->setCursor(Qt::ArrowCursor);

    QString strDownIcon = ":/tip/icon/navigationbar/HIDI_NAVIGATION_COMBOBOX_DOWN.png";
    QString strUpIcon =  ":/tip/icon/navigationbar/HIDI_NAVIGATION_COMBOBOX_UP.png";

    QListView *listView = new QListView(m_pComboChoiceTime);
    listView->setStyleSheet("QListView{ \
                            outline: none; \
                            background-color:#ffffff;\
                            border:1px solid #dfedfd;\
                            }\
                            QListView::item {\
                             border-top: 1px solid #dfedfd; margin:0px;\
                             padding-left:20px;padding-right: 10px; \
                             height: 24px;}  \
                            QListView::item:!hover:!pressed:!selected{ \
                            color:#000000;font-size:12px;\
                           } \
                             QListView::item:hover:!pressed { \
                             background-color: #368ee0;\
                             color:#ffffff;font-size:12px;\
                            }                                               \
                            QListView::item:selected:!hover { \
                            background-color: #368ee0;\
                            color:#ffffff;font-size:12px;\
                            } \
                            ");
    m_pComboChoiceTime->setView(listView);

    m_pComboChoiceTime->setStyleSheet(QString("\
                                     QComboBox{\
                                         border: 1px solid #dfedfd;\
                                         border-radius:2px;\
                                         padding-left:20px;\
                                         padding-right:10px;\
                                         color:#000000;font-size:12px;\
                                         background-color: #ffffff;\
                                         }\
                                     QComboBox::drop-down {\
                                         subcontrol-origin: padding;\
                                         subcontrol-position: top right;\
                                         border-left-width:0px;\
                                         border-left-color: darkgray;\
                                         border-left-style: solid;\
                                         border-top-right-radius:0px;\
                                         border-bottom-right-radius:0px;\
                                         color:#ffffff;font-size:12px;\
                                     }\
                                     QComboBox::down-arrow {\
                                         image: url(%1);\
                                     }\
                                     QComboBox::down-arrow:on { \
                                         image: url(%2);\
                                     }\
                                     ").arg(strDownIcon).arg(strUpIcon));

    m_pComboChoiceTime->addItem("00:00-24:00","0-24");
    m_pComboChoiceTime->addItem("00:00-04:00","0-4");
    m_pComboChoiceTime->addItem("04:00-08:00","4-8");
    m_pComboChoiceTime->addItem("08:00-12:00","8-12");
    m_pComboChoiceTime->addItem("12:00-16:00","12-16");
    m_pComboChoiceTime->addItem("16:00-20:00","16-20");
    m_pComboChoiceTime->addItem("20:00-24:00","20-24");

    m_pComboChoiceTime->setFixedHeight(23);
    m_pComboChoiceTime->setFixedWidth(140);
    m_pComboChoiceTime->setCurrentIndex(0);

    connect(m_pComboChoiceTime,SIGNAL(activated(int)),this,SLOT(sltCurrentCMBItem(int)));

}

void CNavigationToolBar::initDisplayButton()
{
    m_pIconListSelected = new QIcon(":/tip/icon/navigationbar/HIDI_NAVIGATION_LIST_SELECTED.png");
    m_pIconListNormal = new QIcon(":/tip/icon/navigationbar/HIDI_NAVIGATION_LIST_NORMAL.png");
    m_pIconThumbnailSelected = new QIcon(":/tip/icon/navigationbar/HIDI_NAVIGATION_THUMBNAIL_SELECTED.png");
    m_pIconThumbnailNormal = new QIcon(":/tip/icon/navigationbar/HIDI_NAVIGATION_THUMBNAIL_NORMAL.png");

    QString strBtnStyle = "QPushButton {\
            border: none;\
            background-color: #ffffff;\
            }";

    m_pBtnList = new QPushButton(this);
    m_pBtnList->setIcon(*m_pIconListSelected);
    m_pBtnList->setStyleSheet(strBtnStyle);
    m_pBtnList->setFixedSize(30,30);
    connect(m_pBtnList,SIGNAL(clicked()),this,SLOT(sltListDisplayClicked()));

    m_pBtnThumbnail = new QPushButton(this);
    m_pBtnThumbnail->setIcon(*m_pIconThumbnailNormal);
    m_pBtnThumbnail->setStyleSheet(strBtnStyle);
    m_pBtnThumbnail->setFixedSize(30,30);
    connect(m_pBtnThumbnail,SIGNAL(clicked()),this,SLOT(sltThumbnailDisplayClicked()));
}

void CNavigationToolBar::initAddRemoveButton()
{
    QString strAddBtnStyle = "QToolButton{\
            border: 0px solid gray;\
            border-radius:2px;\
            background-color: #78cc50;\
            padding-left:10px;padding-right: 10px;\
            color:#ffffff;font-size:12px;\
            }\
            QToolButton:hover:!pressed\
            {\
                border: 0px solid gray;\
                border-radius:2px;\
                background-color: #8ee963;\
                color:#ffffff;font-size:12px;\
            }\
            QToolButton:pressed\
            {\
                border: 0px solid gray;\
                border-radius:2px;\
                background-color: #8deb60;\
                color:#ffffff;font-size:12px;\
            }";

    m_pBtnAdd = new QToolButton(this);
    m_pBtnAdd->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QIcon addicon(":/tip/icon/navigationbar/HIDI_NAVIGATION_ADD.png");
    m_pBtnAdd->setIcon(addicon);
    m_pBtnAdd->setText(QString::fromLocal8Bit("添加"));
    m_pBtnAdd->setStyleSheet(strAddBtnStyle);
    m_pBtnAdd->setIconSize(QSize(16, 16));
    m_pBtnAdd->setFixedSize(70,23);
    connect(m_pBtnAdd,SIGNAL(clicked()),this,SIGNAL(sigAdd()));

    QString strRemoveBtnStyle = "QToolButton{\
            border: 0px solid gray;\
            border-radius:2px;\
            background-color: #ff6c60;\
            padding-left:10px;padding-right: 10px;\
            color:#ffffff;font-size:12px;\
            }\
            QToolButton:hover:!pressed\
            {\
                border: 0px solid gray;\
                border-radius:2px;\
                background-color: #fe7e7e;\
                color:#ffffff;font-size:12px;\
            }\
            QToolButton:pressed\
            {\
                border: 0px solid gray;\
                border-radius:2px;\
                background-color: #ee4444;\
                color:#ffffff;font-size:12px;\
            }";

    m_pBtnRemove = new QToolButton(this);
    m_pBtnRemove->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QIcon removeicon(":/tip/icon/navigationbar/HIDI_NAVIGATION_REMOVE.png");
    m_pBtnRemove->setIcon(removeicon);
    m_pBtnRemove->setIconSize(QSize(16,16));
    m_pBtnRemove->setText(QString::fromLocal8Bit("删除"));
    m_pBtnRemove->setStyleSheet(strRemoveBtnStyle);
    m_pBtnRemove->setFixedSize(70,23);
    connect(m_pBtnRemove,SIGNAL(clicked()),this,SIGNAL(sigRemove()));
}

void CNavigationToolBar::sltListDisplayClicked()
{
    m_pBtnList->setIcon(*m_pIconListSelected);
    m_pBtnThumbnail->setIcon(*m_pIconThumbnailNormal);

    emit sigShowList();
}

void CNavigationToolBar::sltThumbnailDisplayClicked()
{
    m_pBtnList->setIcon(*m_pIconListNormal);
    m_pBtnThumbnail->setIcon(*m_pIconThumbnailSelected);

    emit sigShowThumbnail();
}

void CNavigationToolBar::sltCurrentCMBItem(int nIndex)
{
    QString strTime = m_pComboChoiceTime->itemData(nIndex).toString();
    qDebug("%s",qPrintable(strTime));
    emit sigTimeSelection(strTime);
}
