#include "../../include/CMessageWidget.h"
#include "../../include/CPushButton.h"
#include "../../include/CPixmapLabel.h"

#include <QStyleOption>
#include <QtCore/qmath.h>
#include <QBitmap>

CMessageWidget::CMessageWidget(QWidget *parent, int nFlag, bool bDefault)
    :QDialog(parent)
{
    m_pwndCenteWidget = NULL;
    m_pwndScrollArea = NULL;
    m_plblContent = NULL;
    m_plblBottomSpacer = NULL;
    m_bDefault = bDefault;
    m_nFlag = nFlag;
    m_pwndParent = parent;
    m_nShadowWidth = 5;
    m_nRadius = 0;
    m_bIsRoundBorder = true;
    setFixedWidth(500);

    setContentsMargins(0, 0, 0, 0);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setAttribute(Qt::WA_TranslucentBackground);
    m_bOkVisible = true;
    m_bCancelVisible = true;


    initTitleBar();

    m_pvblMain = new QVBoxLayout();
    m_pvblMain->setAlignment(Qt::AlignTop);
    m_pvblMain->setContentsMargins(m_nShadowWidth, m_nShadowWidth, m_nShadowWidth, m_nShadowWidth);
    m_pvblMain->setSpacing(0);
    m_ptPress = false;

    m_pBtnWidget = new QWidget(this);
    QHBoxLayout *phblActionBtn = new QHBoxLayout();
    phblActionBtn->setContentsMargins(0, 0, 0, 20);
    phblActionBtn->setSpacing(30);
    phblActionBtn->setAlignment(Qt::AlignCenter);

    m_pbtnLeft = new QPushButton(m_pBtnWidget);
    m_pbtnLeft->setFocusPolicy(Qt::NoFocus);
    m_pbtnLeft->setObjectName("messageboxOk");
    m_pbtnLeft->setStyleSheet("QPushButton#messageboxOk{\
                              background-color:#f0f0f0;\
                              border-radius:5px;\
                              border: 2px solid #8bd6f3;\
                              font-size: 12px;\
                              color:#333333;\
                            }\
                            QPushButton#messageboxOk:hover{\
                              background-color:#cde7ff;\
                            }"
                            "QPushButton#messageboxOk:pressed{"
                            "background-color: #dadada;}");
    m_pbtnLeft->setFixedSize(100,25);
    m_pbtnLeft->setText(QString::fromLocal8Bit("确定"));
    m_pbtnLeft->setAutoDefault(false);
    m_pbtnLeft->setDefault(false);
    m_pbtnLeft->setFocusPolicy(Qt::NoFocus);

    m_pbtnRight = new QPushButton(m_pBtnWidget);
    m_pbtnRight->setFocusPolicy(Qt::NoFocus);
    m_pbtnRight->setAutoDefault(false);
    m_pbtnRight->setDefault(false);
    m_pbtnRight->setFocusPolicy(Qt::NoFocus);
    m_pbtnRight->setFixedSize(100,25);
    m_pbtnRight->setObjectName("messageboxCancel");
    m_pbtnRight->setStyleSheet("QPushButton#messageboxCancel{\
                               background-color:#f0f0f0;\
                               border-radius:5px;\
                               border: none;\
                               font-size: 12px;\
                               color:#333333;\
                           }\
                           QPushButton#messageboxCancel:hover{\
                               background-color: #cde7ff;\
                           }\
                           QPushButton#messageboxCancel:pressed{\
                               background:#dadada;\
                           }");
    m_pbtnRight->setText(QString::fromLocal8Bit("取消"));

    phblActionBtn->addWidget(m_pbtnLeft);
    phblActionBtn->addWidget(m_pbtnRight);
    m_lstActionBtn<<m_pbtnLeft<<m_pbtnRight;
    m_pBtnWidget->setLayout(phblActionBtn);

    this->setLayout(m_pvblMain);
    setMessageFlag(m_nFlag);

    connect(m_pbtnLeft, SIGNAL(clicked()), this, SLOT(accept()));
    connect(m_pbtnRight, SIGNAL(clicked()), this, SLOT(reject()));
    connect(m_pbtnLeft, SIGNAL(clicked()), this, SIGNAL(sigOK()));
    connect(m_pbtnRight, SIGNAL(clicked()), this, SIGNAL(sigCancle()));
}


