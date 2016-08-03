
#include "../../include/CSharpCornerWidget.h"

#include "../CCustomToolButton.h"

CSharpCornerWidget::CSharpCornerWidget(QWidget *parent, QPixmap pixShadow)
    :CShadowWidget(parent,pixShadow)
{
    m_pMainLayout = new QVBoxLayout();

    setWindowFlags( windowFlags() | Qt::Popup);

    setBackgroundColor(QColor(92,179,255));
    setContentMargin(4,7,4,4);

    m_pMainLayout->setSpacing(0);
    m_pMainLayout->setContentsMargins(0,0,0,0);



    m_pTitleLabel = new QLabel(this);
    m_pTitleLabel->setFixedHeight(40);
    m_pTitleLabel->setAlignment(Qt::AlignCenter);
    m_pTitleLabel->setText("hello");
    m_pTitleLabel->setStyleSheet("color:#ffffff;");

    m_pMainLayout->addWidget(m_pTitleLabel,1,Qt::AlignTop);

    this->setLayout(m_pMainLayout);


}

CSharpCornerWidget::~CSharpCornerWidget()
{

}

void CSharpCornerWidget::setTitle(QString strTitle)
{
    m_pTitleLabel->setText(strTitle);
}

void CSharpCornerWidget::addActionItem(QString strIcon, QString strText, QString strKey)
{
    CCustomToolButton *pToolButton = new CCustomToolButton(this);
    pToolButton->setText(strText);
    pToolButton->setIcon(strIcon);
    pToolButton->setKey(strKey);
    pToolButton->setFontColor("#666666");//"#5cb3ff"
    pToolButton->setFixedHeight(35);
    connect(pToolButton,SIGNAL(clicked()),this,SLOT(sltItemClicked()));
    m_pMainLayout->addWidget(pToolButton);
    m_lstItem.append(pToolButton);

    updateItems();
}

void CSharpCornerWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void CSharpCornerWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

void CSharpCornerWidget::hideEvent(QHideEvent *event)
{
    //qDebug("======================CSharpCornerWidget::hideEvent");
    emit sigHidden();
    QWidget::hideEvent(event);
}

void CSharpCornerWidget::updateItems()
{
    for(int i = 0; i < m_lstItem.count() - 1; i++)
    {
        CCustomToolButton *pToolButton = m_lstItem.at(i);
        pToolButton->setHasBottomLine(true);
    }
    CCustomToolButton *pToolButton = m_lstItem.last();
    pToolButton->setHasBottomLine(false);
}

void CSharpCornerWidget::sltItemClicked()
{
    CCustomToolButton *sender = qobject_cast<CCustomToolButton *>(this->sender());
    QString strKey = sender->getKey();
    emit sigItemClicked(strKey);
}
