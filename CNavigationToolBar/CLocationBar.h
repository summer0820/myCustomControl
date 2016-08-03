#ifndef CLOCATIONBAR_H
#define CLOCATIONBAR_H

#include "stdafx.h"

class CLocationBar : public QWidget
{
    Q_OBJECT
public:
    explicit CLocationBar(QWidget *parent = NULL);
    ~CLocationBar();

    void                setTitle(QStringList lstTitle);

private:
    void                updateUI();
    void                clearLabels();
    void                setlastLabelStyle(QLabel *pLabel);


private:
    QHBoxLayout         *m_pMainLayout;
    //QLabel              *m_pHomeIcon;

    QList<QWidget*>     m_lstLocationWidgets;

    QStringList         m_lstTitel;

    QFont               m_textFont;

};

#endif // CLOCATIONBAR_H
