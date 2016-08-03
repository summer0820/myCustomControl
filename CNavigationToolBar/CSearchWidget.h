#ifndef CSEARCHWIDGET_H
#define CSEARCHWIDGET_H

#include "stdafx.h"

class CSearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CSearchWidget(QWidget *parent = NULL);
    ~CSearchWidget();

    void                clearString();

signals:
    void                sigResearch(QString strKey);

private slots:
    void                sltOrignalSearchClicked();
    void                sltSearchClicked();

    void                sltCheckInput(QString str);

private:
    QHBoxLayout         *m_pMainLayout;
    //QPushButton         *m_pBtnOrignalSearch;
    QLineEdit           *m_pSearchEditor;
    QPushButton         *m_pBtnSearch;

    QString              m_strOldText;
};

#endif // CSEARCHWIDGET_H