CMessageWidget::~CMessageWidget()
{

}

void CMessageWidget::setTitleText(QString strTitle)
{
    m_plblTitleText->setText(strTitle);
}

QString CMessageWidget::getTitleText()
{
    return m_plblTitleText->text();
}

void CMessageWidget::setTitleLogo(QPixmap pix)
{
    m_plblTitleLogo->setPixmap(pix);
}

const QPixmap* CMessageWidget::getTitleLogo()
{
    return m_plblTitleLogo->pixmap();
}

void CMessageWidget::setContentWidget(QWidget *widget)
{
    m_pwndCenteWidget = widget;
    if(m_nFlag == INFO_ERROR)
    {
        m_pwndScrollArea->setWidget(widget);
    }
    else
    {
        QHBoxLayout *phblMain = new QHBoxLayout();
        phblMain->setContentsMargins(0, 0, 0, 0);
        phblMain->setAlignment(Qt::AlignTop);
        phblMain->setSpacing(0);
        phblMain->addWidget(widget);

        m_plblContent->setLayout(phblMain);
        m_plblContent->adjustSize();
    }
}

QWidget *CMessageWidget::getContentWidget()
{
    return m_pwndCenteWidget;
}

QList<QPushButton *> CMessageWidget::getActionButtons()
{
    return m_lstActionBtn;
}

//获取确定按钮
QPushButton *CMessageWidget::getOKBtn()
{
    return m_pbtnLeft;
}

//获取取消按钮
QPushButton *CMessageWidget::getCancelBtn()
{
    return m_pbtnRight;
}

void CMessageWidget::setCancelBtnVisible(bool b)
{
    m_bCancelVisible = b;
    m_pbtnRight->setVisible(b);

    if(m_bCancelVisible == false && m_bOkVisible == false)
    {
        m_pBtnWidget->hide();
    }
    else
    {
        m_pBtnWidget->show();
    }
}

void CMessageWidget::setOKBtnVisible(bool b)
{
    m_bOkVisible = b;
    m_pbtnLeft->setVisible(b);

    if(m_bCancelVisible == false && m_bOkVisible == false)
    {
        m_pBtnWidget->hide();
    }
    else
    {
        m_pBtnWidget->show();
    }
}

void CMessageWidget::setCloseBtnPixName(QString pix)
{
    m_pbtnClose->setPixName(pix);
}

void CMessageWidget::setMinBtnPixName(QString pix)
{
    m_pbtnMin->show();
    m_pbtnMin->setPixName(pix);
}

void CMessageWidget::setMessageInfo(QString infoPixmap, QString strInfo)
{
    //qDebug()<<"strInfo = "<<strInfo;
    QWidget *widgetContent = new QWidget(this);
    widgetContent->setMinimumWidth(500 - this->contentsMargins().left() - this->contentsMargins().right());
    widgetContent->setMinimumHeight(80);
    widgetContent->setContentsMargins(20, 60, 20, 0);
    QHBoxLayout *phblText = new QHBoxLayout();
    phblText->setContentsMargins(0, 0, 0, 0);
    phblText->setAlignment(Qt::AlignHCenter);

    /*
    QLabel *plblText = new QLabel(strInfo);
    plblText->setStyleSheet("QLabel{color:#333333;font:14px;}");
    plblText->setWordWrap(true);
    plblText->setAlignment(Qt::AlignCenter);
    plblText->adjustSize();
    if(infoPixmap.isEmpty() == false)
    {
       QLabel *plblTextPixmap = new QLabel(widgetContent);
       plblTextPixmap->setContentsMargins(0, 0, 0, 0);
       QPixmap pixmapInfo = QPixmap(infoPixmap);
       plblTextPixmap->setPixmap(pixmapInfo.scaled(QSize(24,24), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
       plblTextPixmap->adjustSize();
       phblText->addWidget(plblTextPixmap);
       phblText->addWidget(plblText);
       plblText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
       int nWidth = widgetContent->width() - plblTextPixmap->geometry().x() - plblTextPixmap->width();
       qDebug()<<"$$$$$$$$$$$ = "<<nWidth;
       plblText->setFixedWidth(nWidth);
       phblText->setAlignment(Qt::AlignCenter);
    }
    else
    {
        phblText->addWidget(plblText);
    }
    */
    QPixmap pixmapInfo = QPixmap(infoPixmap);
    CPixmapLabel *plblText = new CPixmapLabel(widgetContent,pixmapInfo,strInfo);
    plblText->setStyleSheet("QLabel{color:#333333;font:14px;}");
    plblText->setSpacing(10);

    //plblText->setLeftPixmap(pixmapInfo.scaled(QSize(24,24), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    //plblText->setShowText(strInfo);
    phblText->addWidget(plblText);
    widgetContent->setLayout(phblText);
    setContentWidget(widgetContent);
}

