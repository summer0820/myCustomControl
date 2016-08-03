#include "../../include/CPushButton.h"

CPushButton::CPushButton(QWidget *parent)
    :QPushButton(parent)
{
    m_enuBtnStatus = NORMAL;
    m_bMousePress = false;
    m_bPressStatus = false;
}

void CPushButton::setPixName(QString pixName)
{
    m_strPixName = pixName;
    setFixedSize(QPixmap(pixName).size());
}

void CPushButton::setIsPressStatus(bool bPress)
{
    m_bPressStatus = bPress;
    if(m_bPressStatus)
    {
        m_enuBtnStatus = PRESS;
    }
    else
    {
        m_enuBtnStatus = NORMAL;
    }
    update();
}

void CPushButton::enterEvent(QEvent *)
{
    if(m_bPressStatus)
    {
        m_enuBtnStatus = PRESS;
    }
    else
    {
        m_enuBtnStatus = ENTER;
    }
    update();
}

void CPushButton::mousePressEvent(QMouseEvent *event)
{
    //若点击鼠标左键
    if(event->button() == Qt::LeftButton)
    {
        m_bMousePress = true;
        m_enuBtnStatus = PRESS;
        update();
    }
}

void CPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    //若点击鼠标左键
    if(m_bMousePress)
    {
        m_bMousePress = false;
        if(m_bPressStatus)
        {
            m_enuBtnStatus = PRESS;
        }
        else
        {
            m_enuBtnStatus = ENTER;
        }
        update();
        emit clicked();
    }
}

void CPushButton::leaveEvent(QEvent *)
{
    if(m_bPressStatus)
    {
        m_enuBtnStatus = PRESS;
    }
    else
    {
        m_enuBtnStatus = NORMAL;
    }
    update();
}

void CPushButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap;

    if(isEnabled())
    {
        switch(m_enuBtnStatus)
        {
        case NORMAL:
            {
                pixmap.load(m_strPixName);
                break;
            }
        case ENTER:
            {
                pixmap.load(m_strPixName + QString("_hover"));
                break;
            }
        case PRESS:
            {
                pixmap.load(m_strPixName + QString("_pressed"));
                break;
            }
        case NOSTATUS:
            {
                pixmap.load(m_strPixName);
                break;
            }
        default:
            pixmap.load(m_strPixName);
        }
    }
    else
    {
        if(pixmap.load(m_strPixName + QString("_disabled")) == false)
        {
            pixmap.load(m_strPixName);
        }
    }
    painter.drawPixmap(rect(), pixmap);
}

