
#include "../CFileSystemModel.h"

CFileSystemModel::CFileSystemModel()
{

}

bool CFileSystemModel::isChecked(const QModelIndex &index)
{
    return checkedIndexes.contains(index);
}

QStringList CFileSystemModel::getCheckedPath()
{
    QStringList lstFilePath;
    QSet<QPersistentModelIndex>::const_iterator i = checkedIndexes.constBegin();
    while (i != checkedIndexes.constEnd())
    {
        QModelIndex index = *i;
        QString strPath = filePath(index);
        lstFilePath.append(strPath);
        ++i;
    }
    return lstFilePath;
}

void CFileSystemModel::setTreeView(QTreeView *pTreeView)
{
    m_pTreeView = pTreeView;
}

void CFileSystemModel::clearSelectedPath()
{
    checkedIndexes.clear();
}

Qt::ItemFlags CFileSystemModel::flags(const QModelIndex &index) const
{
    return QDirModel::flags(index) | Qt::ItemIsUserCheckable;
}

QVariant CFileSystemModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::CheckStateRole && index.column() == 0)
    {
        return checkedIndexes.contains(index) ? Qt::Checked : Qt::Unchecked;
    }
    else
    {
        return QDirModel::data(index, role);
    }
}
bool CFileSystemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::CheckStateRole)
    {
        if(value == Qt::Checked)
        {
            if(!checkedIndexes.contains(index))
            {
                checkedIndexes.insert(index);
                recursiveCheckParent(index,value);
                if(m_pTreeView->isExpanded(index))
                {
                    recursiveCheckChild(index, value);
                }
            }
        }
        else
        {
            recursiveUncheckParent(index,value);
            if(hasChildren(index) == true)
            {
                recursiveUncheckChild(index, value);
            }
            checkedIndexes.remove(index);
        }        
        emit layoutChanged();
        return true;
    }
    return QDirModel::setData(index, value, role);
}

int CFileSystemModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

void CFileSystemModel::recursiveCheckChild(const QModelIndex &index, const QVariant &value)
{    
    if(hasChildren(index))
    {
        int childrenCount = rowCount(index);
        QModelIndex child;
        for(int i=0; i<childrenCount; i++)
        {
            child = QDirModel::index(i, 0, index);
            checkedIndexes.insert(child);
            if(m_pTreeView->isExpanded(child))
            {
                recursiveCheckChild(child, value);
            }
        }
    }
}

void CFileSystemModel::recursiveUncheckParent(const QModelIndex &index, const QVariant &value)
{
    if(index.parent().isValid())
    {
        QModelIndex parent = index.parent();
        if(checkedIndexes.contains(parent))
        {
            checkedIndexes.remove(parent);            
            recursiveUncheckParent(parent,value);
        }
    }
}

void CFileSystemModel::recursiveUncheckChild(const QModelIndex &index, const QVariant &value)
{
    if(!checkedIndexes.contains(index))
    {
        return;
    }
    if(hasChildren(index))
    {
        int childrenCount = rowCount(index);
        QModelIndex child;
        for(int i=0; i<childrenCount; i++)
        {
            child = QDirModel::index(i, 0, index);
            recursiveUncheckChild(child, value);
            checkedIndexes.remove(child);
        }
    }
}

void CFileSystemModel::recursiveCheckParent(const QModelIndex &index, const QVariant &value)
{
    if(index.parent().isValid())
    {
        QModelIndex parent = index.parent();
        int childrenCount = rowCount(parent);
        QModelIndex child;
        bool bAll = true;
        for(int i=0; i<childrenCount; i++)
        {
            child = QDirModel::index(i, 0, parent);
            if(!checkedIndexes.contains(child))
            {
                bAll = false;
                break;
            }
        }
        if(bAll)
        {
            checkedIndexes.insert(parent);            
            recursiveCheckParent(parent,value);
        }
    }
}
