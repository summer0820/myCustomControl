#ifndef CFILESYSTEMMODEL_H
#define CFILESYSTEMMODEL_H



#include "stdafx.h"

class CFileSystemModel : public QDirModel
{
    Q_OBJECT
public:
    CFileSystemModel();

public:
    bool                isChecked(const QModelIndex &index);
    QStringList         getCheckedPath();
    void                setTreeView(QTreeView *pTreeView);
    void                clearSelectedPath();

    Qt::ItemFlags       flags(const QModelIndex &index) const;
    QVariant            data(const QModelIndex &index, int role) const;
    bool                setData(const QModelIndex &index, const QVariant &value, int role);
    int                 columnCount(const QModelIndex &parent = QModelIndex()) const;

public:
    void                recursiveCheckChild(const QModelIndex &index, const QVariant &value);
    void                recursiveCheckParent(const QModelIndex &index, const QVariant &value);

    void                recursiveUncheckParent(const QModelIndex &index, const QVariant &value);
    void                recursiveUncheckChild(const QModelIndex &index, const QVariant &value);


private:
    QSet<QPersistentModelIndex> checkedIndexes;
    QTreeView       *m_pTreeView;
};



#endif // CFILESYSTEMMODEL_H
