
#include "../../include/CSwitchPageToolBar.h"

#define RECORDNUMBER 20

CSwitchPageToolBar::CSwitchPageToolBar(QWidget *parent)
    :QWidget(parent)
{
    setFocusPolicy(Qt::ClickFocus);
    m_pMainLayout= new QHBoxLayout();
    this->setLayout(m_pMainLayout);
    this->setObjectName("CSwitchPageToolBar");
    this->setStyleSheet("QWidget#CSwitchPageToolBar{\
                        border:1px solid #f0f0f0;\
                        background-color:#f9f9f9;\
                        }");

    initStyle();

    QFont font;
    font.setPixelSize(12);

    m_pFirstPageButton = new QPushButton(this);
    m_pFirstPageButton->setText(QString::fromLocal8Bit("首页"));
    m_pFirstPageButton->setFixedSize(40,30);
    m_pFirstPageButton->setStyleSheet(m_strDefaultStyle);
    m_pFirstPageButton->setFont(font);
    connect(m_pFirstPageButton,SIGNAL(clicked()),this,SLOT(sltFirstPageClick()));


    m_pPrePageButton = new QPushButton(this);
    m_pPrePageButton->setIcon(QIcon(":/tip/icon/switchpagebar/HIDI_SWITCHPAGE_ARROW_LEFT.png"));
    m_pPrePageButton->setFixedSize(30,30);
    m_pPrePageButton->setStyleSheet(m_strDefaultStyle);
    connect(m_pPrePageButton,SIGNAL(clicked()),this,SLOT(sltPrePageClick()));

    QFont numberFont("Arial");
    numberFont.setPixelSize(12);
    //numberFont.setBold(true);
    m_pFirstNumberButton = new QPushButton(this);
    m_pFirstNumberButton->setText("1");    
    m_pFirstNumberButton->setFixedSize(30,30);
    m_pFirstNumberButton->setFont(numberFont);
    m_pFirstNumberButton->setStyleSheet(m_strDefaultStyle);
    connect(m_pFirstNumberButton,SIGNAL(clicked()),this,SLOT(sltFirstNumberClick()));    

    m_pSecondNumberButton = new QPushButton(this);
    m_pSecondNumberButton->setText("2");
    m_pSecondNumberButton->setFixedSize(30,30);
    m_pSecondNumberButton->setFont(numberFont);
    m_pSecondNumberButton->setStyleSheet(m_strDefaultStyle);
    connect(m_pSecondNumberButton,SIGNAL(clicked()),this,SLOT(sltSecondNumberClick()));

    m_pThirdNumberButton = new QPushButton(this);
    m_pThirdNumberButton->setText("3");
    m_pThirdNumberButton->setFixedSize(30,30);
    m_pThirdNumberButton->setFont(numberFont);
    m_pThirdNumberButton->setStyleSheet(m_strDefaultStyle);
    connect(m_pThirdNumberButton,SIGNAL(clicked()),this,SLOT(sltThirdNumberClick()));

    m_pNextPageButton = new QPushButton(this);
    m_pNextPageButton->setIcon(QIcon(":/tip/icon/switchpagebar/HIDI_SWITCHPAGE_ARROW_RIGHT.png"));
    m_pNextPageButton->setFixedSize(30,30);
    m_pNextPageButton->setStyleSheet(m_strDefaultStyle);
    connect(m_pNextPageButton,SIGNAL(clicked()),this,SLOT(sltNextPageClick()));

    m_pLastPageButton = new QPushButton(this);
    m_pLastPageButton->setText(QString::fromLocal8Bit("尾页"));
    m_pLastPageButton->setFixedSize(40,30);
    m_pLastPageButton->setFont(font);
    connect(m_pLastPageButton,SIGNAL(clicked()),this,SLOT(sltLastPageClick()));
    m_pLastPageButton->setStyleSheet(m_strDefaultStyle);



    QString strlabelstyle = "QLabel{\
            color: #717171;\
        }";
    m_pGotoLabel = new QLabel(this);
    m_pGotoLabel->setAttribute(Qt::WA_TranslucentBackground);
    m_pGotoLabel->setText(QString::fromLocal8Bit("跳转到："));
    m_pGotoLabel->setFixedHeight(30);
    m_pGotoLabel->setFont(font);
    m_pGotoLabel->setStyleSheet(strlabelstyle);

    QString strEditStyle = "QLineEdit {\
            border: 1px solid #c6c9ca;\
            border-radius: 2px;\
        }";


    m_pNumberEditor = new QLineEdit(this);
    m_pNumberEditor->setFocusPolicy(Qt::ClickFocus);
    //QIntValidator *validator = new QIntValidator(m_pNumberEditor);
    //validator->setBottom(1);
    //m_pNumberEditor->setValidator(validator);
    //QValidator *validator = new QIntValidator(1,99999,this);
    //m_pNumberEditor->setValidator(validator);

    QRegExp regx("[0-9]+$");//只能输入数字
    QValidator *validator=new QRegExpValidator(regx,m_pNumberEditor);
    m_pNumberEditor->setValidator(validator);
    m_pNumberEditor->setMaxLength(8);
    m_pNumberEditor->setFixedSize(40,30);
    m_pNumberEditor->setStyleSheet(strEditStyle);
    m_pNumberEditor->setAlignment(Qt::AlignCenter);
    connect(m_pNumberEditor, SIGNAL(returnPressed()), this, SLOT(sltGotoPageClick()));


    m_pGotoButton = new QPushButton(this);
    m_pGotoButton->setText("Go");
    m_pGotoButton->setFixedSize(30,30);
    m_pGotoButton->setStyleSheet(m_strDefaultStyle);
    connect(m_pGotoButton,SIGNAL(clicked()),this,SLOT(sltGotoPageClick()));

    m_pFirstRecordLabel = new QLabel(this);
    m_pFirstRecordLabel->setAttribute(Qt::WA_TranslucentBackground);
    m_pFirstRecordLabel->setText(QString::fromLocal8Bit("当前页"));
    m_pFirstRecordLabel->setFixedSize(38,30);
    m_pFirstRecordLabel->setFont(font);
    m_pFirstRecordLabel->setStyleSheet(strlabelstyle);

    QFont curRecordFont(font);
    curRecordFont.setBold(true);
    m_pCurRecordLabel = new QLabel(this);
    m_pCurRecordLabel->setAttribute(Qt::WA_TranslucentBackground);
    m_pCurRecordLabel->setFixedHeight(30);
    m_pCurRecordLabel->setFont(curRecordFont);
    m_pCurRecordLabel->setStyleSheet("QLabel{color: #83b2e8;}");

    m_pMidRecordLabel = new QLabel(this);
    m_pMidRecordLabel->setAttribute(Qt::WA_TranslucentBackground);
    m_pMidRecordLabel->setText(QString::fromLocal8Bit("条，共"));
    m_pMidRecordLabel->setFixedHeight(30);
    //m_pMidRecordLabel->setFixedSize(60,30);
    m_pMidRecordLabel->setFont(font);
    m_pMidRecordLabel->setStyleSheet(strlabelstyle);
    m_pMidRecordLabel->adjustSize();

    m_pTotalRecordLabel = new QLabel(this);
    m_pTotalRecordLabel->setAttribute(Qt::WA_TranslucentBackground);
    m_pTotalRecordLabel->setFixedHeight(30);
    m_pTotalRecordLabel->setAlignment(Qt::AlignCenter);
    m_pTotalRecordLabel->setFont(curRecordFont);
    m_pTotalRecordLabel->setStyleSheet("QLabel{color: #b9b9b9;}");

    m_pLastRecordLabel = new QLabel(this);
    m_pLastRecordLabel->setAttribute(Qt::WA_TranslucentBackground);
    m_pLastRecordLabel->setText(QString::fromLocal8Bit("条记录"));
    m_pLastRecordLabel->setFixedHeight(30);
    m_pLastRecordLabel->setFont(font);
    m_pLastRecordLabel->setStyleSheet(strlabelstyle);

    m_pMainLayout->setContentsMargins(10,5,10,5);
    m_pMainLayout->addWidget(m_pFirstPageButton,0,Qt::AlignLeft);
    m_pMainLayout->addWidget(m_pPrePageButton,0,Qt::AlignLeft);
    m_pMainLayout->addWidget(m_pFirstNumberButton,0,Qt::AlignLeft);
    m_pMainLayout->addWidget(m_pSecondNumberButton,0,Qt::AlignLeft);
    m_pMainLayout->addWidget(m_pThirdNumberButton,0,Qt::AlignLeft);
    m_pMainLayout->addWidget(m_pNextPageButton,0,Qt::AlignLeft);
    m_pMainLayout->addWidget(m_pLastPageButton,0,Qt::AlignLeft);
    m_pMainLayout->addSpacing(10);
    m_pMainLayout->addWidget(m_pGotoLabel,0,Qt::AlignLeft);    
    m_pMainLayout->addWidget(m_pNumberEditor,0,Qt::AlignLeft);
    m_pMainLayout->addWidget(m_pGotoButton,1,Qt::AlignLeft);

    m_pMainLayout->addStretch(1);
    m_pMainLayout->addWidget(m_pFirstRecordLabel,0,Qt::AlignRight);
    m_pMainLayout->addWidget(m_pCurRecordLabel,0,Qt::AlignRight);
    m_pMainLayout->addWidget(m_pMidRecordLabel,0,Qt::AlignRight);
    m_pMainLayout->addWidget(m_pTotalRecordLabel,0,Qt::AlignRight);
    m_pMainLayout->addWidget(m_pLastRecordLabel,0,Qt::AlignRight);

    m_nTotalPageNumber = 0;
    m_nTotalRecord = 0;
    m_nCurrentPageNumber = 1;

    m_pFirstPageButton->setEnabled(false);
    m_pPrePageButton->setEnabled(false);
    m_pNextPageButton->setEnabled(false);
    m_pLastPageButton->setEnabled(false);
    m_pFirstNumberButton->setEnabled(false);
    m_pSecondNumberButton->setEnabled(false);
    m_pThirdNumberButton->setEnabled(false);

}

