#ifndef CHEADERVIEW
#define CHEADERVIEW
#include "../include/stdafx.h"

class CButtonDelegateStyle;
class CHeaderView : public QHeaderView
{
    Q_OBJECT

public:
    CHeaderView(Qt::Orientation orientation, QWidget * parent = 0);
    virtual ~CHeaderView(){}

    void   setCheckable(bool b, int nIndex = 0);
    void   setChecked(bool b);

    void   setBoderImage(QString str);
    void   setSortUpIcon(Qt::Orientation orientation, QString pixmap);
    void   setSortDownIcon(Qt::Orientation orientation, QString pixmap);
    void   setCheckedPixmap(QString pixmap);
    void   setUnCheckedPixmap(QString pixmap);

protected:
    void    paintSection( QPainter *painter, const QRect &rect, int logicalIndex ) const; //绘制checkbox

    void    mousePressEvent(QMouseEvent *event);      //鼠标click事件
    void    mouseMoveEvent(QMouseEvent *event);
    void    enterEvent(QEvent *event);
    void    leaveEvent(QEvent *event);
    void    paintEvent( QPaintEvent* e );              //绘制checkbox事件

signals:
    void sigCheckStateChanged(Qt::CheckState state);

private:
    int  m_nPosX;                   //横坐标
    int  m_nPosY;                   //纵坐标
    int  m_nHoverIndex;

    int         m_nStyle;                  //记录QStyle
    QString     m_strText;
    CButtonDelegateStyle  *m_pbtnDelegateStyle;

    bool                  m_bChecked;
    bool                  m_bSort;
    int                   m_nCheckedIndex;
    QPixmap               m_pixSort;

    QString               m_strAscendingOrder;
    QString               m_strDescendingOrder;
    QString               m_strBorderPixmap;


    void                  drawCheckableItem(QPainter *painter, const QRect &rect, QString displayText) const;
    void                  drawPixmap(QPainter *painter, const QRect &rect, QPixmap pixmap) const;
    void                  drawDisplayText(QPainter *painter, const QRect &rect, QString displayText) const;
    void                  drawHoverRect(QPainter *painter, const QRect &rect) const;

private slots:
    void                  sltSectionPressed(int logicalIndex);
};

#endif // CHEADERVIEW

