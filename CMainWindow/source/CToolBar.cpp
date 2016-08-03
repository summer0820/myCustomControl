#include "../CToolBar.h"

#include "CToolButton.h"
#include "CClickLabel.h"

CToolBar::CToolBar(QWidget *parent, QString userFlag)
    :QWidget(parent)
    ,m_strCurUser(userFlag)
{
    setContentsMargins(0, 0, 0, 0);
    m_phblMain = new QHBoxLayout();
    m_phblMain->setContentsMargins(10, 0, 10, 0);
    m_phblMain->setSpacing(10);
    m_phblMain->setAlignment(Qt::AlignLeft);
    setLayout(m_phblMain);

    //initLogoWidget();
    //m_phblMain->addWidget(m_pwndLogo);
    setFixedHeight(116);
}

CToolBar::~CToolBar()
{

}

void CToolBar::setCurUser(QString strUserFlag)
{
    m_strCurUser = strUserFlag;
}

void CToolBar::readToolBarInfo(QString xmlFileName)
{
    if(xmlFileName.isEmpty())
    {
        return;
    }
    QFile file(xmlFileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(NULL, QString("title"), QString("open error!"));
        return;
    }
    m_listButton.clear();
    QDomDocument document;
    QString error;
    int row = 0, column = 0;
    if(!document.setContent(&file, false, &error, &row, &column))
    {
        QMessageBox::information(NULL, QString("title"), QString("parse file failed at line row and column") + QString::number(row, 10) + QString(",") + QString::number(column, 10));
        return;
    }

    if(document.isNull())
    {
        QMessageBox::information(NULL, QString("title"), QString("document is null!"));

        return;
    }
    QDomElement root = document.documentElement();

    QDomNodeList list = root.childNodes();
    int count = list.count();
    for(int i=0; i < count; i++)
    {
        QDomNode dom_node = list.item(i);
        QDomElement element = dom_node.toElement();
        QString strUserFlag = element.attributeNode("flag").value();
        if(strUserFlag == m_strCurUser)
        {
            QDomNodeList btnList = element.childNodes();
            int nbtnCount = btnList.count();
            m_pbtnGroup = new QButtonGroup(this);
            for(int nbtnIndex = 0; nbtnIndex < nbtnCount; nbtnIndex++)
            {
                QDomNode btnDomNode = btnList.item(nbtnIndex);
                QDomElement btnElement = btnDomNode.toElement();
                QString btnID = btnElement.attributeNode("id").value();
                QString btnName = btnElement.attributeNode("name").value();
                QString btnIconname = btnElement.attributeNode("iconname").value();
                QString btnObjectname = (btnElement.attributeNode("objectname").value());
                CToolButton *btnTool = new CToolButton(btnIconname, this);
                btnTool->setID(btnID);
                btnTool->setObjectName(btnObjectname);
                btnTool->setText(btnName);
                btnTool->setCheckable(true);
				btnTool->setMousePress(true);
                m_phblMain->addWidget(btnTool);
                m_pbtnGroup->addButton(btnTool);
                m_listButton.append(btnTool);
            }
            connect(m_pbtnGroup, SIGNAL(buttonReleased(int)), this, SLOT(sltBtnClicked(int)));
            break;
        }
    }
    file.close();
}

void CToolBar::setCheckedButton(QString strKey)
{
    if(m_listButton.isEmpty())
    {
       return;
    }
    for(int i = 0; i < m_listButton.count(); i++)
    {
        CToolButton *pToolButton = m_listButton.at(i);
        QString strID = pToolButton->getID();
        if(strID == strKey)
        {
            pToolButton->setCheckable(true);
            pToolButton->setChecked(true);
        }
    }
}

void CToolBar::setLicenseOnly(bool b)
{
    if(m_listButton.isEmpty() || m_strCurUser != "sysuser")
    {
        return;
    }

    for(int i = 0; i < m_listButton.count(); i++)
    {
        CToolButton *pToolButton = m_listButton.at(i);
        QString strID = pToolButton->getID();
        if(b == true)
        {
            if(strID == "license")
            {
                pToolButton->show();
                pToolButton->setCheckable(true);
                pToolButton->setChecked(true);
            }
            else
            {
                pToolButton->hide();
            }
        }
        else
        {
           pToolButton->show();
        }
    }

    /*
    if(m_listButton.isEmpty() || m_strCurUser != "sysuser")
    {
        return;
    }
    for(int i = 0; i < m_listButton.count(); i++)
    {
        CToolButton *pToolButton = m_listButton.at(i);
        QString strID = pToolButton->getID();
        if(b == true)
        {
            if(strID == "license")
            {
                pToolButton->show();
            }
            else
            {
                pToolButton->hide();
            }
        }
        else
        {
           pToolButton->show();
        }
    }
    */
}

void CToolBar::setBackgroundPixmap(QPixmap pix)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), pix);
}

void CToolBar::initLogoWidget()
{
    m_pwndLogo = new QWidget(this);
    m_pwndLogo->setContentsMargins(0, 0, 0, 0);
    m_plblLogo = new CClickLabel(m_pwndLogo);
    m_plblLogo->setAlignment(Qt::AlignCenter);

    m_plblWindowTitle = new CClickLabel(m_pwndLogo);
    m_plblWindowTitle->setText(QString::fromLocal8Bit("[白细胞]可信免疫系统"));
    m_plblWindowTitle->setWordWrap(false);
    m_plblWindowTitle->setStyleSheet("color:#ffffff;"
                                     "font: 12px '汉仪综艺体简';");

    m_plblVersion = new CClickLabel(m_pwndLogo);
    m_plblVersion->setObjectName("versiontext");
    m_plblVersion->setFixedHeight(15);
    m_plblVersion->setAlignment(Qt::AlignCenter);
    m_plblVersion->setWordWrap(false);
    m_plblVersion->setText(QString::fromLocal8Bit("目前版本:"));

    QVBoxLayout *pvblLogo = new QVBoxLayout();
    pvblLogo->setContentsMargins(0, 0, 0, 0);
    pvblLogo->setSpacing(5);
    pvblLogo->addWidget(m_plblLogo);
    pvblLogo->addWidget(m_plblWindowTitle);
    pvblLogo->addWidget(m_plblVersion);
    m_pwndLogo->setLayout(pvblLogo);

    connect(m_plblLogo, SIGNAL(clicked()), this, SLOT(sltLogoClicked()));
    connect(m_plblVersion, SIGNAL(clicked()), this, SLOT(sltLogoClicked()));
    connect(m_plblWindowTitle, SIGNAL(clicked()), this, SLOT(sltLogoClicked()));
}

void CToolBar::sltBtnClicked(int nButton)
{
    CToolButton *pButton = (CToolButton*)m_pbtnGroup->button(nButton);
    pButton->setCheckable(true);
    pButton->setChecked(true);
    QString strID = pButton->getID();
    emit sigClicked(strID);
}

void CToolBar::sltLogoClicked()
{
    for(int i = 0; i < m_listButton.count(); i++)
    {
        CToolButton *pToolButton = m_listButton.at(i);
        if(pToolButton->isChecked() == true)
        {
            pToolButton->setCheckable(false);
            pToolButton->update();
        }
    }
    emit sigLogoClicked();
}
