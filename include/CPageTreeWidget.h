#ifndef CPAGETREEWIDGET_H
#define CPAGETREEWIDGET_H

#include "stdafx.h"

#include "TItemStruct.h"

class CPageTreeWidgetItem;

class CPageTreeWidget : public QWidget
{
    Q_OBJECT
public:
    CPageTreeWidget(QWidget *parent = NULL);
    ~CPageTreeWidget();

    void                            showFirstItem();

    void                            setItemDataList(QList<TItemData> lstItemData);

    QStringList                     getFullPathByKey(QString strKey);

    void                            setCurrentClicked(QString strKey);

protected:
    void                            paintEvent(QPaintEvent *event);

private:
    void                            installTreeWidget();
    CPageTreeWidgetItem             *findParentByID(int nParentID);
    void                            updatePressState(QString strKey);
    QString                         findFirstItemKey();

private slots:
    void                            sltItemClick(QString strKey);

signals:
    void                            sigItemClick(QString strKey);

private:
    QVBoxLayout                     *m_pMainLayout;

    QList<TItemData>                m_lstItemData;
    QList<CPageTreeWidgetItem *>    m_lstTreeItem;


};

#endif // CPAGETREEWIDGET_H
