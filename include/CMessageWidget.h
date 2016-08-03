#ifndef CMESSAGEWIDGET_H
#define CMESSAGEWIDGET_H

#include "stdafx.h"

class CPushButton;
enum
{
	INFO_WARNIG = 0,
	INFO_ERROR = 1,
	INFO_DIALOG = 2,
    INFO_WIDGET = 3
};

class CMessageWidget : public QDialog
{
	Q_OBJECT
public:
    CMessageWidget(QWidget *parent = NULL, int nFlag = INFO_DIALOG, bool bDefault = true);
	~CMessageWidget();

    void                 setTitleText(QString strTitle);
    QString              getTitleText();

    void                 setTitleLogo(QPixmap pix);
    const QPixmap*       getTitleLogo();

    void                 setContentWidget(QWidget *widget);
    QWidget*             getContentWidget();

    QList<QPushButton*>  getActionButtons();
    QPushButton*         getOKBtn();
    QPushButton*         getCancelBtn();

    void                 setCancelBtnVisible(bool b);
    void                 setOKBtnVisible(bool b);

    void                 setCloseBtnPixName(QString pix);
    void                 setMinBtnPixName(QString pix);
    void                 setMessageInfo(QString infoPixmap = "",QString strInfo = "");

    void                 setMessageError(QString strPixmap, QString strTitle, QStringList listError);
    void                 setMessageInfo(QString strPixmap, QString strInfo, QString strDeco);

    void                 setMessageFlag(int nFlag);

    void                 setBottomSpaceVisible(bool b);
    void                 setBorderIsRounded(bool b);

protected:
    void                showEvent(QShowEvent *e);
    void                paintEvent(QPaintEvent *event);
    void                mousePressEvent(QMouseEvent *event);
    void                mouseReleaseEvent(QMouseEvent *event);
    void                mouseMoveEvent(QMouseEvent *event);

    void                keyPressEvent(QKeyEvent *event);

    void                drawWindowShadow(QPainter &p);

private:
    QWidget     *m_pwndCenteWidget;
    QVBoxLayout *m_pvblMain;
    QLabel      *m_plblTitleBar;
    QLabel      *m_plblTitleText;
    QLabel      *m_plblTitleLogo;
    CPushButton *m_pbtnClose;
    CPushButton *m_pbtnMin;

    QScrollArea *m_pwndScrollArea;

    QWidget      *m_plblContent;
    QWidget      *m_pwndParent;

    QPushButton *m_pbtnLeft;
    QPushButton *m_pbtnRight;
    QWidget     *m_pBtnWidget;
    QLabel      *m_plblBottomSpacer;

    int         m_bIsRoundBorder;


    bool        m_bOkVisible;
    bool        m_bCancelVisible;

    QList<QPushButton*>  m_lstActionBtn;

    QPoint  m_ptMove;
    bool    m_ptPress;
    bool    m_bDefault;
    int     m_nShadowWidth;
    int     m_nRadius;

    int     m_nFlag;

    void    initTitleBar();

signals:
    void    sigOK();
    void    sigCancle();
    void    sigReturnKeyPressed();

};
#endif // CMESSAGEWIDGET_H
