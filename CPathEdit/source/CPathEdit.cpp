#include "CPathEdit.h"
#include "CMessageWidget.h"

CPathEdit::CPathEdit(QWidget *parent, int fileDlgFlag)
    :QLabel(parent),
    m_nFileDlgFlag(fileDlgFlag)
{
    m_strWarinPixmap = ":/tip/icon/ID_WARING_ICON.png";
    m_nLenth = -1;
    m_strFilter = "*.*";
    //setMinimumHeight(25);
    m_strNormalStyle =  "QPushButton{"
            "border:0px solid rgb(180, 180, 180);"
            "background:#f3f3f3;"
            "border-radius:3px;"
            "color:#333333;"
            "font:12px;}"
            "QPushButton:hover{"
            "background:#999999;}"
            "QPushButton:pressed{"
            "background:#8bd6f3;}"
            "QLabel{"
            "background:rgb(255, 255, 255);"
            "border:1px solid #dddddd;"
            "border-radius:5px;}"
            "QLabel:hover{"
            "background:rgb(255, 255, 255);"
            "border:1px solid #999999;}"
            "QLineEdit{"
            "background:rgb(255, 255, 255);"
            "border:1px solid #dddddd;"
            "border-radius:5px;}"
            ;

    m_strHoverStyle = m_strNormalStyle;

    m_strFocusStyle =
            "QPushButton{"
            "border:0px solid rgb(180, 180, 180);"
            "background:#f3f3f3;"
            "border-radius:3px;"
            "color:#333333;"
            "font:12px;}"
            "QPushButton:hover{"
            "background:#999999;}"
            "QPushButton:pressed{"
            "background:#8bd6f3;}"
            "QLabel{"
            "background:rgb(255, 255, 255);"
            "border:1px solid #8bd6f3;"
            "border-radius:5px;}";
    setNormalstyle(m_strNormalStyle);
    initUI();
}

CPathEdit::~CPathEdit()
{

}

void CPathEdit::setTextSize(int nSize)
{
    m_nLenth = nSize;
}

int CPathEdit::getTextSize()
{
    return m_nLenth;
}

void CPathEdit::setBrowserButtonHeight(int nHeight)
{
    m_pbtnBrowser->setFixedHeight(nHeight);
}

void CPathEdit::updateBrowserState()
{
    m_pbtnBrowser->setFixedHeight(this->height()-contentsMargins().top() - contentsMargins().bottom()
                                  - 2);
}

void CPathEdit::setBrowserObjectName(QString objectName)
{
    m_strBroserObject = objectName;
    m_pbtnBrowser->setObjectName(objectName);

}

QString CPathEdit::getBrowserObjectName()
{
    return m_strBroserObject;
}

void CPathEdit::setLineEditObjectName(QString objectName)
{
    m_strLineEditObject = objectName;
    m_pwndLineEdit->setObjectName(objectName);
}

QString CPathEdit::getLineEditObjectName()
{
    return m_strLineEditObject;
}

void CPathEdit::setMouseHoverStyle(QString styleSheet)
{
    m_strHoverStyle = styleSheet;
}

void CPathEdit::setMouseFocusStyle(QString styleSheet)
{
    m_strFocusStyle = styleSheet;
}

void CPathEdit::setNormalstyle(QString styleSheet)
{
    m_strNormalStyle = styleSheet;
    setStyleSheet(m_strNormalStyle);
}

void CPathEdit::setPlaceholderText(QString strText)
{
    m_strPlaceholderText = strText;
    m_pwndLineEdit->setPlaceholderText(strText);
}

QString CPathEdit::getPlaceHolderText()
{
    return m_strPlaceholderText;
}

void CPathEdit::setReadOnly(bool b)
{
    m_pwndLineEdit->setReadOnly(b);
}

bool CPathEdit::isReadOnly()
{
    return m_pwndLineEdit->isReadOnly();
}

QString CPathEdit::getPath()
{
    return m_pwndLineEdit->text();
}

void CPathEdit::setPath(QString strPath)
{
    m_pwndLineEdit->setText(strPath);
}

void CPathEdit::setWarinPixmap(QString pixmap)
{
    m_strWarinPixmap = pixmap;
}

QString CPathEdit::getWarinPixmap()
{
    return m_strWarinPixmap;
}

void CPathEdit::setFilter(QString filter)
{
    m_strFilter = filter;
}

QString CPathEdit::getFilter()
{
    return m_strFilter;
}

void CPathEdit::clearText()
{
    m_pwndLineEdit->clear();
}

void CPathEdit::enterEvent(QEvent *event)
{
    if(m_pwndLineEdit->hasFocus() == false)
    {
        setStyleSheet(m_strHoverStyle);
    }
    QLabel::enterEvent(event);
}

void CPathEdit::leaveEvent(QEvent *event)
{
    if(m_pwndLineEdit->hasFocus() == false)
    {
        setStyleSheet(m_strNormalStyle);
    }
    QLabel::leaveEvent(event);
}

