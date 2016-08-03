#ifndef CTOOLBAR
#define CTOOLBAR

#include "stdafx.h"
class CClickLabel;
class CToolButton;

class CToolBar : public QWidget
{
   Q_OBJECT
public:
    explicit CToolBar(QWidget *parent = 0, QString userFlag = "sysuser");
    ~CToolBar();

    void     setCurUser(QString strUserFlag);
    void     readToolBarInfo(QString xmlFileName);
    void     setVersion(QString version);
    void     setLicenseOnly(bool b);

    void     setBackgroundPixmap(QPixmap pix);

    void     setCheckedButton(QString strKey);
private:
    QString  m_strCurUser;

    //logo界面元素, 两个label用来存放图标和版本号
    QWidget       *m_pwndLogo;
    CClickLabel   *m_plblLogo;
    CClickLabel   *m_plblWindowTitle;
    CClickLabel   *m_plblVersion;

    QHBoxLayout        *m_phblMain;
    QList<CToolButton*> m_listButton;
    QButtonGroup       *m_pbtnGroup;

    void     initLogoWidget();

private slots:
    void     sltBtnClicked(int nButton);
    void     sltLogoClicked();

signals:
    void     sigClicked(QString);
    void     sigLogoClicked();

};

#endif // CTOOLBAR

