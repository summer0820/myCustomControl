#ifndef CCUSTOMTOOLBUTTON_H
#define CCUSTOMTOOLBUTTON_H

#include "stdafx.h"

class CCustomToolButton : public QWidget
{
    Q_OBJECT
public:
    CCustomToolButton(QWidget *parent = NULL);
    ~CCustomToolButton();

    void                setText(QString strText);
    void                setIcon(QString strIcon);
    void                setKey(QString strKey);

    void                setTextFont(QFont font);
    void                setFontColor(QString fontColor);

    void                setHasBottomLine(bool bBottom);

    QString             getKey();

protected:
    void                mousePressEvent(QMouseEvent *event);
    void                mouseReleaseEvent(QMouseEvent *event);
    void                enterEvent(QEvent *event);
    void                leaveEvent(QEvent *event);

    void                paintEvent(QPaintEvent *event);

signals:
    void                clicked();

private:
    QHBoxLayout         *m_pMainLayout;
    QLabel              *m_pIconLabel;
    QLabel              *m_pTextLabel;

    QString             m_strText;
    QString             m_strKey;
    QPoint              m_ptPos;

    bool                m_bBorderBottom;

    QString             m_strBorderBottomStyleNormal;
    QString             m_strBorderBottomStyleHover;

    QString             m_strBorderNoneStyleNormal;
    QString             m_strBorderNoneStyleHover;
};


#endif // CCUSTOMTOOLBUTTON_H