CSwitchPageToolBar::~CSwitchPageToolBar()
{

}

void CSwitchPageToolBar::setTotalRecordNumber(int nTotal)
{
    m_nTotalRecord = nTotal;
    m_nTotalPageNumber = nTotal/RECORDNUMBER + (nTotal%RECORDNUMBER != 0 ? 1 : 0);

    m_pTotalRecordLabel->setText(QString::number(nTotal));
}

void CSwitchPageToolBar::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void CSwitchPageToolBar::setCurrentPage(int nCur)
{
    if(m_nTotalPageNumber == 0)
    {
        initBtnState();        
        m_pSecondNumberButton->setEnabled(false);
        m_pThirdNumberButton->setEnabled(false);
        m_pFirstPageButton->setEnabled(false);
        m_pPrePageButton->setEnabled(false);
        m_pNextPageButton->setEnabled(false);
        m_pLastPageButton->setEnabled(false);
        m_pFirstNumberButton->setText(QString::number(1));
        m_pSecondNumberButton->setText(QString::number(2));
        m_pThirdNumberButton->setText(QString::number(3));
        m_pFirstNumberButton->setStyleSheet(m_strCheckedStyle);
        m_pSecondNumberButton->setStyleSheet(m_strDefaultStyle);
        m_pThirdNumberButton->setStyleSheet(m_strDefaultStyle);
        m_pCurRecordLabel->setText(QString::number(0));

        m_nCurrentPageNumber = 1;

        this->setVisible(false);
        return;
    }

    if(nCur > m_nTotalPageNumber)
    {
        m_nCurrentPageNumber = m_nTotalPageNumber;
    }
    else
    {
        m_nCurrentPageNumber = nCur;
    }

    initBtnState();

    if(m_nTotalPageNumber == 1)
    {
        m_pFirstNumberButton->setText(QString::number(1));
        m_pSecondNumberButton->setText(QString::number(2));
        m_pThirdNumberButton->setText(QString::number(3));
        m_pSecondNumberButton->setEnabled(false);
        m_pThirdNumberButton->setEnabled(false);

        this->setVisible(false);
    }
    else if(m_nTotalPageNumber == 2)
    {
        m_pFirstNumberButton->setText(QString::number(1));
        m_pSecondNumberButton->setText(QString::number(2));
        m_pThirdNumberButton->setText(QString::number(3));
        m_pThirdNumberButton->setEnabled(false);
    }
    else
    {
        if(isCenter(nCur))
        {
            m_pFirstNumberButton->setText(QString::number(nCur - 1));
            m_pSecondNumberButton->setText(QString::number(nCur));
            m_pThirdNumberButton->setText(QString::number(nCur + 1));
        }
        else if(isLeft(nCur))
        {
            m_pFirstNumberButton->setText(QString::number(nCur));
            m_pSecondNumberButton->setText(QString::number(nCur + 1));
            m_pThirdNumberButton->setText(QString::number(nCur + 2));
        }
        else if(isRight(nCur))
        {
            m_pFirstNumberButton->setText(QString::number(nCur - 2));
            m_pSecondNumberButton->setText(QString::number(nCur - 1));
            m_pThirdNumberButton->setText(QString::number(nCur));
        }
    }

    if(isLeft(nCur))
    {
        m_pFirstPageButton->setEnabled(false);
        m_pPrePageButton->setEnabled(false);
    }

    if(isRight(nCur))
    {
        m_pNextPageButton->setEnabled(false);
        m_pLastPageButton->setEnabled(false);
    }

    setNumberButtonStyle();

    int nCount = getPageRecordCount(m_nCurrentPageNumber);
    m_pCurRecordLabel->setText(QString::number(nCount));

    int maxNumber = m_pThirdNumberButton->text().toInt();
    if(maxNumber >= 1000 )
    {
        m_pThirdNumberButton->setFixedWidth(40);
        m_pSecondNumberButton->setFixedWidth(40);
        m_pFirstNumberButton->setFixedWidth(40);
    }
    else
    {
        m_pThirdNumberButton->setFixedWidth(30);
        m_pSecondNumberButton->setFixedWidth(30);
        m_pFirstNumberButton->setFixedWidth(30);
    }

}

