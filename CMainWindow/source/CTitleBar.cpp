#include "../CTitleBar.h"

#include "CPushButton.h"

#define ICON_WIDTH 16
#define ICON_HEIGHT 16
#define BUTTON_WIDTH 26
#define BUTTON_HEIGHT 26

CTitleBar::CTitleBar(QWidget *parent) :
    QLabel(parent)
{
    setContentsMargins(0, 0, 0, 0);
    setFixedHeight(BUTTON_HEIGHT);
    m_plblTitle = new QLabel(this);
    m_plblTitle->setObjectName("title");

    m_plblTitlePixmap = new QLabel(this);
    m_plblTitlePixmap->setContentsMargins(15, 0, 0, 0);

    m_pbtnMax = new CPushButton(this);
    m_pbtnMax->setIconSize(QSize(ICON_WIDTH, ICON_HEIGHT));
    m_pbtnMax->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    //m_pbtnMax->setAutoDefault(false);
    m_pbtnMax->setDefault(false);
    m_pbtnMax->setFocusPolicy(Qt::NoFocus);
    m_pbtnMax->setObjectName("titleButton");


    m_pbtnMin = new CPushButton(this);
    //m_pbtnMin->setAutoDefault(false);
    m_pbtnMin->setDefault(false);
    m_pbtnMin->setFocusPolicy(Qt::NoFocus);
    m_pbtnMin->setIconSize(QSize(ICON_WIDTH, ICON_HEIGHT));
    m_pbtnMin->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    m_pbtnMin->setPixName(":/tip/icon/ID_MIN_TITLEBAR");


    m_pbtnClose = new CPushButton(this);
    m_pbtnClose->setIconSize(QSize(ICON_WIDTH, ICON_HEIGHT));
    m_pbtnClose->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    m_pbtnClose->setPixName(":/tip/icon/ID_CLOSED_TITLEBAR");
    //m_pbtnClose->setAutoDefault(false);
    m_pbtnClose->setDefault(false);
    m_pbtnClose->setFocusPolicy(Qt::NoFocus);

    QHBoxLayout *phblMain = new QHBoxLayout();
    phblMain->setSpacing(0);
    phblMain->setContentsMargins(0, 0, 5, 0);
    phblMain->addWidget(m_plblTitlePixmap);
    phblMain->addSpacing(8);
    phblMain->addWidget(m_plblTitle);
    phblMain->addStretch();
    phblMain->addWidget(m_pbtnMax, 0, Qt::AlignTop);
    phblMain->addWidget(m_pbtnMin, 0, Qt::AlignTop);
    phblMain->addWidget(m_pbtnClose, 0, Qt::AlignTop);

    setLayout(phblMain);

    m_pbtnMax->setVisible(false);
    m_plblTitlePixmap->setVisible(false);

    connect(m_pbtnMin, SIGNAL(clicked()), this, SIGNAL(sigShowMin()));
    connect(m_pbtnClose, SIGNAL(clicked()), this, SIGNAL(sigClose()));
    connect(m_pbtnMax, SIGNAL(clicked()), this, SIGNAL(sigshowMax()));
}

void CTitleBar::setMinButtonVisible(bool b)
{
    if(m_pbtnMin->isVisible() == b)
    {
        return;
    }
    m_pbtnMin->setVisible(b);
}

void CTitleBar::setMaxButtonVisible(bool b)
{
    if(m_pbtnMax->isVisible() == b)
    {
        return;
    }
    m_pbtnMax->setVisible(b);
}

void CTitleBar::setCloseButtonVisible(bool b)
{
    if(m_pbtnClose->isVisible() == b)
    {
        return;
    }
    m_pbtnClose->setVisible(b);
}

void CTitleBar::setMaxButtonIcon(QString iconName)
{
    m_pbtnMax->setPixName(iconName);
}

void CTitleBar::setMinButtonIcon(QString iconName)
{
    m_pbtnMin->setPixName(iconName);
}

void CTitleBar::setCloseButtonIcon(QString iconName)
{
    m_pbtnClose->setPixName(iconName);
}

void CTitleBar::setTitleText(QString title)
{
    m_plblTitle->setText(title);
}

void CTitleBar::setTitlePixmap(QPixmap strPixmap)
{
    if(strPixmap.isNull())
    {
        m_plblTitlePixmap->setVisible(false);
    }
    m_plblTitlePixmap->setPixmap(strPixmap);
    m_plblTitlePixmap->setVisible(true);
}

void CTitleBar::setTitleStyleSheet(QString style)
{
    m_plblTitle->setStyleSheet(style);
}

void CTitleBar::setCloseButtonEnable(bool bEnabled)
{
    m_pbtnClose->setEnabled(bEnabled);
}