void CPathEdit::initUI()
{
    m_pwndLineEdit = new CLineEdit(this);
    m_pwndLineEdit->setReadOnly(true);
    m_pwndLineEdit->setFocusPolicy(Qt::NoFocus);
    setContentsMargins(1, 1, 2, 1);

    m_pbtnBrowser = new QPushButton(this);
    m_pbtnBrowser->setFocusPolicy(Qt::NoFocus);
    m_pbtnBrowser->setText(QString::fromLocal8Bit("浏 览"));
    m_pbtnBrowser->setFixedWidth(52);
    //m_pbtnBrowser->setFixedSize(52, 27);

    QHBoxLayout *phblMain = new QHBoxLayout();
    phblMain->setContentsMargins(0, 0, 0, 0);
    phblMain->setSpacing(1);

    phblMain->addWidget(m_pwndLineEdit);
    phblMain->addWidget(m_pbtnBrowser);
    this->setLayout(phblMain);

    connect(m_pbtnBrowser, SIGNAL(clicked()), this, SLOT(sltBrowserSavePath()));
    connect(m_pwndLineEdit, SIGNAL(textChanged(QString)), this, SLOT(sltCheckPathLength(QString)));
    connect(m_pwndLineEdit, SIGNAL(sigFocusIn()), this, SLOT(sltSetFocusStyle()));
    connect(m_pwndLineEdit, SIGNAL(sigFocusOut()), this, SLOT(sltSetNorStyle()));
}

void CPathEdit::sltBrowserSavePath()
{
    QString dir;
    if(m_nFileDlgFlag == FILE)
    {
#if defined Q_OS_WIN32
        dir = QFileDialog::getOpenFileName(NULL, QString::fromLocal8Bit("选择文件"),
                    QDir::homePath(), m_strFilter,0,
                    QFileDialog::DontUseNativeDialog);
#else
         dir = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择文件"),
                                                         QDir::homePath(), m_strFilter);
#endif
    }
    else
    {
        QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    #if defined Q_OS_WIN32
        options |= QFileDialog::DontUseNativeDialog;
    #endif

        dir = QFileDialog::getExistingDirectory(NULL, QString::fromLocal8Bit("选择路径"),
                                                        QDir::homePath(),
                                                        options);
    }

    if(dir.isEmpty() == false)
    {
        dir = QDir::toNativeSeparators(dir);
    }
    m_pwndLineEdit->setText(dir);
}

/*
*  检测输入或者选择路径长度（按照字节数计算）有效性
*/
void CPathEdit::sltCheckPathLength(QString strText)
{
    int nCurPos = m_pwndLineEdit->cursorPosition();
    emit sigInput();
    //如果长度为-1，未设置长度限制
    if(m_nLenth == -1)
    {
        m_pwndLineEdit->setText(strText);
		m_pwndLineEdit->setCursorPosition(nCurPos);
        emit sigSelectedPath(strText);
        return;
    }

    //根据长度限制，检测输入内容
    int nSize = strText.toUtf8().size();
    if(nSize <= m_nLenth)
    {
        m_strPath = strText;
    }
    else
    {
        CMessageWidget *msg = new CMessageWidget(this);
        msg->setContentsMargins(1, 1, 1, 1);
        msg->setCloseBtnPixName(QString(":/tip/icon/titlebar/ID_CLOSED_TITLEBAR"));
        msg->setCancelBtnVisible(false);
        msg->setTitleText(QString::fromLocal8Bit("提示"));
        //操作失败！路径超长，请重新选择
        msg->setMessageInfo(m_strWarinPixmap, QString::fromLocal8Bit("操作失败！"), QString::fromLocal8Bit("路径超长，请重新选择!"));
        msg->exec();
    }
    m_pwndLineEdit->setText(m_strPath);
    m_pwndLineEdit->setCursorPosition(nCurPos);
    emit sigSelectedPath(m_strPath);
}

void CPathEdit::sltSetFocusStyle()
{
    if(m_pwndLineEdit->isReadOnly() == true)
    {
        return;
    }
    setStyleSheet(m_strFocusStyle);
}

void CPathEdit::sltSetNorStyle()
{
    setStyleSheet(m_strNormalStyle);
}


/*
*  自定义QLineEdit
*  重写QLineEdit::focusInEvent事件，在鼠标进入焦点时，向父窗体发送进入编辑状态信号，用于设置父窗体鼠标状态的显示
*  重新QLineEdit::focusOutEvent事件，在鼠标离开焦点是，向父窗体发送退出编辑状态信号，用于设置父窗体鼠标状态的显示
*/
CLineEdit::CLineEdit(QWidget *parent)
    :QLineEdit(parent)
{

}

CLineEdit::~CLineEdit()
{

}

void CLineEdit::focusInEvent(QFocusEvent *event)
{
    emit sigFocusIn();
    QLineEdit::focusInEvent(event);
}

void CLineEdit::focusOutEvent(QFocusEvent *event)
{
    emit sigFocusOut();
    QLineEdit::focusOutEvent(event);
}
