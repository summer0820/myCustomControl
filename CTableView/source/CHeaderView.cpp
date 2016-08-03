#include "../CHeaderView.h"
#include "../CButtonDelegateStyle.h"
CHeaderView::CHeaderView( Qt::Orientation orientation, QWidget * parent )
    : QHeaderView(orientation, parent),
    m_nPosX(0),
    m_nPosY(3),
    m_nStyle(QStyle::State_Off)
{
    m_bChecked = false;
    m_bSort = true;
    m_nHoverIndex = -1;
    m_nCheckedIndex = -1;
    //m_strAscendingOrder = QString(":/tip/icon/other/ID_ARROW_UP.png");
    //m_strDescendingOrder = QString(":/tip/icon/other/ID_ARROW_DOWN.png");
    //m_strBorderPixmap = QString(":/tip/icon/other/ID_HEADERVIEW_RIGHT_BORDER.png");
    m_pbtnDelegateStyle = new CButtonDelegateStyle();
    this->setStyleSheet("QHeaderView::section{background-color:#f9f9f9;"
                        "color:rgba(0, 0, 0, 0);"
                        "border:0px solid #6c6c6c;"
                        "padding-left: 17px;"
                        "padding-right:5px;"
                        "height:36px;"
                        "font-size: 12px;"
                        "font-family: Microsoft YaHei;"
                        "font:bold;}"
                        "QHeaderView::down-arrow {"
                        "image:none;}"
                        "QHeaderView::up-arrow {"
                        "image:none;}");

    Qt::SortOrder nSort = sortIndicatorOrder();
    if(nSort == Qt::AscendingOrder)
    {
        nSort = Qt::DescendingOrder;
        m_pixSort = QPixmap(m_strDescendingOrder);
    }
    else
    {
        nSort = Qt::AscendingOrder;
        m_pixSort = QPixmap(m_strAscendingOrder);
    }
    QFont font("Microsoft YaHei");
    font.setPixelSize(12);
    font.setBold(true);
    setFont(font);
    connect(this, SIGNAL(sectionEntered(int)), this, SLOT(sltSectionPressed(int)));
}

void CHeaderView::setCheckable(bool b, int nIndex)
{
    m_bChecked = b;
    m_nCheckedIndex = nIndex;
}

void CHeaderView::setChecked(bool b)
{
    if(b == false)
    {
        m_nStyle = QStyle::State_Off;
    }
    else
    {
        m_nStyle = QStyle::State_On;
    }
}

void CHeaderView::setBoderImage(QString str)
{
    m_strBorderPixmap = str;
}

void CHeaderView::setSortUpIcon(Qt::Orientation orientation, QString pixmap)
{
    if(orientation == Qt::Horizontal)
    {
        m_strAscendingOrder = pixmap;
    }
}

void CHeaderView::setSortDownIcon(Qt::Orientation orientation, QString pixmap)
{
    if(orientation == Qt::Horizontal)
    {
        m_strDescendingOrder = pixmap;
    }
}

void CHeaderView::setCheckedPixmap(QString pixmap)
{
    if(m_pbtnDelegateStyle != NULL)
    {
        m_pbtnDelegateStyle->setCheckedPixmap(pixmap);
    }
}

void CHeaderView::setUnCheckedPixmap(QString pixmap)
{
    if(m_pbtnDelegateStyle != NULL)
    {
        m_pbtnDelegateStyle->setUncheckedPixmap(pixmap);
    }
}

//根据表头鼠标事件控制checkbox的状态，此事件在绘制之前触发
void CHeaderView::paintEvent( QPaintEvent* event )
{
    QHeaderView::paintEvent( event );
}

//重载paintSection，此函数为const控制，函数内不允许对函数外部变量的修改

//绘制QStyleOptionButton的样式，这里选取*20大小

QStyleOption RectOption;
void CHeaderView::paintSection( QPainter *painter, const QRect &rect, int logicalIndex ) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();

    QVariant displayText = model()->headerData(logicalIndex, Qt::Horizontal, Qt::DisplayRole);
    QFontMetrics fontMerics = this->fontMetrics();
    int nWidget = fontMerics.width(displayText.toString());
    QRect rectPixmap = QRect(0, 0, 0, 0);
    QRect rectText = QRect(0, 0, 0, 0);

    if(m_nHoverIndex == logicalIndex)
    {
        drawHoverRect(painter, rect);
    }
    if(m_bChecked == true && m_nCheckedIndex == logicalIndex)
    {
        RectOption.rect = QRect(rect.x() + 10, rect.center().y() - 6, 12, 12);
        rectText = QRect(RectOption.rect.x() + RectOption.rect.width() + 20, rect.y(), nWidget, rect.height());
        rectPixmap = QRect(rectText.x() + rectText.width() + 10, rectText.center().y() - 2, 7, 4);

        drawCheckableItem(painter, rectText, displayText.toString());
        drawDisplayText(painter,rectText,displayText.toString());

    }
    else
    {
        rectText = QRect(rect.x() + 10, rect.y(), nWidget, rect.height());
        rectPixmap = QRect(rectText.x() + rectText.width() + 10, rectText.center().y() - 2, 7, 4);
        drawDisplayText(painter, rectText, displayText.toString());
    }
    if(this->sortIndicatorSection() == logicalIndex)
    {
        //draw sort pixmap
        drawPixmap(painter, rectPixmap, m_pixSort);
    }
    if(rect.x() + rect.width() != this->rect().width())
    {
        QRect rectBorderImage = QRect(rect.x() + rect.width() - 1, rect.y(), 1, rect.height());
        drawPixmap(painter, rectBorderImage, QPixmap(m_strBorderPixmap));
    }
}