void CMessageWidget::setMessageError(QString strPixmap, QString strTitle, QStringList listError)
{
    QHBoxLayout *phblTitle = new QHBoxLayout();
    phblTitle->setContentsMargins(0, 0, 0, 0);
    phblTitle->setSpacing(2);
    phblTitle->setAlignment(Qt::AlignCenter);

    QLabel *plblTitleIcon = new QLabel(m_plblContent);
    plblTitleIcon->setPixmap(strPixmap);
    plblTitleIcon->adjustSize();

    QLabel *plblTitleText = new QLabel(m_plblContent);
    plblTitleText->setContentsMargins(0, 0, 0, 0);
    plblTitleText->setText(strTitle);
    plblTitleText->adjustSize();

    phblTitle->addWidget(plblTitleIcon);
    phblTitle->addWidget(plblTitleText);

    QTextEdit *pwndTextEdit = new QTextEdit(m_plblContent);
    pwndTextEdit->setContentsMargins(0, 0, 0, 0);
    pwndTextEdit->setFrameShape(QFrame::NoFrame);
    pwndTextEdit->setWordWrapMode(QTextOption::WrapAnywhere);
    pwndTextEdit->setStyleSheet("border:0px solid red;"
                                "font-size:12px;"
                                "color:#333333;");
    pwndTextEdit->setReadOnly(true);
    for(int i = 0; i < listError.count(); i++)
    {
        QString strText = listError.at(i);
        if(strText.isEmpty() == false)
        {
            //pwndTextEdit->setText(pwndTextEdit->toPlainText().append("\n").append(strText));
            pwndTextEdit->append(strText);
        }
    }
    pwndTextEdit->document()->adjustSize();
    int nDocHeight = pwndTextEdit->document()->size().rheight();
    int nHeight = nDocHeight + pwndTextEdit->frameWidth()*2;
    if(nHeight > 200)
    {
        nHeight = 200;
    }
    pwndTextEdit->setFixedHeight(nHeight);

    QVBoxLayout *pvblError = new QVBoxLayout();
    pvblError->setContentsMargins(20, 60, 20, 0);
    pvblError->setAlignment(Qt::AlignTop);
    pvblError->setSpacing(10);
    m_plblContent->setLayout(pvblError);

    pvblError->addLayout(phblTitle);
    pvblError->addWidget(pwndTextEdit);
}

void CMessageWidget::setMessageInfo(QString strPixmap, QString strInfo, QString strDeco)
{
    //qDebug()<<"strInfo = "<<strInfo;
    QWidget *widgetContent = new QWidget(this);
    widgetContent->setMinimumWidth(500 - this->contentsMargins().left() - this->contentsMargins().right());
    widgetContent->setMinimumHeight(80);
    widgetContent->setContentsMargins(20, 60, 20, 0);
    QVBoxLayout *pvblText = new QVBoxLayout();
    pvblText->setSpacing(10);
    pvblText->setContentsMargins(0, 0, 0, 0);
    //pvblText->setAlignment(Qt::AlignHCenter);
    QPixmap pixmapInfo = QPixmap(strPixmap);
    CPixmapLabel *plblText = new CPixmapLabel(widgetContent,pixmapInfo,strInfo);
    plblText->setStyleSheet("QLabel{color:#333333;font:14px;}");
    plblText->setSpacing(10);

    QLabel *plblDeco = new QLabel(strDeco, widgetContent);
    plblDeco->setStyleSheet("QLabel{color:#333333;font:14px;}");
    plblDeco->setContentsMargins(0, 0, 0, 0);
    plblDeco->setAlignment(Qt::AlignCenter);

    pvblText->addWidget(plblText, 1, Qt::AlignHCenter);
    pvblText->addWidget(plblDeco);

    //plblText->setLeftPixmap(pixmapInfo.scaled(QSize(24,24), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    //plblText->setShowText(strInfo);
    //phblText->addWidget(plblText);
    widgetContent->setLayout(pvblText);
    setContentWidget(widgetContent);
}


