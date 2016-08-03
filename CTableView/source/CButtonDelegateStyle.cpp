#include "../CButtonDelegateStyle.h"
/*
*  实现软件下载按钮自定义风格的绘制
*/
CButtonDelegateStyle::CButtonDelegateStyle()
{

}

/*
*  根据风格具体要求改变调色板的面板
*  @param: QWidget* 需要改变调色的面板
*/
void CButtonDelegateStyle::polish(QWidget *widget)
{
    if (qobject_cast<QPushButton *>(widget) || qobject_cast<QComboBox *>(widget)
        || qobject_cast<QCheckBox *>(widget) )
    {
        widget->setAttribute(Qt::WA_Hover, true);
    }
}

/*
*  卸载小部件的外观。
*  呼吁每个抛光小部件样式时动态改变;前者风格unpolish其设置新风格波兰之前他们了。
*  注意,unpolish()才会叫小部件被摧毁。在某些情况下,这可能会导致问题。
*  如果您删除了一个从UI小部件,缓存,然后重新插入后的风格发生了变化;
*  Qt的一些类缓存它们的小部件。
*/
void CButtonDelegateStyle::unpolish(QWidget *widget)
{
    if (qobject_cast<QPushButton *>(widget) || qobject_cast<QComboBox *>(widget))
    {
        widget->setAttribute(Qt::WA_Hover, false);
    }
}

/*
*  返回给定像素的价值指标。
*  指定的选项和小部件可用于计算指标。
*  一般来说,小部件参数没有使用的选项可以使用qstyleoption_cast被强制转换为适当的类型()函数。
*  注意,尽管可能是零甚至PixelMetrics,可以利用它。
*/
int CButtonDelegateStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    switch (metric)
    {
    case PM_ComboBoxFrameWidth:
        return 8;
    case PM_ScrollBarExtent:
        return QMotifStyle::pixelMetric(metric, option, widget) + 4;

    case PM_CheckBoxLabelSpacing:
        return 20;

    default:
        return QMotifStyle::pixelMetric(metric, option, widget);
    }
}

/*
*	返回一个整数代表指定的风格提示给定部件提供所描述的风格的选择。
*/
int CButtonDelegateStyle::styleHint(StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    switch (hint)
    {
    case SH_DitherDisabledText:
        return int(false);
    case SH_EtchDisabledText:
        return int(true);
    default:
        return QMotifStyle::styleHint(hint, option, widget, returnData);
    }
}

/*
*  将给定的原始元素提供的画家使用指定的样式选项选项。
*  小部件参数是可选的,可以包含一个小部件,可能帮助绘制原始元素。
*/
void CButtonDelegateStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    //painter->setRenderHint(QPainter::Antialiasing);//开启边缘反锯齿

    switch (element)
    {
    case PE_PanelButtonCommand:
    {
		painter->save();
        int x, y, width, height;
        option->rect.getRect(&x, &y, &width, &height);

        QBrush brush;
        QPen drawRectPen;
        drawRectPen.setWidth(1);
        drawRectPen.setColor(QColor("#a0a0a0"));

        const QStyleOptionButton *buttonOption = qstyleoption_cast<const QStyleOptionButton *>(option);
        if (buttonOption && (buttonOption->features & QStyleOptionButton::Flat))
        {
            //按钮设置扁平化状态显示
            brush = QColor("#f2f2f2");
        }
        if(buttonOption && (buttonOption->state == QStyle::State_Enabled))
        {
            //按钮初始化时候的状态显示
            brush = QColor("#f2f2f2");
            painter->save();
            drawRectPen.setWidth(1);
            painter->setPen(drawRectPen);
            painter->setBrush(brush);
            painter->drawPath(roundRectPath(option->rect));
            painter->restore();
        }
        else
        {
            //按钮 按下或者抬起时候的状态
            painter->save();
            drawRectPen.setWidth(1);
            drawRectPen.setColor(QColor(255, 255, 255, 255));
            brush.setColor(QColor(255, 255, 255, 255));
            drawRectPen.setBrush(brush);
            painter->setPen(drawRectPen);
            painter->drawPath(roundRectPath(option->rect));
            painter->restore();
        }
		painter->restore();
    }
        break;

    case PE_IndicatorCheckBox:
        drawBronzeCheckBoxIndicator(option, painter);
        break;

    default:
        QMotifStyle::drawPrimitive(element, option, painter, widget);
    }
}

