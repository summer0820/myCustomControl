#ifndef CFILESYSTEMTREEWIDGET_H
#define CFILESYSTEMTREEWIDGET_H

#include "stdafx.h"

class CFileSystemModel;

class CFileSystemTreeWidget : public QTreeView
{
    Q_OBJECT
public:
    explicit CFileSystemTreeWidget(QWidget *parent = 0);
    ~CFileSystemTreeWidget();

    QStringList         getCheckedPath();

    QStringList         getOrignalFiles();

    QStringList         getSelectedFiles();
    void                clearSelectedPath();
    void                refresh();
    void                setMaxPathLength(int nLen);
    QStringList         getErrorFiles();

private:
    void initTreeView();    

private:
    CFileSystemModel        *m_pTreeModel;
    int                     m_nMaxLength;
    QStringList             m_lstErrorFiles;

private slots:
    void        sltExpanded(const QModelIndex &index);

};

#endif // CFILESYSTEMTREEWIDGET_H
