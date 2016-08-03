#ifndef CTREEMODEL_H
#define CTREEMODEL_H


#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "TItemStruct.h"

class CTreeItem;

class CTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit CTreeModel(QObject *parent = 0);
    ~CTreeModel();

    void                setItemDataList(QList<TItemData> lstItemData);
    TItemData           getItemDataByIndex(QModelIndex index);
    void                setXMLFile(QString strFilePath);
    QStringList         getFullPathByKey(QString strKey);



    QVariant            data(const QModelIndex &index, int role) const;
    Qt::ItemFlags       flags(const QModelIndex &index) const;
    QVariant            headerData(int section, Qt::Orientation orientation,
                                    int role = Qt::DisplayRole) const;
    QModelIndex         index(int row, int column,
                            const QModelIndex &parent = QModelIndex()) const;
    QModelIndex         parent(const QModelIndex &index) const;
    int                 rowCount(const QModelIndex &parent = QModelIndex()) const;
    int                 columnCount(const QModelIndex &parent = QModelIndex()) const;

private:
    void                setupModelData(CTreeItem *parent);
    CTreeItem           *item(CTreeItem *item, TItemData data);
    void                parseXML(QString strFilePath);

private:
    CTreeItem           *m_pRootItem;
    QList<TItemData>    m_lstItemData;
    QString             m_strAppPath;
};

#endif // CTREEMODEL_H
