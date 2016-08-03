#ifndef CSTATUSBAR
#define CSTATUSBAR

#include "stdafx.h"

class CStatusBar : public QLabel
{
    Q_OBJECT
public:
    explicit CStatusBar(QWidget *parent = 0);
    ~CStatusBar();

    void     setOnlineState(QString state);
    void     setRegisterState(QString state);

private:
    QLabel  *m_plblOnline;

    void    initWidget();
};

#endif // CSTATUSBAR

