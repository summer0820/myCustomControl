#ifndef CDROPSHADOWWIDGET
#define CDROPSHADOWWIDGET

#include "stdafx.h"

class CDropShadowWidget : public QWidget
{
    Q_OBJECT

public:
    CDropShadowWidget(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private:
    QPoint m_ptMove;
    bool   m_bMousePress;
};
#endif // CDROPSHADOWWIDGET

