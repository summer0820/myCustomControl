#ifndef BUTTONDELEGATESTYLE_H
#define BUTTONDELEGATESTYLE_H

#include <QMotifStyle>
#include <QPalette>
#include <QtGui>

QT_BEGIN_NAMESPACE
class QPainterPath;
QT_END_NAMESPACE

class CButtonDelegateStyle : public QMotifStyle
{
    Q_OBJECT

public:
    CButtonDelegateStyle();

    void        polish(QWidget *widget);
    void        unpolish(QWidget *widget);
    int         pixelMetric(PixelMetric metric, const QStyleOption *option,const QWidget *widget) const;
    int         styleHint(StyleHint hint, const QStyleOption *option,const QWidget *widget, QStyleHintReturn *returnData) const;
    void        drawPrimitive(PrimitiveElement element, const QStyleOption *option,QPainter *painter, const QWidget *widget) const;
    void        drawControl(ControlElement control, const QStyleOption *option,QPainter *painter, const QWidget *widget) const;
    void        drawItemText(QPainter * painter, const QRect & rectangle, int alignment, const QPalette & palette, bool enabled, const QString & text, QPalette::ColorRole textRole = QPalette::NoRole) const;

    void        setCheckedPixmap(QString pixmap);
    void        setUncheckedPixmap(QString pixmap);

private:
    static void         setTexture(QPalette &palette, QPalette::ColorRole role,const QPixmap &pixmap);
    static QPainterPath roundRectPath(const QRect &rect);

    void                drawBronzeCheckBoxIndicator(const QStyleOption *option, QPainter *painter) const;

    QString             m_strCheckedPixmap;
    QString             m_strUncheckedPixmap;
};
#endif // BUTTONDELEGATESTYLE_H
