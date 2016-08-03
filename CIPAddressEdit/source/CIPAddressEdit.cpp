#include "../../include/CIPAddressEdit.h"
#include "../CIPPartlineEdit.h"

CIPAddressEdit::CIPAddressEdit(QWidget* pParent)
    : QFrame(pParent)
{
    setObjectName("ipedit");
    m_pIpPart1 = new CIPPartlineEdit(this);
    m_pIpPart2 = new CIPPartlineEdit(this);
    m_pIpPart3 = new CIPPartlineEdit(this);
    m_pIpPart4 = new CIPPartlineEdit(this);

    QFont font;
    font.setPixelSize(20);
    m_plblDot1 = new QLabel(this);
    m_plblDot1->setObjectName("dot");
    m_plblDot1->setFont(font);
    m_plblDot2 = new QLabel(this);
    m_plblDot2->setObjectName("dot");
    m_plblDot2->setFont(font);
    m_plblDot3 = new QLabel(this);
    m_plblDot3->setObjectName("dot");
    m_plblDot3->setFont(font);
    m_plblDot1->setText(" .");
    m_plblDot1->setFixedWidth(10);
    m_plblDot1->setAlignment(Qt::AlignCenter);

    m_plblDot2->setText(" .");
    m_plblDot2->setFixedWidth(10);
    m_plblDot2->setAlignment(Qt::AlignCenter);

    m_plblDot3->setText(" .");
    m_plblDot3->setFixedWidth(10);
    m_plblDot3->setAlignment(Qt::AlignCenter);

    QWidget::setTabOrder(m_pIpPart1, m_pIpPart2);
    QWidget::setTabOrder(m_pIpPart2, m_pIpPart3);
    QWidget::setTabOrder(m_pIpPart3, m_pIpPart4);
    m_pIpPart1->setNtextTabEdit(m_pIpPart2);
    m_pIpPart2->setNtextTabEdit(m_pIpPart3);
    m_pIpPart3->setNtextTabEdit(m_pIpPart4);
    m_pIpPart1->setFixedHeight(m_plblDot1->height());
    m_pIpPart2->setFixedHeight(m_plblDot1->height());
    m_pIpPart3->setFixedHeight(m_plblDot1->height());
    m_pIpPart4->setFixedHeight(m_plblDot1->height());

    m_pIpPart4->setPrevEdit(m_pIpPart3);
    m_pIpPart3->setPrevEdit(m_pIpPart2);
    m_pIpPart2->setPrevEdit(m_pIpPart1);

    QHBoxLayout  *phblMain = new QHBoxLayout();
    phblMain->setContentsMargins(1, 1, 1, 1);
    phblMain->setSpacing(0);
    phblMain->addWidget(m_pIpPart1);
    phblMain->addWidget(m_plblDot1);
    phblMain->addWidget(m_pIpPart2);
    phblMain->addWidget(m_plblDot2);
    phblMain->addWidget(m_pIpPart3);
    phblMain->addWidget(m_plblDot3);
    phblMain->addWidget(m_pIpPart4);
    this->setLayout(phblMain);

    connect(m_pIpPart1, SIGNAL(textChanged(const QString&)), this, SLOT(sltTextChanged(const QString&)));
    connect(m_pIpPart2, SIGNAL(textChanged(const QString&)), this, SLOT(sltTextChanged(const QString&)));
    connect(m_pIpPart3, SIGNAL(textChanged(const QString&)), this, SLOT(sltTextChanged(const QString&)));
    connect(m_pIpPart4, SIGNAL(textChanged(const QString&)), this, SLOT(sltTextChanged(const QString&)));

    connect(m_pIpPart1, SIGNAL(textEdited (const QString&)), this, SLOT(sltTextEdited(const QString&)));
    connect(m_pIpPart2, SIGNAL(textEdited (const QString&)), this, SLOT(sltTextEdited(const QString&)));
    connect(m_pIpPart3, SIGNAL(textEdited (const QString&)), this, SLOT(sltTextEdited(const QString&)));
    connect(m_pIpPart4, SIGNAL(textEdited (const QString&)), this, SLOT(sltTextEdited(const QString&)));

    /*
    m_pIpPart1->setStyleSheet("border: 0px solid rgb(180, 180, 180);\
                              border-left: 1px solid rgb(180, 180, 180);\
                               border-top: 1px solid rgb(180, 180, 180);\
                               border-bottom: 1px solid rgb(180, 180, 180);\
                               border-top-left-radius: 5px;\
                                border-bottom-left-radius: 5px;");
   m_pIpPart4->setStyleSheet("border: 0px solid rgb(180, 180, 180);\
                             border-right: 1px solid rgb(180, 180, 180);\
                              border-top: 1px solid rgb(180, 180, 180);\
                              border-bottom: 1px solid rgb(180, 180, 180);\
                              border-top-right-radius: 5px;\
                              border-bottom-right-radius: 5px;");
   m_plblDot1->setStyleSheet("border: 0px solid rgb(180, 180, 180);\
                              border-top: 1px solid rgb(180, 180, 180);\
                              border-bottom: 1px solid rgb(180, 180, 180);\
                              background-color:transparent;");
   m_plblDot2->setStyleSheet("border: 0px solid rgb(180, 180, 180);\
                              border-top: 1px solid rgb(180, 180, 180);\
                              border-bottom: 1px solid rgb(180, 180, 180);\
                              background-color:transparent;");
   m_plblDot3->setStyleSheet("border: 0px solid rgb(180, 180, 180);\
                              border-top: 1px solid rgb(180, 180, 180);\
                              border-bottom: 1px solid rgb(180, 180, 180);\
                              background-color:transparent;");
   m_pIpPart2->setStyleSheet("border: 0px solid rgb(180, 180, 180);\
                              border-top: 1px solid rgb(180, 180, 180);\
                              border-bottom: 1px solid rgb(180, 180, 180);");
   m_pIpPart3->setStyleSheet("border: 0px solid rgb(180, 180, 180);\
                              border-top: 1px solid rgb(180, 180, 180);\
                              border-bottom: 1px solid rgb(180, 180, 180);\
                              ");
                              */

    //m_pIpPart1->setStyleSheet();

}

