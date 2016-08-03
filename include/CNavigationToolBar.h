#ifndef CNAVIGATIONTOOLBAR_H
#define CNAVIGATIONTOOLBAR_H

#include "stdafx.h"


class CLocationBar;
class CSearchWidget;

class CNavigationToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit CNavigationToolBar(QWidget *parent = NULL);
    ~CNavigationToolBar();

    void                    setTitle(QStringList lstTitle);

    void                    setShowResearch(bool bShow);
    void                    setShowAddRemove(bool bShow);
    void                    setShowChoiceTime(bool bShow);
    void                    setShowDisplayMode(bool bShow);

    void                    setChoiceTimeCurrentIndex(QString strData);

    void                    setWidget(QWidget *pCustomWidget);
    void                    insertToolButton(QToolButton *pToolButton,int opt = 1);

    QToolButton*            getAddButton();
    QToolButton*            getRemoveButton();

    void                    resetChiceTime();
    void                    clearResearch();

protected:
    void                    paintEvent(QPaintEvent *event);

private:
    void                    updateShowState();
    void                    initChoiceTimeUI();
    void                    initDisplayButton();
    void                    initAddRemoveButton();

signals:
    void                    sigAdd();
    void                    sigRemove();
    void                    sigShowList();
    void                    sigShowThumbnail();
    void                    sigTimeSelection(QString strTime);
    void                    sigResearch(QString strKey);       


private slots:
    void                    sltListDisplayClicked();
    void                    sltThumbnailDisplayClicked();
    void                    sltCurrentCMBItem(int nIndex);


private:
    QHBoxLayout             *m_pMainLayout;
    CLocationBar            *m_pLocationBar;

    QPushButton             *m_pBtnThumbnail;
    QPushButton             *m_pBtnList;
    QIcon                   *m_pIconListSelected;
    QIcon                   *m_pIconListNormal;
    QIcon                   *m_pIconThumbnailSelected;
    QIcon                   *m_pIconThumbnailNormal;

    QToolButton             *m_pBtnAdd;
    QToolButton             *m_pBtnRemove;


    QLabel                  *m_pLabelChoiceTime;
    QComboBox               *m_pComboChoiceTime;

    CSearchWidget             *m_pSearchWidget;

    QList<QWidget *>        m_lstHeadAddedWidget;
    QList<QWidget *>        m_lstTailAddedWidget;
    QWidget                 *m_pCustomWidget;

    bool                    m_bIsShowDisplayMode;
    bool                    m_bIsShowSearchWidget;
    bool                    m_bIsShowChoiceTime;
    bool                    m_bIsShowAddRemoveWidget;

    QFont                   m_textFont;
};

#endif // CNAVIGATIONTOOLBAR_H
