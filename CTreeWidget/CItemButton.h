#ifndef CITEMBUTTON_H
#define CITEMBUTTON_H

#include "stdafx.h"

class CItemButton : public QWidget
{
    Q_OBJECT
public:
    CItemButton(QWidget *parent = NULL);
    ~CItemButton();

    void                setText(QString strText);
    void                setNormalIcon(QString strIcon);
    void                setCheckedIcon(QString strIcon);
    void                setDirectIcon(QString strExpand, QString strCollapse);
    void                setKey(QString strKey);

    void                setTextFont(QFont font);

    QString             getKey();

    void                setIsPressed(bool bPressed);
    void                sethasbottomBorder(bool b);

    void                expand();
    void                collapse();

protected:
    void                mousePressEvent(QMouseEvent *event);
    void                mouseReleaseEvent(QMouseEvent *event);
    void                enterEvent(QEvent *event);
    void                leaveEvent(QEvent *event);

    void                paintEvent(QPaintEvent *event);

    void                updateStyle();

signals:
    void                clicked();

private:
    QHBoxLayout         *m_pMainLayout;
    QLabel              *m_pIconLabel;
    QLabel              *m_pTextLabel;
    QLabel              *m_pDirectLabel;
    QMovie              *m_pMovieExpand;
    QMovie              *m_pMovieCollapse;

    QPixmap             m_pixNormal;
    QPixmap             m_pPixChecked;
    bool                m_bBottomBorder;
    bool                m_bPress;
    bool                m_bHover;
    bool                m_bClicked;

    QString             m_strText;
    QString             m_strKey;
    QPoint              m_ptPos;
};


#endif // CCUSTOMTOOLBUTTON_H