CIPAddressEdit::~CIPAddressEdit()
{

}

void CIPAddressEdit::sltTextChanged(const QString&)
{
    QString ippart1, ippart2, ippart3, ippart4;
    ippart1 = m_pIpPart1->text();
    ippart2 = m_pIpPart2->text();
    ippart3 = m_pIpPart3->text();
    ippart4 = m_pIpPart4->text();

    QString ipaddr = QString("%1.%2.%3.%4")
                     .arg(ippart1)
                     .arg(ippart2)
                     .arg(ippart3)
                     .arg(ippart4);

    emit sigTextchanged(ipaddr);
}

void CIPAddressEdit::sltTextEdited(const QString &)
{
    QString ippart1, ippart2, ippart3, ippart4;
    ippart1 = m_pIpPart1->text();
    ippart2 = m_pIpPart2->text();
    ippart3 = m_pIpPart3->text();
    ippart4 = m_pIpPart4->text();

    QString ipaddr = QString("%1.%2.%3.%4")
        .arg(ippart1)
        .arg(ippart2)
        .arg(ippart3)
        .arg(ippart4);

    emit sitTextEdited(ipaddr);
}

void CIPAddressEdit::setText(const QString &text)
{
    QString ippart1, ippart2, ippart3, ippart4;
    QString qstring_validate = text;

    // IP地址验证
    QRegExp regexp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    QRegExpValidator regexp_validator(regexp, this);
    int nPos = 0;
    QValidator::State state = regexp_validator.validate(qstring_validate, nPos);
    // IP合法
    if (state == QValidator::Acceptable)
    {
        //下面开始分割字符串，用点号进行分割，得到每个字符串，如果字符串，不合法，则返回false，不合法情况包括，字符串中间有空格，字符串有前导0，字符串中数字不再0-255之间，还有字符串为空，这些都是不合法
        QStringList ippartlist = text.split(".");

        int strcount = ippartlist.size();
        int index = 0;
        if (index < strcount)
        {
            ippart1 = ippartlist.at(index);
        }
        if (++index < strcount)
        {
            ippart2 = ippartlist.at(index);
        }
        if (++index < strcount)
        {
            ippart3 = ippartlist.at(index);
        }
        if (++index < strcount)
        {
            ippart4 = ippartlist.at(index);
        }
    }

    m_pIpPart1->setText(ippart1);
    m_pIpPart2->setText(ippart2);
    m_pIpPart3->setText(ippart3);
    m_pIpPart4->setText(ippart4);
}

QString CIPAddressEdit::getText()
{
    QString ippart1, ippart2, ippart3, ippart4;
    ippart1 = m_pIpPart1->text();
    ippart2 = m_pIpPart2->text();
    ippart3 = m_pIpPart3->text();
    ippart4 = m_pIpPart4->text();

    if(ippart1.isEmpty() || ippart2.isEmpty() || ippart3.isEmpty() || ippart4.isEmpty())
    {
        return "";
    }
    else
    {
        return QString("%1.%2.%3.%4")
            .arg(ippart1)
            .arg(ippart2)
            .arg(ippart3)
            .arg(ippart4);
    }
}

void CIPAddressEdit::setStyleSheet(const QString &styleSheet)
{
    m_pIpPart1->setStyleSheet(styleSheet);
    m_pIpPart2->setStyleSheet(styleSheet);
    m_pIpPart3->setStyleSheet(styleSheet);
    m_pIpPart4->setStyleSheet(styleSheet);
}

void CIPAddressEdit::setHeight(int nHeight)
{
    m_pIpPart1->setFixedHeight(nHeight - 2);
    m_pIpPart2->setFixedHeight(nHeight - 2);
    m_pIpPart3->setFixedHeight(nHeight - 2);
    m_pIpPart4->setFixedHeight(nHeight - 2);

    m_plblDot1->setFixedHeight(nHeight - 2);
    m_plblDot2->setFixedHeight(nHeight - 2);
    m_plblDot3->setFixedHeight(nHeight - 2);
}

void CIPAddressEdit::setDotAlignment(Qt::Alignment n)
{
    m_plblDot1->setAlignment(n);
    m_plblDot2->setAlignment(n);
    m_plblDot3->setAlignment(n);
}

void CIPAddressEdit::setDotObjectName(QString name)
{
    m_plblDot1->setObjectName(name);
    m_plblDot2->setObjectName(name);
    m_plblDot3->setObjectName(name);

    m_pIpPart1->setObjectName(name);
    m_pIpPart2->setObjectName(name);
    m_pIpPart3->setObjectName(name);
    m_pIpPart4->setObjectName(name);
}

void CIPAddressEdit::setReadOnly(bool b)
{
    m_pIpPart1->setReadOnly(b);
    m_pIpPart2->setReadOnly(b);
    m_pIpPart3->setReadOnly(b);
    m_pIpPart4->setReadOnly(b);
}

