#ifndef CMAINFRAME_H
#define CMAINFRAME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHash>
#include <QToolButton>

class CPageTreeWidget;
class CNavigationToolBar;
class CSwitchPageToolBar;

#include "TItemStruct.h"

class CMainFrame : public QWidget
{
    Q_OBJECT
public:
    explicit CMainFrame(QWidget *parent = NULL);
    ~CMainFrame();

    void                showFirstItem();
    void                setCurrentItem(QString strKey);

    void                setLeftTreeVisible(bool bShow);
    void                setNavigationBarVisible(bool bShow);
    void                setSwitchPageBarVisible(bool bShow);

    //navigation bar
    void                setResearchVisible(bool bShow);
    void                setwAddRemoveVisible(bool bShow);
    void                setChoiceTimeVisible(bool bShow);
    void                setDisplayModeVisible(bool bShow);

    void                resetChiceTime();
    void                clearGotoPageNum();
    void                clearResearch();

    void                setNavWidget(QWidget *pCustomWidget);

    /*
     * 在导航条上插入按钮
     * option 插入选项 0:前面插入按钮 1:后面插入按钮（默认）
     */
    void                insertNavToolButton(QToolButton *pToolButton, int option = 1);

    QToolButton*        getNavAddButton();
    QToolButton*        getNavRemoveButton();

    //
    void                resetSwitchPageBar();
    /*
     * 设置总记录的条数
     */
    void                setRecordNumber(int nCount);

    /*
     *获取当前要显示的页码，以及每页要显示的数量， 参数为输入参数
     */
    void                getCurrentPage(int &nIndex,int &nCount);

    /*
     *获取当前页签下 下拉框中选定的时间
     */
    QList<int>          getCurrentTime();

    void                setSwitchPageEnable(bool bEnable);



    void                installLeftTreeWidget(QString strConfigFile);
    QStringList         getTableHeadDataByKey(QString strKey);

    void                setLocation(QStringList lstLocaltion);


    void                setContentWidget(QWidget *pContent);

protected:
    void                paintEvent(QPaintEvent *event);

private:
    void                initSate();
    QStringList         getLocationPath(QString strLocation);
    void                parseXML(QString strFilePath);

signals:
    /*
     * 指定的页签下 发生了翻页操作
     */
    void                sigGotoPage(QString strKey);

    /*
     * 左侧树页签被点击
     */
    void                sigTabItemClick(QString strKey);


    /*
     *指定的页签下 发生了时间段改变
     */
    void                sigTimeSelection(QString strKey);

    void                sigAdd();
    void                sigRemove();
    void                sigShowList();
    void                sigShowThumbnail();    
    void                sigResearch(QString strKey);



private slots:
    void                sltTabItemClicked(QString strKey);
    void                sltGotoPage(int nPageNumber);
    void                sltTimeSelection(QString strTime);


private:
    QHBoxLayout                 *m_pMainLayout;
    QVBoxLayout                 *m_pContentLayout;

    CPageTreeWidget             *m_pLeftTree;
    CNavigationToolBar          *m_pNavigationBar;
    CSwitchPageToolBar          *m_pSwitchPageBar;
    QWidget                     *m_pContetWidget;

    QList<TItemData>            m_lstItemData;
    QHash<QString,TItemSate>    m_mapItemState;
    QString                     m_strCurrentKey;

    bool                        m_bShowFirst;
};

#endif // CMAINFRAME_H
