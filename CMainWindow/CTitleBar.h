#ifndef CTITLEBAR
#define CTITLEBAR

#include "stdafx.h"

class CPushButton;

class CTitleBar : public QLabel
{
    Q_OBJECT
public:
    explicit CTitleBar(QWidget *parent = 0);

    void  setMinButtonVisible(bool b);
    void  setMaxButtonVisible(bool b);
    void  setCloseButtonVisible(bool b);

    void  setMaxButtonIcon(QString iconName);
    void  setMinButtonIcon(QString iconName);
    void  setCloseButtonIcon(QString iconName);

    void  setTitleText(QString title);
    void  setTitlePixmap(QPixmap strPixmap);
    void  setTitleStyleSheet(QString style);

    void  setCloseButtonEnable(bool bEnabled);

private:
    QLabel      *m_plblTitle;
    QLabel      *m_plblTitlePixmap;
    CPushButton *m_pbtnMax;
    CPushButton *m_pbtnMin;
    CPushButton *m_pbtnClose;

signals:
    void    sigShowMin();
    void    sigClose();
    void    sigshowMax();
};

#endif // CTITLEBAR