int CSwitchPageToolBar::getCurrentPage()
{
    return m_nCurrentPageNumber;
}

void CSwitchPageToolBar::clearGoPageNum()
{
    m_pNumberEditor->clear();
}

void CSwitchPageToolBar::setSwitchPageEnable(bool bEnable)
{
    m_pNumberEditor->setEnabled(bEnable);
    m_pGotoButton->setEnabled(bEnable);

    if(bEnable)
    {
        setCurrentPage(m_nCurrentPageNumber);
    }
    else
    {
        m_pFirstPageButton->setEnabled(bEnable);
        m_pPrePageButton->setEnabled(bEnable);
        m_pNextPageButton->setEnabled(bEnable);
        m_pLastPageButton->setEnabled(bEnable);
        m_pFirstNumberButton->setEnabled(bEnable);
        m_pSecondNumberButton->setEnabled(bEnable);
        m_pThirdNumberButton->setEnabled(bEnable);
    }

}

void CSwitchPageToolBar::initBtnState()
{
    this->setVisible(true);

    m_pFirstPageButton->setEnabled(true);
    m_pPrePageButton->setEnabled(true);
    m_pNextPageButton->setEnabled(true);
    m_pLastPageButton->setEnabled(true);
    m_pFirstNumberButton->setEnabled(true);
    m_pSecondNumberButton->setEnabled(true);
    m_pThirdNumberButton->setEnabled(true);
}

