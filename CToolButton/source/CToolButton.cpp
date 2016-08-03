#include "../../include/CToolButton.h"

CToolButton::CToolButton(QString iconName, QWidget *parent)
    :QToolButton(parent)
{
    //设置大小
    //setFixedSize(pixmap.width()+30, pixmap.height()+30);
    setAutoRaise(true);
    //设置不获取焦点，即用tab键选中不了，就不会出现虚线框
    setFocusPolicy(Qt::NoFocus);

    m_bMouseHover = false;
    m_bMousePress = false;
    m_enuBtnStatus = NORMAL;
    m_strPixName = iconName;
    m_strID = "0";
	m_pMoviePix = 0;
    setFixedSize(QPixmap(m_strPixName).size());
}

void CToolButton::setMovieName(const QString& pixName)
{
	if (!m_pMoviePix)
	{
		m_pMoviePix = new QMovie;
		connect(m_pMoviePix, SIGNAL(frameChanged(int)),this, SLOT(update()));
	}

    m_pMoviePix->setFileName(pixName);
}


void CToolButton::enterEvent(QEvent *event)
{
    m_enuBtnStatus = ENTER;
	if(m_pMoviePix) m_pMoviePix->start();
    update();
    QToolButton::enterEvent(event);
}

void CToolButton::mousePressEvent(QMouseEvent *event)
{
    //若点击鼠标左键
    if(event->button() == Qt::LeftButton)
    {
        m_bMousePress = true;
        m_enuBtnStatus = PRESS;
        update();
    }
    QToolButton::mousePressEvent(event);
}

void CToolButton::mouseReleaseEvent(QMouseEvent *event)
{
    //若点击鼠标左键
    if(m_bMousePress  && this->rect().contains(event->pos()))
    {
        m_bMousePress = false;
        m_enuBtnStatus = PRESS;
        update();
        //emit clicked();
    }
    QToolButton::mouseReleaseEvent(event);
}

void CToolButton::leaveEvent(QEvent *event)
{
    m_enuBtnStatus = NORMAL;
	if(m_pMoviePix) m_pMoviePix->stop();
    update();
    QToolButton::leaveEvent(event);
}

void CToolButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pixmap;
    if(isChecked() == true)
    {
        pixmap.load(m_strPixName + QString("_pressed"));
    }
    else
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
                if (m_pMoviePix)
                {
                    pixmap = m_pMoviePix->currentPixmap();
                }
                else
                {
                    pixmap.load(m_strPixName + QString("_hover"));
                }
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
            {
                pixmap.load(m_strPixName);
                break;
            }
        }
    }

    painter.drawPixmap(rect(), pixmap);
    //QToolButton::paintEvent(event);
}

void CToolButton::setMousePress(bool bMousePress)
{
    m_bMousePress = bMousePress;
}

/*
* 设置按钮的ID,唯一标识
* @param: QString
*/
void CToolButton::setID(QString ID)
{
    m_strID = ID;
}

/*
*   获取按钮的ID
* @return: QString
*/
QString CToolButton::getID()
{
    return m_strID;
}