/*
* 吸引了给定的元素为画家提供了指定的样式选项的选择。
* 处理按钮在不同状态下文字绘制的颜色
*/
void CButtonDelegateStyle::drawControl(ControlElement element,const QStyleOption *option, QPainter *painter,const QWidget *widget) const
{

    switch (element)
    {
    case CE_PushButtonLabel:
    {
		painter->save();
        QStyleOptionButton myButtonOption;
        const QStyleOptionButton *buttonOption = qstyleoption_cast<const QStyleOptionButton *>(option);
        QBrush brush;

        if (buttonOption)
        {
            myButtonOption = *buttonOption;
            if (myButtonOption.palette.currentColorGroup() != QPalette::Disabled)
            {
				/*
                if (myButtonOption.state & (State_Sunken | State_On))
                {
                    //按钮按下时候 文字显示的颜色
                    brush = QColor("#368ee0");
                    myButtonOption.palette.setBrush(QPalette::ButtonText, brush);
                }
				*/
                if(myButtonOption.state == QStyle::State_Enabled)
                {
                    //按钮默认文字显示黑色
                    brush = QColor("#666666");
                    myButtonOption.palette.setBrush(QPalette::ButtonText, brush);
                }
				else
				{
					//按钮按下时候 文字显示的颜色
					brush = QColor("#368ee0");
					myButtonOption.palette.setBrush(QPalette::ButtonText, brush);
					myButtonOption.palette.setBrush(QPalette::Background, QBrush(QColor(0,0,0,0)));
				}
				/*
                else
                {
                    //按钮置灰不可使用，文字显示灰色
                    brush = QColor("#666666");
                    myButtonOption.palette.setBrush(QPalette::ButtonText, brush);
                }
				*/
            }
        }
        QMotifStyle::drawControl(element, &myButtonOption, painter, widget);
		painter->restore();
	}
        break;
    default:
        QMotifStyle::drawControl(element, option, painter, widget);
    }
}

/*
*  处理纹理
*/
void CButtonDelegateStyle::setTexture(QPalette &palette, QPalette::ColorRole role, const QPixmap &pixmap)
{

    for (int i = 0; i < QPalette::NColorGroups; ++i)
    {
        QColor color = palette.brush(QPalette::ColorGroup(i), role).color();
        palette.setBrush(QPalette::ColorGroup(i), role, QBrush(color, pixmap));
    }

}

/*
* 绘制控件的文字显示
*/
void CButtonDelegateStyle::drawItemText(QPainter *painter, const QRect &rectangle, int alignment, const QPalette &palette, bool enabled, const QString &text, QPalette::ColorRole textRole) const
{
    QTextOption textOption = Qt::AlignCenter | Qt::AlignVCenter;
    textOption.setWrapMode(QTextOption::NoWrap);
    QFont font;
    font.setWeight(12);
    font.setBold(false);
    painter->setFont(font);
    QPen pen;
    pen.setColor(palette.color(textRole));
    painter->setPen(pen);
    painter->drawText(rectangle, text, textOption);
    painter->save();
    painter->restore();
}

void CButtonDelegateStyle::setCheckedPixmap(QString pixmap)
{
    m_strCheckedPixmap = pixmap;
}

void CButtonDelegateStyle::setUncheckedPixmap(QString pixmap)
{
    m_strUncheckedPixmap = pixmap;
}

/*
*  绘制圆角控件
*/
QPainterPath CButtonDelegateStyle::roundRectPath(const QRect &rect)
{

    int radius = 3; // qMin(rect.width(), rect.height()) / 2;
    int diam = 2 * radius;

    int x1, y1, x2, y2;
    rect.getCoords(&x1, &y1, &x2, &y2);

    QPainterPath path;
    path.moveTo(x2, y1 + radius);
    path.arcTo(QRect(x2 - diam, y1, diam, diam), 0.0, +90.0);
    path.lineTo(x1 + radius, y1);
    path.arcTo(QRect(x1, y1, diam, diam), 90.0, +90.0);
    path.lineTo(x1, y2 - radius);
    path.arcTo(QRect(x1, y2 - diam, diam, diam), 180.0, +90.0);
    path.lineTo(x1 + radius, y2);
    path.arcTo(QRect(x2 - diam, y2 - diam, diam, diam), 270.0, +90.0);
    path.closeSubpath();
    return path;
}

void CButtonDelegateStyle::drawBronzeCheckBoxIndicator(const QStyleOption *option, QPainter *painter) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing,true);

	QPixmap pixmap;
	if(option->state == State_Off)
	{
        if(m_strUncheckedPixmap.isEmpty())
        {
            pixmap.load(":/tip/icon/other/ID_CHECKBOX_UNCHECKED.png");
        }
        else
        {
            pixmap.load(m_strUncheckedPixmap);
        }
	}
	else if(option->state == State_On)
	{
        if(m_strCheckedPixmap.isEmpty())
        {
            pixmap.load(":/tip/icon/other/ID_CHECKBOX_CHECKED.png");
        }
        else
        {
            pixmap.load(m_strCheckedPixmap);
        }
	}
	painter->drawPixmap(option->rect, pixmap);
    painter->restore();
}

