#ifndef CTOOLBUTTON_H
#define CTOOLBUTTON_H

#include "stdafx.h"

class CToolButton : public QToolButton
{
    Q_OBJECT
public:
    CToolButton(QString iconName, QWidget *parent = 0);

    void     setMousePress(bool bMousePress);
    void     setID(QString ID);
    QString  getID();
	void	 setMovieName(const QString& pixName);
protected:
    void     enterEvent(QEvent *);
    void     leaveEvent(QEvent *);
    void     mousePressEvent(QMouseEvent *event);
    void     mouseReleaseEvent(QMouseEvent *event);
    void     paintEvent(QPaintEvent *);
public:
    bool       m_bMouseHover; //鼠标是否移过
    bool       m_bMousePress; //鼠标是否按下
    QString    m_strID;

    //枚举按钮的几种状态
    enum ButtonStatus{NORMAL, ENTER, PRESS, NOSTATUS};
    ButtonStatus m_enuBtnStatus;
    QString      m_strPixName;
	QMovie		 *m_pMoviePix;	//动态图像
};

#endif // CTOOLBUTTON_H