void CSwitchPageToolBar::initStyle()
{
    m_strDefaultStyle = "QPushButton {\
            border: 1px solid #c6c9ca;\
            border-radius: 2px;\
            background-color: #ffffff;\
            color:#666666;\
            }\
            QPushButton:focus{outline: none;}\
            QPushButton:hover{\
                border: 1px solid #368ee0;\
                border-radius: 2px;\
                background-color: #ffffff;\
                color:#666666;\
            }\
            QPushButton:!enabled\
            {\
                border: none;\
                border-radius: 2px;\
                background-color: #efefef;\
                color:#999999;\
            }";

    m_strCheckedStyle = "QPushButton {\
            border: none;\
            border-radius: 2px;\
            background-color: #368ee0;\
            color:#ffffff;\
            }\
            QPushButton:focus{outline: none;}";
}

bool CSwitchPageToolBar::isLeft(int nIndex)
{
    return nIndex == 1;
}

bool CSwitchPageToolBar::isCenter(int nIndex)
{
    bool bCenter = false;
    if(nIndex > 1 && nIndex < m_nTotalPageNumber)
    {
        bCenter = true;
    }
    return bCenter;
}

bool CSwitchPageToolBar::isRight(int nIndex)
{
    return nIndex == m_nTotalPageNumber;
}

