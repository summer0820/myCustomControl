#ifndef CSHADOWWIDGET_H
#define CSHADOWWIDGET_H

#include "stdafx.h"

/**
* 窗口可以拖动
* 窗口增加阴影效果
* @brief The BFWidget class
*/
class CShadowWidget : public QDialog
{
    Q_OBJECT
public:
    explicit CShadowWidget(QWidget *parent = 0, QPixmap pixShadow = QPixmap(""));

    void    setBackgroundColor(QColor bgColor);
    void    setContentMargin(int nLeft,int nTop,int nRight,int nBottom);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    //显示内容的区域
    QPixmap m_pixShadow;
    //阴影图片
    QPoint  m_ptMove;
    //移动的距离
    bool    m_ptPress; //按下鼠标左键
    QColor  m_backgrouncolor;
    int     m_nLeft;
    int     m_nTop;
    int     m_nRight;
    int     m_nBottom;
};

#endif // MAINWINDOW_H
