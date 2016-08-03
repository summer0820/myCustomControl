#include "CBusyIndicatorWidget.h"
#include <QPainter>

CBusyIndicator::CBusyIndicator(QWidget* parent)
        : QWidget(parent),
        m_nAngle(0),
        m_nTimerId(-1),
        m_nDelay(40),
        m_bDisplayedWhenStopped(false),
        m_color(Qt::white)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFocusPolicy(Qt::NoFocus);
}

bool CBusyIndicator::isAnimated () const
{
    return (m_nTimerId != -1);
}

void CBusyIndicator::setDisplayedWhenStopped(bool state)
{
    m_bDisplayedWhenStopped = state;

    update();
}

bool CBusyIndicator::isDisplayedWhenStopped() const
{
    return m_bDisplayedWhenStopped;
}

void CBusyIndicator::startAnimation()
{
    m_nAngle = 0;

    if (m_nTimerId == -1)
        m_nTimerId = startTimer(m_nDelay);
}

void CBusyIndicator::stopAnimation()
{
    if (m_nTimerId != -1)
        killTimer(m_nTimerId);

    m_nTimerId = -1;

    update();
}

void CBusyIndicator::setAnimationDelay(int delay)
{
    if (m_nTimerId != -1)
        killTimer(m_nTimerId);

    m_nDelay = delay;

    if (m_nTimerId != -1)
        m_nTimerId = startTimer(m_nDelay);
}

void CBusyIndicator::setColor(const QColor & color)
{
    m_color = color;

    update();
}

QSize CBusyIndicator::sizeHint() const
{
    return QSize(24,24);
}

int CBusyIndicator::heightForWidth(int w) const
{
    return w;
}

void CBusyIndicator::timerEvent(QTimerEvent * /*event*/)
{
    m_nAngle = (m_nAngle+30)%360;

    update();
}

void CBusyIndicator::paintEvent(QPaintEvent * /*event*/)
{
    if (!m_bDisplayedWhenStopped && !isAnimated())
        return;

    int width = qMin(this->width(), this->height());

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    int outerRadius = (width-1)*0.5;
    int innerRadius = (width-1)*0.5*0.38;

    int capsuleHeight = outerRadius - innerRadius;
    int capsuleWidth  = (width > 32 ) ? capsuleHeight *.23 : capsuleHeight *.35;
    int capsuleRadius = capsuleWidth/2;

    for (int i=0; i<12; i++)
    {
        QColor color = m_color;
        color.setAlphaF(1.0f - (i/12.0f));
        p.setPen(Qt::NoPen);
        p.setBrush(color);
        p.save();
        p.translate(rect().center());
        p.rotate(m_nAngle - i*30.0f);
        p.drawRoundedRect(-capsuleWidth*0.5, -(innerRadius+capsuleHeight), capsuleWidth, capsuleHeight, capsuleRadius, capsuleRadius);
        p.restore();
    }
}


CBusyIndicatorWidget::CBusyIndicatorWidget(QWidget *parent)
    :QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    m_pBusyIndicator = new CBusyIndicator();

    QFrame* frame = new QFrame;
    frame->setStyleSheet("background-color: rgba(0, 0, 0, 150)");

    QVBoxLayout* vbl = new QVBoxLayout;
    vbl->setContentsMargins(0, 0, 0, 0);

    m_plblBusyInfo = new QLabel;
    m_plblBusyInfo->setStyleSheet("background-color:rgba(0, 0, 0, 0);"
                                  "color:white;");
    m_plblBusyInfo->setText(QString::fromLocal8Bit("请稍后..."));
    QFont font;
    font.setWeight(24);

    QHBoxLayout* hbl = new QHBoxLayout(frame);
    hbl->setContentsMargins(0, 0, 0, 0);
    hbl->setAlignment(Qt::AlignCenter);
    hbl->addWidget(m_pBusyIndicator);
    hbl->addWidget(m_plblBusyInfo);

    vbl->addWidget(frame);
    this->setLayout(vbl);
}

CBusyIndicatorWidget::~CBusyIndicatorWidget()
{

}

void CBusyIndicatorWidget::showBusyIndicatorWidget(int x, int y, int with, int height)
{
    this->setGeometry(x, y, with, height);
    m_pBusyIndicator->startAnimation();
    this->show();
}

void CBusyIndicatorWidget::showBusyIndicatorWidget(QRect rect)
{
    this->setGeometry(rect);
    m_pBusyIndicator->startAnimation();
    this->show();
}

void CBusyIndicatorWidget::closeBusyIndicatorWidget()
{
    m_pBusyIndicator->stopAnimation();
    this->close();
}

void CBusyIndicatorWidget::setBusyInfo(QString strText)
{
    m_plblBusyInfo->setText(strText);
}
