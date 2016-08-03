
#include "../CLocationBar.h"


CLocationBar::CLocationBar(QWidget *parent)
    :QWidget(parent)
{
    m_textFont.setPixelSize(12);
    //m_textFont.setFamily(QString::fromLocal8Bit("宋体"));

    setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255,255,255));
    setPalette(palette);

    m_pMainLayout = new QHBoxLayout();
    this->setLayout(m_pMainLayout);

    //m_pHomeIcon = new QLabel(this);
    //QPixmap pixmap(":/tip/icon/navigationbar/HIDI_NAVIGATION_HOME.png");
    //m_pHomeIcon->setPixmap(pixmap);

    m_pMainLayout->setContentsMargins(0,0,0,0);
    //m_pMainLayout->addWidget(m_pHomeIcon,0,Qt::AlignLeft);
}

CLocationBar::~CLocationBar()
{

}

void CLocationBar::setTitle(QStringList lstTitle)
{
    m_lstTitel = lstTitle;
    updateUI();
}

void CLocationBar::updateUI()
{
    clearLabels();

    if(m_lstTitel.count() == 1)
    {
        QLabel *pLable = new QLabel(this);
        setlastLabelStyle(pLable);

        m_pMainLayout->addWidget(pLable,0,Qt::AlignLeft);
        m_lstLocationWidgets.append(pLable);

    }
    else if(m_lstTitel.count() > 1)
    {
        for(int i = 0; i < m_lstTitel.count() - 1; i++)
        {
            QLabel *pLable = new QLabel(this);
            QString strName = m_lstTitel.at(i) + " / ";
            pLable->setText(strName);
            pLable->setFont(m_textFont);
            QString strStyle = "QLabel{color:#999999;}";
            pLable->setStyleSheet(strStyle);
            m_pMainLayout->addWidget(pLable,0,Qt::AlignLeft);

            m_lstLocationWidgets.append(pLable);

        }

        QLabel *pLastLable = new QLabel(this);
        setlastLabelStyle(pLastLable);
        m_pMainLayout->addWidget(pLastLable,0,Qt::AlignLeft);
        m_lstLocationWidgets.append(pLastLable);
    }
}

void CLocationBar::clearLabels()
{
    for(int i = 0; i < m_lstLocationWidgets.count(); i++)
    {
        QWidget *pLabel = m_lstLocationWidgets.at(i);
        m_pMainLayout->removeWidget(pLabel);
        delete pLabel;
    }
    m_lstLocationWidgets.clear();
}

void CLocationBar::setlastLabelStyle(QLabel *pLabel)
{
    QString strText = m_lstTitel.last();
    pLabel->setText(strText);
    pLabel->setFont(m_textFont);

    QString strStyle = "QLabel{color:#49a7ff;}";
    pLabel->setStyleSheet(strStyle);
}
