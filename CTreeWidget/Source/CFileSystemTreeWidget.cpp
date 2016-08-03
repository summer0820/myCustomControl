
#include "CFileSystemTreeWidget.h"
#include "../CFileSystemModel.h"


CFileSystemTreeWidget::CFileSystemTreeWidget(QWidget *parent)
    :QTreeView(parent)
{
    m_nMaxLength = -1;
    initTreeView();
    connect(this,SIGNAL(expanded(QModelIndex)),this,SLOT(sltExpanded(QModelIndex)));
    setFocusPolicy(Qt::NoFocus);
}

CFileSystemTreeWidget::~CFileSystemTreeWidget()
{
    int nCount = m_pTreeModel->rowCount();
    m_pTreeModel->removeRows(0,nCount);
    delete m_pTreeModel;
}

QStringList CFileSystemTreeWidget::getCheckedPath()
{
    return m_pTreeModel->getCheckedPath();
}

QStringList CFileSystemTreeWidget::getSelectedFiles()
{
    m_lstErrorFiles.clear();
    QStringList listResult;
    QStringList lstOrignal = getOrignalFiles();
    if(m_nMaxLength > 0)
    {
        for(int i = 0; i < lstOrignal.count(); i++)
        {
            QString strFileName = QDir::toNativeSeparators(lstOrignal.at(i));

            int nPathLen = strFileName.toUtf8().size();
            if(nPathLen > m_nMaxLength)
            {
                m_lstErrorFiles.append(strFileName);
            }
            else
            {
                listResult.append(strFileName);
            }
        }
    }
    else
    {
        listResult = lstOrignal;
    }
    return listResult;
}

void CFileSystemTreeWidget::clearSelectedPath()
{
    m_pTreeModel->clearSelectedPath();
}

void CFileSystemTreeWidget::refresh()
{
    m_pTreeModel->refresh();
}

void CFileSystemTreeWidget::setMaxPathLength(int nLen)
{
    m_nMaxLength = nLen;
}

QStringList CFileSystemTreeWidget::getErrorFiles()
{
    return m_lstErrorFiles;
}

void CFileSystemTreeWidget::initTreeView()
{
    setHeaderHidden(true);
    setAnimated(true);

    header()->setResizeMode(QHeaderView::ResizeToContents);
    header()->setStretchLastSection(false);

    m_pTreeModel = new CFileSystemModel();    
    m_pTreeModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
    m_pTreeModel->setTreeView(this);
    setModel(m_pTreeModel);
}

QStringList CFileSystemTreeWidget::getOrignalFiles()
{
    QStringList lstSourcePath = m_pTreeModel->getCheckedPath();

    QStringList lstDestFiles;
    while(lstSourcePath.count() > 0)
    {
        QString strPath = lstSourcePath.at(0);
        QFileInfo info(strPath);
        lstSourcePath.removeOne(strPath);
        if(info.isDir())
        {
            QDirIterator iter(strPath, QDirIterator::Subdirectories);
            while(iter.hasNext())
            {
                iter.next();
                QFileInfo info = iter.fileInfo();
                QString strAbsPath = info.absoluteFilePath();
                if(info.isFile())
                {
                    lstDestFiles.append(strAbsPath);
                }
                else if(info.isDir())
                {
                    if(lstSourcePath.contains(strAbsPath))
                    {
                        lstSourcePath.removeOne(strAbsPath);
                    }
                }
            }
        }
        else if(info.isFile())
        {
            lstDestFiles.append(strPath);
        }
    }

    lstDestFiles.removeDuplicates();

    return lstDestFiles;
}

void CFileSystemTreeWidget::sltExpanded(const QModelIndex &index)
{
    if(m_pTreeModel->isChecked(index))
    {
        m_pTreeModel->recursiveCheckChild(index,Qt::Checked);
    }
}
