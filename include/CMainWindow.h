#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include "stdafx.h"
#include "CDropShadowWidget.h"

class CToolBar;
class CTitleBar;
class CStatusBar;
class CMainWindow : public CDropShadowWidget
{

    Q_OBJECT
public:
    CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

    void      setTitleBarVisible(bool b);
    void      setToolBarVisible(bool b);
    void      setStatusBarvisible(bool b);

    void      setStatusBar(QWidget *widget);
    void      setToolBar(QWidget *widget);
    void      setTitleBar(QWidget *widget);
    void      setCentralWidget(QWidget *widget);

    void      setTitleBarPalette(QPalette pal);
    void      setToolBarPalette(QPalette pal);
    void      setStatusBarPAlette(QPalette pal);


    void      setTitleBarHeight(int height);
    void      setToolBarHeight(int height);
    void      setStatusBarHeight(int height);

    void      setBackgroundPixmap(QString pixName);
    void      loadToolBarConfigFile(QString strFile);

    void      setClosebtnIcon(QString pixname);
    void      setMinbtnIcon(QString pixname);

    void      setCurrentUser(QString userFlag);

    void      setVersion(QString version);
    void      setTitleText(QString title);
    void      setTitleStyleSheet(QString str);

    void      setTitlePixmap(QPixmap strPixmap);

    void      setShowLicenseOnly(bool b);
    void      setVersionVisible(bool b);
    void      setCloseButtonEnable(bool bEnabled);

    void      setChecked(QString strKey);
    void      disconnectCloseFuc();


	QWidget*   getCenteWidget();

private:
    CToolBar   *m_pwndToolBar;
    CTitleBar  *m_pwndTitleBar;
    CStatusBar *m_pwndStausBar;
    QWidget    *m_pwndCentral;

    QVBoxLayout *m_pvblMain;

public slots:
    void      sltClosed();

signals:
    void       sigToolBarClicked(QString strFlag);
    void       sigLogoClicked();
    void       sigExit();
};

#endif // CMAINWINDOW_H
