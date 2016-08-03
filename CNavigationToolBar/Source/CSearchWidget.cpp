
#include "../CSearchWidget.h"


CSearchWidget::CSearchWidget(QWidget *parent)
    :QWidget(parent)
{
    m_pMainLayout= new QHBoxLayout();
    this->setLayout(m_pMainLayout);

    QIcon searchIcon(":/tip/icon/navigationbar/HIDI_NAVIGATION_RESEARCH.png");

    /*
    m_pBtnOrignalSearch = new QPushButton(this);
    m_pBtnOrignalSearch->setIcon(searchIcon);
    m_pBtnOrignalSearch->setStyleSheet(strOrigBtnStyle);
    m_pBtnOrignalSearch->setFixedSize(24,24);
    connect(m_pBtnOrignalSearch,SIGNAL(clicked()),this,SLOT(sltOrignalSearchClicked()));
    */


    QString strEditorStyle = "QLineEdit{\
            border: 1px solid #dfedfd;\
            border-top-left-radius: 2px;\
            border-bottom-left-radius: 2px;\
            color:#333333;\
            padding-left:8px;\
            }";

    m_pSearchEditor = new QLineEdit(this);
    m_pSearchEditor->setStyleSheet(strEditorStyle);
    m_pSearchEditor->setFixedSize(140,24);
    QString strPlaceText = QString::fromLocal8Bit("请输入关键字");
    m_pSearchEditor->setPlaceholderText(strPlaceText);


    QString strSearchBtnStyle = "QPushButton {\
            border: 0px solid #999999;\
            border-top-right-radius: 2px;\
            border-bottom-right-radius: 2px;\
            background-color: #368ee0;\
            }";
    m_pBtnSearch = new QPushButton(this);
    m_pBtnSearch->setIcon(searchIcon);
    m_pBtnSearch->setStyleSheet(strSearchBtnStyle);
    m_pBtnSearch->setFixedSize(24,24);
    connect(m_pBtnSearch,SIGNAL(clicked()),this,SLOT(sltSearchClicked()));


    m_pMainLayout->setContentsMargins(0,0,0,0);
    //m_pMainLayout->addWidget(m_pBtnOrignalSearch,0,Qt::AlignLeft);
    m_pMainLayout->addWidget(m_pSearchEditor,0,Qt::AlignLeft);
    m_pMainLayout->setSpacing(0);
    m_pMainLayout->addWidget(m_pBtnSearch,0,Qt::AlignLeft);


    connect(m_pSearchEditor, SIGNAL(textChanged(QString)), this, SLOT(sltCheckInput(QString)));
    connect(m_pSearchEditor, SIGNAL(returnPressed()), this, SLOT(sltSearchClicked()));
    //m_pSearchEditor->hide();
    //m_pBtnSearch->hide();
}

CSearchWidget::~CSearchWidget()
{

}

void CSearchWidget::clearString()
{
    m_pSearchEditor->clear();
}

void CSearchWidget::sltOrignalSearchClicked()
{
    //m_pBtnOrignalSearch->hide();

    m_pSearchEditor->show();
    m_pBtnSearch->show();

}

void CSearchWidget::sltSearchClicked()
{
    //m_pBtnOrignalSearch->show();
    //m_pSearchEditor->hide();
    //m_pBtnSearch->hide();

    m_pSearchEditor->clearFocus();
    QString strText = m_pSearchEditor->text();
    emit sigResearch(strText);
    //m_pSearchEditor->clear();
}

void CSearchWidget::sltCheckInput(QString str)
{
    int nCurPos = m_pSearchEditor->cursorPosition();
    int nSize = str.toUtf8().size();
    if(nSize <= 100)
    {
        m_strOldText = str;
    }
    m_pSearchEditor->setText(m_strOldText);
    m_pSearchEditor->setCursorPosition(nCurPos);
}
