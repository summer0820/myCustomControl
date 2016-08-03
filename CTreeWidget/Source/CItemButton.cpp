
#include "../CItemButton.h"


CItemButton::CItemButton(QWidget *parent)
    :QWidget(parent)
{
    m_pMainLayout = new QHBoxLayout();
    m_pMainLayout->setSpacing(0);
    m_pMainLayout->setContentsMargins(13,7,14,0);
    m_pMainLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    m_pIconLabel = new QLabel(this);
    m_pIconLabel->setFixedSize(16,16);
    m_pIconLabel->setAttribute(Qt::WA_TranslucentBackground,true);

    m_pTextLabel = new QLabel(this);
    m_pTextLabel->setAttribute(Qt::WA_TranslucentBackground,true);

    m_pDirectLabel = new QLabel(this);
    m_pDirectLabel->setAttribute(Qt::WA_TranslucentBackground,true);

    m_pMovieExpand = new QMovie();
    m_pMovieCollapse = new QMovie();

    this->setLayout(m_pMainLayout);
    m_pMainLayout->addWidget(m_pIconLabel,0,Qt::AlignLeft);
    m_pMainLayout->addSpacing(10);
    m_pMainLayout->addWidget(m_pTextLabel,1,Qt::AlignLeft);
    m_pMainLayout->addWidget(m_pDirectLabel,0,Qt::AlignRight);

    m_bPress = false;
    m_bBottomBorder = true;
    m_bHover = false;
    m_bClicked = false;

    setObjectName("CItemButton");
    updateStyle();

    this->setFixedSize(149,36);
}

CItemButton::~CItemButton()
{

}

void CItemButton::setText(QString strText)
{
    m_strText = strText;
    m_pTextLabel ->setText(strText);

}

void CItemButton::setNormalIcon(QString strIcon)
{
    m_pixNormal = QPixmap(strIcon);
    m_pIconLabel->setPixmap(m_pixNormal);
}

void CItemButton::setCheckedIcon(QString strIcon)
{
    m_pPixChecked = QPixmap(strIcon);
}

void CItemButton::setDirectIcon(QString strExpand,QString strCollapse)
{
    m_pMovieExpand->setFileName(strExpand);
    m_pMovieCollapse->setFileName(strCollapse);

    m_pDirectLabel->setMovie(m_pMovieExpand);
    m_pMovieExpand->start();
}

void CItemButton::setKey(QString strKey)
{
    m_strKey = strKey;
}

void CItemButton::setTextFont(QFont font)
{
    m_pTextLabel->setFont(font);
}

QString CItemButton::getKey()
{
    return m_strKey;
}

void CItemButton::setIsPressed(bool bPressed)
{
    m_bPress = bPressed;
    updateStyle();

}

void CItemButton::sethasbottomBorder(bool b)
{
    m_bBottomBorder = b;
    updateStyle();
}

void CItemButton::expand()
{
    m_pDirectLabel->setMovie(m_pMovieExpand);
    m_pMovieExpand->start();
}

void CItemButton::collapse()
{
    m_pDirectLabel->setMovie(m_pMovieCollapse);
    m_pMovieCollapse->start();
}

void CItemButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_ptPos = event->pos();        
        m_bClicked = true;
        updateStyle();
    }
    QWidget::mousePressEvent(event);
}

void CItemButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bClicked = false;
        updateStyle();
        if (event->pos() == m_ptPos)
        {
            emit clicked();
        }
    }
    QWidget::mouseReleaseEvent(event);
}

void CItemButton::enterEvent(QEvent *event)
{
    m_bHover = true;
    updateStyle();
    QWidget::enterEvent(event);
}

void CItemButton::leaveEvent(QEvent *event)
{
    m_bHover = false;
    updateStyle();
    QWidget::leaveEvent(event);
}

void CItemButton::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void CItemButton::updateStyle()
{
    if(m_bPress)
    {
        if(m_bBottomBorder)
        {
            setStyleSheet("QWidget#CItemButton{background-color:#368ee0;border-bottom: 1px solid #d7e6eb;}");
        }
        else
        {
            setStyleSheet("QWidget#CItemButton{background-color:#368ee0;border-bottom: 0px solid #d7e6eb;}");
        }
        m_pIconLabel->setPixmap(m_pPixChecked);
        m_pTextLabel->setStyleSheet("QLabel{color:#ffffff}");
    }
    else
    {
        if(m_bBottomBorder)
        {
            setStyleSheet("QWidget#CItemButton{background-color:#f6fafd;border-bottom: 1px solid #d7e6eb;}");
        }
        else
        {
            setStyleSheet("QWidget#CItemButton{background-color:#f6fafd;border-bottom: 0px solid #d7e6eb;}");
        }
        m_pIconLabel->setPixmap(m_pixNormal);
        if(m_bHover)
        {
            m_pTextLabel->setStyleSheet("QLabel{color:#368ee0}");
        }
        else
        {
            if(m_bClicked)
            {
                m_pTextLabel->setStyleSheet("QLabel{color:#368eff}");
            }
            else
            {
                m_pTextLabel->setStyleSheet("QLabel{color:#333333}");
            }
        }
    }
}
