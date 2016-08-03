
#include "../CTreeModel.h"
#include "../CTreeItem.h"
#include "TItemStruct.h"

#include <QCoreApplication>
#include <QStringList>
#include <QIcon>
#include <QFont>
#include <QTextFormat>
#include <QFile>
#include <QDomDocument>


CTreeModel::CTreeModel(QObject *parent)
    :QAbstractItemModel(parent)
{
    m_strAppPath = QCoreApplication::applicationDirPath();
    QList<QVariant> rootData;
    rootData << "Title";
    m_pRootItem = new CTreeItem(rootData);
}

CTreeModel::~CTreeModel()
{
    delete m_pRootItem;
}

void CTreeModel::setItemDataList(QList<TItemData> lstItemData)
{
    m_lstItemData = lstItemData;
    setupModelData(m_pRootItem);
}

TItemData CTreeModel::getItemDataByIndex(QModelIndex index)
{
    CTreeItem *pItem = static_cast<CTreeItem*>(index.internalPointer());
    TItemData itemData;
    for (int i = 0; i < m_lstItemData.count(); ++i)
    {
        itemData = m_lstItemData.at(i);
        if (itemData.id == pItem->data(0))
        {
            break;
        }
    }

    return itemData;
}

void CTreeModel::setXMLFile(QString strFilePath)
{
    parseXML(strFilePath);
    setupModelData(m_pRootItem);
}

QStringList CTreeModel::getFullPathByKey(QString strKey)
{
    QStringList lstFullPath;
    TItemData itemData;
    bool bFind = false;
    for (int i = 0; i < m_lstItemData.count(); ++i)
    {
        itemData = m_lstItemData.at(i);
        if (itemData.strKey == strKey)
        {
            bFind = true;
            break;
        }
    }

    if(bFind)
    {
        lstFullPath = itemData.lstFullPath;
    }
    return lstFullPath;
}

QVariant CTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    CTreeItem *pItem = static_cast<CTreeItem*>(index.internalPointer());
    TItemData itemData;
    for (int i = 0; i < m_lstItemData.count(); ++i)
    {
        itemData = m_lstItemData.at(i);
        if (itemData.id == pItem->data(0))
        {
            break;
        }
    }

    if (role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignVCenter);
    }
    else if (role == Qt::DisplayRole)
    {
        return itemData.text;
    }
    else if (role == Qt::DecorationRole)
    {
        if(itemData.toolIcon != "")
        {
            return QIcon(m_strAppPath + "/" + itemData.toolIcon);
        }
        else
        {
            return QVariant();
        }
    }
    else if(role == Qt::FontRole)
    {
        QFont font;
        if(itemData.bBold)
        {
            font.setBold(true);
        }
        font.setFamily(itemData.strFontName);
        font.setPixelSize(13);
        return font;
    }
    else
    {
        return QVariant();
    }
}

Qt::ItemFlags CTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return 0;
    }

    return QAbstractItemModel::flags(index);
}

QVariant CTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return m_pRootItem->data(section);
    }

    return QVariant();
}

QModelIndex CTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    CTreeItem *parentItem;

    if (!parent.isValid())
    {
        parentItem = m_pRootItem;
    }
    else
    {
        parentItem = static_cast<CTreeItem*>(parent.internalPointer());
    }

    CTreeItem *childItem = parentItem->child(row);
    if (childItem)
    {
        return createIndex(row, column, childItem);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex CTreeModel::parent(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return QModelIndex();
    }

    CTreeItem *childItem = static_cast<CTreeItem*>(index.internalPointer());
    CTreeItem *parentItem = childItem->parent();

    if(parentItem == m_pRootItem)
    {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int CTreeModel::rowCount(const QModelIndex &parent) const
{
    CTreeItem *parentItem;
    if (parent.column() > 0)
    {
        return 0;
    }

    if (!parent.isValid())
    {
        parentItem = m_pRootItem;
    }
    else
    {
        parentItem = static_cast<CTreeItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}

int CTreeModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        return static_cast<CTreeItem*>(parent.internalPointer())->columnCount();
    }
    else
    {
        return m_pRootItem->columnCount();
    }
}

void CTreeModel::setupModelData(CTreeItem *parent)
{
    QList<CTreeItem*> parents;
    parents << parent;

    for(int i = 0; i < m_lstItemData.count(); ++i)
    {
        TItemData itemData = m_lstItemData.at(i);
        QList<QVariant> columnData;
        columnData << itemData.id;

        for(int j = 0; j < parents.count(); ++j)
        {

            CTreeItem* item = this->item(parents.at(j), itemData);
            if(item)
            {
                item->appendChild(new CTreeItem(columnData, item));
            }
            else
            {
                parents.last()->appendChild(new CTreeItem(columnData, parents.last()));
            }
        }
    }
}

CTreeItem *CTreeModel::item(CTreeItem *item, TItemData data)
{
    CTreeItem *treeItem = NULL;
    if(item == NULL)
    {
        return treeItem;
    }

    int parentId = data.parentId;

    if (item->data(0) == parentId)
    {
        treeItem = item;
    }
    else
    {
        for(int j = 0; j < item->childCount(); ++j)
        {
            CTreeItem *childItem = item->child(j);
            CTreeItem *item2 = this->item(childItem, data);
            if (item2)
            {
                treeItem = item2;
                break;
            }
        }
    }

    return treeItem;
}

void CTreeModel::parseXML(QString strFilePath)
{
    if(strFilePath.isEmpty())
    {
        return;
    }

    QFile file(strFilePath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }

   QDomDocument document;
   QString error;
   int row = 0, column = 0;
   if(!document.setContent(&file, false, &error, &row, &column))
   {
       return;
   }

   if(document.isNull())
   {
       return;
   }

   QDomElement root = document.documentElement();
   QDomNodeList list = root.childNodes();
   int count = list.count();
   for(int i=0; i < count; ++i)
   {
       QDomNode dom_node = list.item(i);
       QDomElement element = dom_node.toElement();

       //获取子节点，数目为，包括：toolexename、tooltip、toolicon、website
       QDomNodeList child_list = element.childNodes();
       int child_count = child_list.count();

       TItemData data;

       for(int j=0; j<child_count; ++j)
       {
           QDomNode child_dom_node = child_list.item(j);
           QDomElement child_element = child_dom_node.toElement();
           QString child_tag_name = child_element.tagName();
           QString child__tag_value = child_element.text();

           if(QString::compare(child_tag_name, "parentID") == 0)
           {
                data.parentId = child__tag_value.toInt();
           }
           else if(QString::compare(child_tag_name, "ID") == 0)
           {
                data.id = child__tag_value.toInt();
           }
           else if(QString::compare(child_tag_name, "key") == 0)
           {
                data.strKey = child__tag_value;
           }
           else if(QString::compare(child_tag_name, "text") == 0)
           {
                data.text = child__tag_value;
           }
           else if(QString::compare(child_tag_name, "toolicon") == 0)
           {
                data.toolIcon = child__tag_value;
           }
           else if(QString::compare(child_tag_name, "fontname") == 0)
           {
                data.strFontName = child__tag_value;
           }
           else if(QString::compare(child_tag_name, "fontcolor") == 0)
           {
                data.strFontColor = child__tag_value;
           }
           else if(QString::compare(child_tag_name, "fontbold") == 0)
           {
                data.bBold = child__tag_value.toInt();
           }
           else if(QString::compare(child_tag_name, "fullpath") == 0)
           {
               QString strFullPath = child__tag_value;
               data.lstFullPath = strFullPath.split(";");
           }
      }
      m_lstItemData.append(data);
   }
}

