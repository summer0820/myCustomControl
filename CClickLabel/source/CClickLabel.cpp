// **************************************************************************
// httc share library for Qt (C++)
// 共享源码库
// 文档说明：可发出clicked信号的Label部件
// ==========================================================================
/// @file tcclicklabel.cpp 可发出clicked信号的Label部件
// ==========================================================================
#include "../../include/CClickLabel.h"

class CClickLabelPrivate
{
    Q_DECLARE_PUBLIC(CClickLabel)
public:
    explicit CClickLabelPrivate(CClickLabel *qptr);
    ~CClickLabelPrivate();
    QPoint pos;
    CClickLabel* const q_ptr;
};

CClickLabelPrivate::CClickLabelPrivate(CClickLabel *qptr)
    : q_ptr(qptr)
{

}

CClickLabelPrivate::~CClickLabelPrivate()
{
}

CClickLabel::CClickLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f),
      d_ptr(new CClickLabelPrivate(this))
{
    m_bTextClicked = false;
}

CClickLabel::CClickLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel(text, parent, f), d_ptr(new CClickLabelPrivate(this))
{
    m_bTextClicked = false;
}

CClickLabel::~CClickLabel()
{
    delete d_ptr;
}

void CClickLabel::mousePressEvent(QMouseEvent *e)
{
    QLabel::mousePressEvent(e);

    Q_D(CClickLabel);
    if (e->button() == Qt::LeftButton)
    {
        d->pos = e->pos();
    }

    if(e->pos().x() <= this->fontMetrics().width(this->text()))
    {
        m_bTextClicked = true;
    }
}

void CClickLabel::mouseReleaseEvent(QMouseEvent *e)
{
    QLabel::mouseReleaseEvent(e);

    Q_D(CClickLabel);
    if (e->button() == Qt::LeftButton)
    {
        if (e->pos() == d->pos)
        {
            Q_EMIT clicked();
        }
    }
    if(m_bTextClicked == true)
    {
        Q_EMIT sigTextClicked();
        m_bTextClicked = false;
    }
}
