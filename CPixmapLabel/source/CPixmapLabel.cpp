#include "CPixmapLabel.h"
CPixmapLabel::CPixmapLabel(QWidget *parent, QString text)
    :QWidget(parent)
    ,m_strText(text)
{
    initUI();
}

CPixmapLabel::CPixmapLabel(QWidget *parent, QPixmap pixmap, QString str)
    :QWidget(parent)
    ,m_pixLeft(pixmap)
    ,m_strText(str)
{
    initUI();
}

CPixmapLabel::~CPixmapLabel()
{

}

void CPixmapLabel::setMarginsValue(int left, int top, int right, int bottom)
{
    m_phblMain->setContentsMargins(left, top, right, bottom);
}

void CPixmapLabel::setSpacing(int space)
{
    m_phblMain->setSpacing(space);
}

int CPixmapLabel::getSpacing()
{
    return m_phblMain->spacing();
}

void CPixmapLabel::setLeftPixmap(QPixmap pix)
{
    m_plblPixmap->setPixmap(pix);
    m_plblPixmap->adjustSize();
}

const QPixmap* CPixmapLabel::getLfetPixmap()
{
    return m_plblPixmap->pixmap();
}

void CPixmapLabel::setShowText(QString str)
{
    m_plblText->setText(str);
    //m_plblText->adjustSize();
    //this->setFixedWidth(m_plblText->width() + m_plblPixmap->width());
}

QString CPixmapLabel::getShowText()
{
    return m_plblText->text();
}

void CPixmapLabel::initUI()
{
    setContentsMargins(0, 0, 0, 0);

    m_phblMain = new QHBoxLayout();
    m_phblMain->setContentsMargins(0, 0, 0, 0);
    m_phblMain->setSpacing(5);
    //m_phblMain->setAlignment(Qt::AlignLeft);

    m_plblPixmap = new QLabel(this);
    m_plblPixmap->setContentsMargins(0, 0, 0, 0);
    m_plblPixmap->setPixmap(m_pixLeft);
    m_plblPixmap->setFixedSize(m_plblPixmap->pixmap()->size());

    m_plblText = new QLabel(this);
    m_plblText->setText(m_strText);
    m_plblText->setContentsMargins(0, 0, 0, 0);
    m_plblText->adjustSize();

    m_phblMain->addWidget(m_plblPixmap);
    m_phblMain->addWidget(m_plblText);

    //QFontMetrics fm(m_plblText->font());
    //qDebug() << fm.width(m_plblText->text());
    //qDebug()<< "====text width"<<m_plblText->width();
    setLayout(m_phblMain);
}