void CSwitchPageToolBar::setNumberButtonStyle()
{
    if(m_nTotalPageNumber == 1)
    {
        m_pFirstNumberButton->setStyleSheet(m_strCheckedStyle);
        m_pSecondNumberButton->setStyleSheet(m_strDefaultStyle);
        m_pThirdNumberButton->setStyleSheet(m_strDefaultStyle);
    }
    else if(m_nTotalPageNumber == 2)
    {
        if(isLeft(m_nCurrentPageNumber))
        {
            m_pFirstNumberButton->setStyleSheet(m_strCheckedStyle);
            m_pSecondNumberButton->setStyleSheet(m_strDefaultStyle);
            m_pThirdNumberButton->setStyleSheet(m_strDefaultStyle);
        }
        else if(isRight(m_nCurrentPageNumber))
        {
            m_pFirstNumberButton->setStyleSheet(m_strDefaultStyle);
            m_pSecondNumberButton->setStyleSheet(m_strCheckedStyle);
            m_pThirdNumberButton->setStyleSheet(m_strDefaultStyle);
        }
    }
    else
    {
        if(isCenter(m_nCurrentPageNumber))
        {
            m_pFirstNumberButton->setStyleSheet(m_strDefaultStyle);
            m_pSecondNumberButton->setStyleSheet(m_strCheckedStyle);
            m_pThirdNumberButton->setStyleSheet(m_strDefaultStyle);
        }
        else if(isLeft(m_nCurrentPageNumber))
        {
            m_pFirstNumberButton->setStyleSheet(m_strCheckedStyle);
            m_pSecondNumberButton->setStyleSheet(m_strDefaultStyle);
            m_pThirdNumberButton->setStyleSheet(m_strDefaultStyle);
        }
        else if(isRight(m_nCurrentPageNumber))
        {
            m_pFirstNumberButton->setStyleSheet(m_strDefaultStyle);
            m_pSecondNumberButton->setStyleSheet(m_strDefaultStyle);
            m_pThirdNumberButton->setStyleSheet(m_strCheckedStyle);
        }
    }
}

int CSwitchPageToolBar::getPageRecordCount(int nPage)
{
    int nCount = 0;
    nCount = m_nTotalRecord - (nPage - 1) * RECORDNUMBER;
    if(nCount > RECORDNUMBER)
    {
        nCount = RECORDNUMBER;
    }
    return nCount;
}

void CSwitchPageToolBar::sltFirstPageClick()
{
    setCurrentPage(1);
    emit sigGotoPage(m_nCurrentPageNumber);
}

void CSwitchPageToolBar::sltPrePageClick()
{
    setCurrentPage(m_nCurrentPageNumber-1);
    emit sigGotoPage(m_nCurrentPageNumber);

}

void CSwitchPageToolBar::sltFirstNumberClick()
{
    int nIndex = m_pFirstNumberButton->text().toInt();
    if(nIndex != m_nCurrentPageNumber)
    {
        setCurrentPage(nIndex);
        emit sigGotoPage(m_nCurrentPageNumber);
    }
}

void CSwitchPageToolBar::sltSecondNumberClick()
{
    int nIndex = m_pSecondNumberButton->text().toInt();
    if(nIndex != m_nCurrentPageNumber)
    {
        setCurrentPage(nIndex);
        emit sigGotoPage(m_nCurrentPageNumber);
    }
}

void CSwitchPageToolBar::sltThirdNumberClick()
{
    int nIndex = m_pThirdNumberButton->text().toInt();
    if(nIndex != m_nCurrentPageNumber)
    {
        setCurrentPage(nIndex);
        emit sigGotoPage(m_nCurrentPageNumber);
    }
}

void CSwitchPageToolBar::sltNextPageClick()
{
    setCurrentPage(m_nCurrentPageNumber + 1);
    emit sigGotoPage(m_nCurrentPageNumber);
}

void CSwitchPageToolBar::sltLastPageClick()
{
    setCurrentPage(m_nTotalPageNumber);
    emit sigGotoPage(m_nCurrentPageNumber);
}

void CSwitchPageToolBar::sltGotoPageClick()
{
    if(m_pNumberEditor->text().isEmpty())
    {
        return;
    }
    int nIndex = m_pNumberEditor->text().toInt();
    m_pNumberEditor->clear();
    if(nIndex != m_nCurrentPageNumber)
    {
        if(nIndex > m_nTotalPageNumber)
        {
            nIndex = m_nTotalPageNumber;
        }
        else if(nIndex < 1)
        {
            nIndex = 1;
        }
        setCurrentPage(nIndex);
        emit sigGotoPage(m_nCurrentPageNumber);
    }
}