//setMessageFlag 需要在setcontentwidget之前调用
void CMessageWidget::setMessageFlag(int nFlag)
{
    switch(nFlag)
    {
    case INFO_WARNIG:
        break;
    case INFO_ERROR:
        this->setMaximumHeight(400);
        m_plblContent = new QWidget(this);
        m_plblContent->setContentsMargins(0, 0, 0, 0);
        m_pvblMain->addWidget(m_plblTitleBar);
        m_pvblMain->addWidget(m_plblContent);
        m_pvblMain->addSpacing(20);
        m_pvblMain->addWidget(m_pBtnWidget);
        break;
    case INFO_WIDGET:
        m_pBtnWidget->hide();
        m_plblContent = new QWidget(this);
        m_plblContent->setContentsMargins(0, 0, 0, 0);
        m_pvblMain->addWidget(m_plblTitleBar);
        m_pvblMain->addWidget(m_plblContent);
        break;
    case INFO_DIALOG:
    default:
        m_plblContent = new QWidget(this);
        m_pvblMain->addWidget(m_plblTitleBar);
        m_pvblMain->addWidget(m_plblContent);
        if(m_bDefault)
        {
            if(m_plblBottomSpacer == NULL)
            {
                m_plblBottomSpacer = new QLabel(this);
                m_plblBottomSpacer->setFixedHeight(40);
            }
            m_pvblMain->addWidget(m_plblBottomSpacer);
        }
        else
        {
            m_pvblMain->addStretch(1);
        }
        m_pvblMain->addWidget(m_pBtnWidget);
        break;
    }
}

void CMessageWidget::setBottomSpaceVisible(bool b)
{
    if(m_plblBottomSpacer != NULL)
    {
        m_plblBottomSpacer->setVisible(b);
    }
}

void CMessageWidget::setBorderIsRounded(bool b)
{
    m_bIsRoundBorder = b;
    if(b == false)
    {
        m_plblTitleBar->setStyleSheet("border-top-left-radius: 0px;"
                                      "border-top-right-radius: 0px;"
                                   "background-color:rgb(53,142,224);"
                                    );
    }
}

//初始化标题栏
void CMessageWidget::initTitleBar()
{
    m_plblTitleBar = new QLabel(this);
    m_plblTitleBar->setStyleSheet("border-top-left-radius: 5px;"
                                  "border-top-right-radius: 5px;"
                               "background-color:rgb(53,142,224);"
                                );

    QHBoxLayout *phblMain = new QHBoxLayout();
    phblMain->setContentsMargins(0, 0, 3, 0);
    phblMain->setSpacing(0);
    m_plblTitleBar->setLayout(phblMain);
    m_plblTitleBar->setFixedHeight(30);

    //初始化标题
    m_plblTitleText = new QLabel(m_plblTitleBar);
    m_plblTitleText->setText(QString::fromUtf8(""));
    m_plblTitleText->setObjectName("cmessagewidgetTitle");

    //初始化logo
    m_plblTitleLogo = new QLabel(m_plblTitleBar);
    m_plblTitleLogo->setPixmap(QPixmap(""));
    m_plblTitleLogo->setFixedSize(30, 30);

    m_pbtnClose = new CPushButton(m_plblTitleBar);
    m_pbtnClose->setAutoDefault(false);
    m_pbtnClose->setDefault(false);
    m_pbtnClose->setFocusPolicy(Qt::NoFocus);
    m_pbtnClose->setShortcut(Qt::CTRL + Qt::Key_W);

    m_pbtnMin = new CPushButton(m_plblTitleBar);
    m_pbtnMin->setAutoDefault(false);
    m_pbtnMin->setFocusPolicy(Qt::NoFocus);
    m_pbtnMin->setDefault(false);


    phblMain->addWidget(m_plblTitleLogo);
    phblMain->addWidget(m_plblTitleText);
    phblMain->addStretch();
    phblMain->addWidget(m_pbtnMin, 0, Qt::AlignRight);
    phblMain->addWidget(m_pbtnClose, 0, Qt::AlignRight);

    m_pbtnMin->hide();

    connect(m_pbtnClose, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_pbtnMin, SIGNAL(clicked()), this, SLOT(showMinimized()));

}

