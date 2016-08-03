#include "../../include/CMainWindow.h"

#include "../CToolBar.h"
#include "../CTitleBar.h"
#include "../CStatusBar.h"

CMainWindow::CMainWindow(QWidget *parent)
    :CDropShadowWidget(parent)
{
    setContentsMargins(0, 0, 0, 0);
    m_pwndStausBar = new CStatusBar(this);
    m_pwndTitleBar = new CTitleBar(this);
    m_pwndToolBar = new CToolBar(this, "sysuser");
    m_pwndCentral = new QWidget(this);

    m_pvblMain = new QVBoxLayout();
    m_pvblMain->setContentsMargins(0, 0, 0, 0);
    m_pvblMain->setSpacing(0);

    m_pvblMain->addWidget(m_pwndTitleBar);
    m_pvblMain->addWidget(m_pwndToolBar);
    m_pvblMain->addWidget(m_pwndCentral);
    m_pvblMain->addWidget(m_pwndStausBar);
    setLayout(m_pvblMain);

    connect(m_pwndToolBar, SIGNAL(sigLogoClicked()), this, SIGNAL(sigLogoClicked()));
    connect(m_pwndTitleBar, SIGNAL(sigClose()), this, SLOT(sltClosed()));
    connect(m_pwndTitleBar, SIGNAL(sigClose()), this, SIGNAL(sigExit()));
    connect(m_pwndTitleBar, SIGNAL(sigShowMin()), this, SLOT(showMinimized()));
    connect(m_pwndToolBar, SIGNAL(sigClicked(QString)), this, SIGNAL(sigToolBarClicked(QString)));
}


CMainWindow::~CMainWindow()
{

}

void CMainWindow::setTitleBarVisible(bool b)
{
    m_pwndTitleBar->setVisible(b);
}

void CMainWindow::setToolBarVisible(bool b)
{
    m_pwndToolBar->setVisible(b);
}

void CMainWindow::setStatusBarvisible(bool b)
{
    m_pwndStausBar->setVisible(b);
}

void CMainWindow::setStatusBar(QWidget *widget)
{
    widget->setFixedHeight(m_pwndStausBar->height());
    m_pvblMain->removeWidget(m_pwndStausBar);
    m_pvblMain->removeWidget(m_pwndTitleBar);
    m_pvblMain->removeWidget(m_pwndToolBar);
    m_pvblMain->removeWidget(m_pwndCentral);
    m_pwndStausBar->setVisible(false);

    m_pwndStausBar = (CStatusBar*)widget;
    m_pvblMain->addWidget(m_pwndTitleBar);
    m_pvblMain->addWidget(m_pwndToolBar);
    m_pvblMain->addWidget(m_pwndCentral);
    m_pvblMain->addWidget(widget);
}

void CMainWindow::setToolBar(QWidget *widget)
{
    widget->setFixedHeight(m_pwndToolBar->height());
    m_pvblMain->removeWidget(m_pwndStausBar);
    m_pvblMain->removeWidget(m_pwndTitleBar);
    m_pvblMain->removeWidget(m_pwndToolBar);
    m_pvblMain->removeWidget(m_pwndCentral);
    m_pwndToolBar->setVisible(false);

    m_pwndToolBar = (CToolBar*)widget;
    m_pvblMain->addWidget(m_pwndTitleBar);
    m_pvblMain->addWidget(widget);
    m_pvblMain->addWidget(m_pwndCentral);
    m_pvblMain->addWidget(m_pwndStausBar);
}

void CMainWindow::setTitleBar(QWidget *widget)
{
    widget->setFixedHeight(m_pwndTitleBar->height());
    m_pvblMain->removeWidget(m_pwndStausBar);
    m_pvblMain->removeWidget(m_pwndTitleBar);
    m_pvblMain->removeWidget(m_pwndToolBar);
    m_pvblMain->removeWidget(m_pwndCentral);
    m_pwndTitleBar->setVisible(false);
    m_pwndTitleBar = (CTitleBar*)widget;
    m_pvblMain->addWidget(widget);
    m_pvblMain->addWidget(m_pwndToolBar);
    m_pvblMain->addWidget(m_pwndCentral);
    m_pvblMain->addWidget(m_pwndStausBar);
}

void CMainWindow::setCentralWidget(QWidget *widget)
{
    m_pvblMain->removeWidget(m_pwndStausBar);
    m_pvblMain->removeWidget(m_pwndTitleBar);
    m_pvblMain->removeWidget(m_pwndToolBar);
    m_pvblMain->removeWidget(m_pwndCentral);
   // m_pwndCentral->setVisible(false);
    m_pwndCentral->close();
    //delete m_pwndCentral;
    //m_pwndCentral = NULL;

    m_pwndCentral = widget;
    m_pvblMain->addWidget(m_pwndTitleBar);
    m_pvblMain->addWidget(m_pwndToolBar);
    m_pvblMain->addWidget(widget);
    m_pvblMain->addWidget(m_pwndStausBar);
}

void CMainWindow::setTitleBarPalette(QPalette pal)
{
    m_pwndTitleBar->setPalette(pal);
    m_pwndTitleBar->setAutoFillBackground(true);
}

void CMainWindow::setToolBarPalette(QPalette pal)
{
    m_pwndToolBar->setPalette(pal);
    m_pwndToolBar->setAutoFillBackground(true);
}

void CMainWindow::setStatusBarPAlette(QPalette pal)
{
    m_pwndStausBar->setPalette(pal);
    m_pwndStausBar->setAutoFillBackground(true);
}

void CMainWindow::setTitleBarHeight(int height)
{
    m_pwndTitleBar->setFixedHeight(height);
}

void CMainWindow::setToolBarHeight(int height)
{
    m_pwndToolBar->setFixedHeight(height);
}

void CMainWindow::setStatusBarHeight(int height)
{
    m_pwndStausBar->setFixedHeight(height);
}

void CMainWindow::setBackgroundPixmap(QString pixName)
{
    QPalette palette;
    QPixmap pixmap(pixName);
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    setPalette(palette);
}

void CMainWindow::loadToolBarConfigFile(QString strFile)
{
    m_pwndToolBar->readToolBarInfo(strFile);
}

void CMainWindow::setClosebtnIcon(QString pixname)
{
    m_pwndTitleBar->setCloseButtonIcon(pixname);
}

void CMainWindow::setMinbtnIcon(QString pixname)
{
    m_pwndTitleBar->setMinButtonIcon(pixname);
}

void CMainWindow::setCurrentUser(QString userFlag)
{
    m_pwndToolBar->setCurUser(userFlag);
}

void CMainWindow::setTitleText(QString title)
{
    m_pwndTitleBar->setTitleText(title);
}

void CMainWindow::setTitlePixmap(QPixmap strPixmap)
{
    m_pwndTitleBar->setTitlePixmap(strPixmap);
}


void CMainWindow::setShowLicenseOnly(bool b)
{
    m_pwndToolBar->setLicenseOnly(b);
}

void CMainWindow::setCloseButtonEnable(bool bEnabled)
{
    if(m_pwndTitleBar)
    {
        m_pwndTitleBar->setCloseButtonEnable(bEnabled);
    }
}

void CMainWindow::setChecked(QString strKey)
{
    m_pwndToolBar->setCheckedButton(strKey);
}

void CMainWindow::disconnectCloseFuc()
{
    disconnect(m_pwndTitleBar, SIGNAL(sigClose()), this, SLOT(sltClosed()));
}

QWidget* CMainWindow::getCenteWidget()
{
    return m_pwndCentral;
}

void CMainWindow::sltClosed()
{
    close();
}

