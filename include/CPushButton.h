#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H

#include "stdafx.h"

class CPushButton : public QPushButton
{
    Q_OBJECT
public:
    CPushButton(QWidget *parent = 0);

    void setPixName(QString pixName);
    void setIsPressStatus(bool bPress);

protected:

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:

    //枚举按钮的几种状态
    enum ButtonStatus{NORMAL, ENTER, PRESS, NOSTATUS};
    ButtonStatus m_enuBtnStatus;
    QString    m_strPixName;

    bool m_bMousePress; //按钮左键是否按下
    bool        m_bPressStatus;
};

#endif // CPUSHBUTTON_H