void CMessageWidget::showEvent(QShowEvent *e)
{    
    if(m_pwndParent == NULL)
    {
        QDesktopWidget *desktop = QApplication::desktop();
        int width = desktop->width();
        int height = desktop->height();
        int nMoveX = (width - this->width()) / 2;
        int nMoveY = (height - this->height()) / 2;
        move(nMoveX, nMoveY);
    }
    QDialog::showEvent(e);
}

void CMessageWidget::paintEvent(QPaintEvent *event)
{
    /*
    QPainter p(this);
    if(this->width() > 45 && this->height() > 45)
        drawWindowShadow(p);

    p.setPen(Qt::NoPen);
    p.setBrush(Qt::white);
    p.drawRect(QRect(18, 18, this->width() - 36,this->height() - 36));

    QWidget::paintEvent(event);
    */
    int nShadowWidth = 5;
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    if(m_bIsRoundBorder == true)
    {
        path.addRoundRect(nShadowWidth, nShadowWidth, this->width()- nShadowWidth * 2, this->height()- nShadowWidth*2, 5);
    }
    else
    {
        path.addRect(nShadowWidth, nShadowWidth, this->width()- nShadowWidth * 2, this->height()- nShadowWidth*2);
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 100);

    QList<int> lstAlpha;
    lstAlpha<<100<<70<<40<<30<<10;
    for(int i = 0; i < m_nShadowWidth; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        //path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
        if(m_bIsRoundBorder == true)
        {
            path.addRoundRect(m_nShadowWidth-i, m_nShadowWidth-i, this->width()-(m_nShadowWidth-i)*2, this->height()-(m_nShadowWidth-i)*2, 5);
        }
        else
        {
            path.addRect(m_nShadowWidth-i, m_nShadowWidth-i, this->width()-(m_nShadowWidth-i)*2, this->height()-(m_nShadowWidth-i)*2);
        }
        color.setAlpha(lstAlpha.at(i));
        painter.setPen(color);
        painter.drawPath(path);
    }
    QWidget::paintEvent(event);

}

void CMessageWidget::drawWindowShadow(QPainter &p)
{
    QList<QPixmap> pixmaps;
    pixmaps.append(QPixmap(":/tip/icon/shadow/shadow_left.png"));
    pixmaps.append(QPixmap(":/tip/icon/shadow/shadow_right.png"));
    pixmaps.append(QPixmap(":/tip/icon/shadow/shadow_top.png"));
    pixmaps.append(QPixmap(":/tip/icon/shadow/shadow_bottom.png"));
    pixmaps.append(QPixmap(":/tip/icon/shadow/shadow_corner1.png"));
    pixmaps.append(QPixmap(":/tip/icon/shadow/shadow_corner2.png"));
    pixmaps.append(QPixmap(":/tip/icon/shadow/shadow_corner3.png"));
    pixmaps.append(QPixmap(":/tip/icon/shadow/shadow_corner4.png"));

    p.drawPixmap(0, 0, 20, 20,pixmaps[4]);
    p.drawPixmap(this->width() - 20,0,20,20,pixmaps[5]);
    p.drawPixmap(0,this->height() - 20,20,20,pixmaps[6]);
    p.drawPixmap(this->width() - 20,this->height() - 20,20,20,pixmaps[7]);

    p.drawPixmap(0,20,20,this->height() - 40,pixmaps[0].scaled(20,this->height() - 40));
    p.drawPixmap(this->width() - 20,20,20,this->height() - 40,pixmaps[1].scaled(20,this->height() - 40));
    p.drawPixmap(20,0,this->width() - 40,20,pixmaps[2].scaled(this->width() - 40,20));
    p.drawPixmap(20,this->height() - 20,this->width() - 40,20,pixmaps[3].scaled(this->width() - 40,20));
}

void CMessageWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_ptPress = true;
    }
    m_ptMove = event->globalPos() - pos();
}

void CMessageWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_ptPress = false;
}

void CMessageWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_ptPress)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - m_ptMove);
    }
}

void CMessageWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        qDebug("CMessageWidget::keyPressEvent emit ok");
        if(m_pbtnLeft->isEnabled() && m_pbtnLeft->isVisible())
        {
            m_pbtnLeft->click();
        }
        emit sigReturnKeyPressed();
    }
}
