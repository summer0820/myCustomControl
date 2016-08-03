#include "../CStatusBar.h"

CStatusBar::CStatusBar(QWidget *parent)
    :QLabel(parent)
{
    setFixedHeight(30);
    this->setStyleSheet("border-top:1px solid red;\
                        background-color:white;");

}

CStatusBar::~CStatusBar()
{

}

void CStatusBar::setOnlineState(QString state)
{

}

void CStatusBar::setRegisterState(QString state)
{

}

void CStatusBar::initWidget()
{
    m_plblOnline = new QLabel(this);
}