//鼠标按下事件，为了屏蔽鼠标在第一列之外的事件，用visualIndexAt判断坐标是否在第一列范围之内
void CHeaderView::mousePressEvent(QMouseEvent *event)
{
    m_bSort = true;
    m_nPosX = event->pos().x();
    m_nPosY = event->pos().y();
    int nCurrentIndex = visualIndexAt( m_nPosX );
    if(m_bChecked == true && m_nCheckedIndex == nCurrentIndex)
    {
        if(RectOption.rect.contains( event->pos()))
        {
            if( m_nStyle == QStyle::State_Off )
            {
                m_nStyle = QStyle::State_On;
                emit sigCheckStateChanged(Qt::Checked);
            }
            else
            {
                m_nStyle = QStyle::State_Off;
                emit sigCheckStateChanged(Qt::Unchecked);
            }
            m_bSort = false;
        }
    }

    int curSectionWidth = 0;
    for(int i = 0; i <= nCurrentIndex; i++)
    {
        curSectionWidth  = curSectionWidth + sectionSize(i);
    }
    QRect rectSort = QRect(this->rect().x() + curSectionWidth - 18, rect().y(), 18, rect().height());
    QRect rectCheck = QRect(rect().x() + curSectionWidth - sectionSize(nCurrentIndex), this->rect().y(), 18, this->rect().height());
    if(m_bSort == true)
    {
        if(rectSort.contains(event->pos()) == true)
        {
            update();
            QHeaderView::mousePressEvent(event);
            return;
        }
        if(rectCheck.contains(event->pos()) == true)
        {
            update();
            QHeaderView::mousePressEvent(event);
            return;
        }
        Qt::SortOrder nSort = sortIndicatorOrder();
        if(nSort == Qt::AscendingOrder)
        {
            nSort = Qt::DescendingOrder;
            m_pixSort = QPixmap(m_strDescendingOrder);
        }
        else
        {
            nSort = Qt::AscendingOrder;
            m_pixSort = QPixmap(m_strAscendingOrder);
        }
        setSortIndicator(nCurrentIndex, nSort);
    }
    update();
    QHeaderView::mousePressEvent(event);
}

void CHeaderView::mouseMoveEvent(QMouseEvent *event)
{
    int nIndex = visualIndexAt(event->pos().x());
    m_nHoverIndex = nIndex;
    update();
    QHeaderView::mouseMoveEvent(event);
}

void CHeaderView::enterEvent(QEvent *event)
{
    QPoint pt = mapFromGlobal( this->cursor().pos() );
    int nIndex = visualIndexAt(pt.x());
    m_nHoverIndex = nIndex;
    update();
    QHeaderView::enterEvent(event);
}

void CHeaderView::leaveEvent(QEvent *event)
{
    m_nHoverIndex = -1;
    update();
    QHeaderView::leaveEvent(event);
}

void CHeaderView::drawCheckableItem(QPainter *painter, const QRect &rect, QString displayText) const
{
    if ( 0x00000020 == m_nStyle )
    {
        RectOption.state = QStyle::State_On;
    }
    else if( 0x00000008 == m_nStyle )
    {
        RectOption.state = QStyle::State_Off;
    }
    m_pbtnDelegateStyle->drawPrimitive(QStyle::PE_IndicatorCheckBox, &RectOption, painter, NULL);
}

void CHeaderView::drawPixmap(QPainter *painter, const QRect &rect, QPixmap pixmap) const
{
    painter->save();
    painter->drawPixmap(rect, pixmap);
    painter->restore();
}

void CHeaderView::drawDisplayText(QPainter *painter, const QRect &rect, QString displayText) const
{
    painter->save();
    QPen penText;
    penText.setBrush(QColor("#797979"));
    painter->setPen(penText);
    painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, displayText);
    painter->restore();
}

void CHeaderView::drawHoverRect(QPainter *painter, const QRect &rect) const
{
    painter->save();
    QPen pen;
    pen.setWidth(2);
    pen.setColor("#dddddd");
    painter->setPen(pen);
    painter->setBrush(QBrush("#eeeeee"));
    painter->drawRect(QRectF(rect.x() - 1,rect.y(), rect.width() - 1, rect.height()));
    painter->restore();
}

void CHeaderView::sltSectionPressed(int logicalIndex)
{
    qDebug("===========sltSectionPressed");
    m_bSort = false;
}
