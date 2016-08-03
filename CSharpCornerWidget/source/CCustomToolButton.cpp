
#include "../CCustomToolButton.h"


CCustomToolButton::CCustomToolButton(QWidget *parent)
    :QWidget(parent)
{
    setObjectName("CCustomToolButton");

    m_pMainLayout = new QHBoxLayout();
    m_pMainLayout->setSpacing(0);
    m_pMainLayout->setContentsMargins(20,10,0,8);

    m_pIconLabel = new QLabel(this);
    m_pIconLabel->setFixedSize(16,16);

    m_pTextLabel = new QLabel(this);

    QFont font;
    font.setPixelSize(12);
    m_pTextLabel->setFont(font);


    this->setLayout(m_pMainLayout);
    m_pMainLayout->addWidget(m_pIconLabel,0,Qt::AlignLeft);
    m_pMainLayout->addSpacing(16);
    m_pMainLayout->addWidget(m_pTextLabel,1,Qt::AlignLeft);

    m_bBorderBottom = true;

    m_strBorderBottomStyleNormal = "QWidget#CCustomToolButton{background-color:#ffffff;border-bottom:1px solid #eeeeee;}";
    m_strBorderBottomStyleHover = "QWidget#CCustomToolButton{background-color:#e6f0f9;border-bottom:1px solid #eeeeee;}";

    m_strBorderNoneStyleNormal = "QWidget#CCustomToolButton{background-color:#ffffff;border-bottom:0px solid #eeeeee;}";
    m_strBorderNoneStyleHover = "QWidget#CCustomToolButton{background-color:#e6f0f9;border-bottom:0px solid #eeeeee;}";

    setStyleSheet(m_strBorderBottomStyleNormal);
}

CCustomToolButton::~CCustomToolButton()
{

}

void CCustomToolButton::setText(QString strText)
{
    m_strText = strText;
    m_pTextLabel ->setText(strText);

}

void CCustomToolButton::setIcon(QString strIcon)
{
    QPixmap pixmap(strIcon);
    m_pIconLabel->setPixmap(pixmap);
}

void CCustomToolButton::setKey(QString strKey)
{
    m_strKey = strKey;
}

void CCustomToolButton::setTextFont(QFont font)
{
    m_pTextLabel->setFont(font);
}

void CCustomToolButton::setFontColor(QString fontColor)
{
    QString strStyle = QString("QLabel{color:%1}").arg(fontColor);
    m_pTextLabel->setStyleSheet(strStyle);
}

void CCustomToolButton::setHasBottomLine(bool bBottom)
{
    m_bBorderBottom = bBottom;

    if(m_bBorderBottom)
    {
        setStyleSheet(m_strBorderBottomStyleNormal);
    }
    else
    {
        setStyleSheet(m_strBorderNoneStyleNormal);
    }
}

QString CCustomToolButton::getKey()
{
    return m_strKey;
}

void CCustomToolButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_ptPos = event->pos();        
        qDebug()<<"==================CCustomToolButton::mousePressEvent event pos:"<<event->pos();
    }
    QWidget::mousePressEvent(event);
}

void CCustomToolButton::mouseReleaseEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {
	qDebug()<<"================CustTomToolButton::mouseReleaseEvent event pos:"<<event->pos();
        //if (event->pos() == m_ptPos)
        {            
            emit clicked();
        }
    }
    QWidget::mouseReleaseEvent(event);
}

void CCustomToolButton::enterEvent(QEvent *event)
{    
    if(m_bBorderBottom)
    {
        setStyleSheet(m_strBorderBottomStyleHover);
    }
    else
    {
        setStyleSheet(m_strBorderNoneStyleHover);
    }

    QWidget::enterEvent(event);
}

void CCustomToolButton::leaveEvent(QEvent *event)
{
    if(m_bBorderBottom)
    {
        setStyleSheet(m_strBorderBottomStyleNormal);
    }
    else
    {
        setStyleSheet(m_strBorderNoneStyleNormal);
    }
    QWidget::leaveEvent(event);
}

void CCustomToolButton::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}
