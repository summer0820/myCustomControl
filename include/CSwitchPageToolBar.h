#ifndef CWITCHPAGETOOLBAR_H
#define CWITCHPAGETOOLBAR_H

#include "stdafx.h"



class CSwitchPageToolBar : public QWidget
{
    Q_OBJECT
public:
     explicit CSwitchPageToolBar(QWidget *parent = NULL);
    ~CSwitchPageToolBar();

    void                setTotalRecordNumber(int nTotal);
    void                setCurrentPage(int nCur);
    int                 getCurrentPage();

    void                clearGoPageNum();

    void                setSwitchPageEnable(bool bEnable);

protected:
    void                paintEvent(QPaintEvent *event);

private:    
    void                initBtnState();
    void                initStyle();
    bool                isLeft(int nIndex);
    bool                isCenter(int nIndex);
    bool                isRight(int nIndex);
    void                setNumberButtonStyle();
    int                 getPageRecordCount(int nPage);


private slots:
    void                sltFirstPageClick();
    void                sltPrePageClick();
    void                sltFirstNumberClick();
    void                sltSecondNumberClick();
    void                sltThirdNumberClick();
    void                sltNextPageClick();
    void                sltLastPageClick();

    void                sltGotoPageClick();

signals:
    void                sigGotoPage(int nPageNumber);


private:
    QHBoxLayout         *m_pMainLayout;

    QPushButton         *m_pFirstPageButton;
    QPushButton         *m_pPrePageButton;
    QPushButton         *m_pFirstNumberButton;
    QPushButton         *m_pSecondNumberButton;
    QPushButton         *m_pThirdNumberButton;
    QPushButton         *m_pNextPageButton;
    QPushButton         *m_pLastPageButton;

    QLabel              *m_pGotoLabel;
    QLineEdit           *m_pNumberEditor;
    QPushButton         *m_pGotoButton;


    QLabel              *m_pFirstRecordLabel;
    QLabel              *m_pCurRecordLabel;
    QLabel              *m_pMidRecordLabel;
    QLabel              *m_pTotalRecordLabel;
    QLabel              *m_pLastRecordLabel;

    int                 m_nTotalRecord;    
    int                 m_nCurrentPageNumber;
    int                 m_nTotalPageNumber;


    QString             m_strDefaultStyle;
    QString             m_strCheckedStyle;
};


#endif // CNAVIGATIONBAR_H
