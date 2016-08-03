#include "../../include/CDropShadowWidget.h"

CDropShadowWidget::CDropShadowWidget(QWidget *parent)
    : QWidget(parent)
{
    m_bMousePress = false;
    //setWindowFlags(Qt::FramelessWindowHint);
    //setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
#if 1
    //setAttribute(Qt::WA_TranslucentBackground);
#else
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255, 120)));
    setPalette(palette);
#endif

#if defined  Q_OS_LINUX
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint
                         |Qt::WindowSystemMenuHint
                         |Qt::WindowMinimizeButtonHint
                         |Qt::WindowMaximizeButtonHint);
#else
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
#endif
}

void CDropShadowWidget::mousePressEvent(QMouseEvent *e)
{
    //只能是鼠标左键移动和改变大小
    if(e->button() == Qt::LeftButton)
    {
        m_bMousePress = true;
    }

    //窗口移动距离
    m_ptMove = e->globalPos() - pos();
    QWidget::mousePressEvent(e);
}

void CDropShadowWidget::mouseReleaseEvent(QMouseEvent *e)
{
    m_bMousePress = false;
    QWidget::mouseReleaseEvent(e);
}

void CDropShadowWidget::mouseMoveEvent(QMouseEvent *e)
{
    //移动窗口
    if(m_bMousePress)
    {
        QPoint ptMove = e->globalPos();
        move(ptMove - m_ptMove);
    }
    QWidget::mouseMoveEvent(e);
}


