#ifndef CTABLEVIEW_H
#define CTABLEVIEW_H

#include "stdafx.h"
#include "../include/CSortStandardItem.h"
#include "../include/CClickLabel.h"

enum ETableLayoutModel
{
    ListModel = 0,
    IconModel = 1
};

class ItemDelegate:public QItemDelegate
{
    Q_OBJECT
public:
    ItemDelegate(){}
    void drawDisplay(QPainter*painter,const QStyleOptionViewItem& option,const QRect& rect,const QString& text)const
    {
        //qDebug()<<"=======draw display";
        //painter->setPen(Qt::green);
        //painter->drawText(rect.x() + 10,rect.y(),rect.width() - 10,rect.height(),Qt::AlignHCenter,text);
        QRect rectText = QRect(rect.x() + 10,rect.y(),rect.width() - 10,rect.height());
        QItemDelegate::drawDisplay(painter,option,rectText,text);
    }
};

class CHeaderView;
class CTableView : public QTableView
{
    Q_OBJECT

public:
       CTableView(QWidget *parent = 0);

       void                resetSort();
       void                resetModel(int nItemCount);
       void                setViewModel(QStandardItemModel *model);

       void                setDataNullMode(bool b);

       void                setLayoutModel(ETableLayoutModel layoutModel);
       ETableLayoutModel   getLayoutModel();

       void                setListLayout();
       void                setIconLayout();

       void                resizeToContent();

       void                setHeaderBorderImage(Qt::Orientation orientation, QString str);
       QString             getHeaderBorderImage(Qt::Orientation orientation);

       void                setSortUpIcon(Qt::Orientation orientation, QString pixmap);
       void                setSortDownIcon(Qt::Orientation orientation, QString pixmap);

       void                setHeaderCheckedIcon(QString icon);
       void                setHeaderUnCheckedIcon(QString icon);

       void                setHeaderCheckable(Qt::Orientation orientation, bool chekable);
       void                addItem( QString strText, int nColum, int nRow, bool bCheckable = false, SortMode sortMode = String);
       void                addItem(QString strText, int nColum, int nRow, int bLink = 0, SortMode sortMode = String, QString objectname = "");

       QStringList         getCheckedText();
       QList<int>          getCheckedIndex();

private:
       CHeaderView          *m_pViewHorizontalHeader;
       QStandardItemModel   *m_pViewModel;
       ETableLayoutModel     m_etableLayoutModel;
       int                   m_nListLayoutItemHeight;

       QHBoxLayout           *m_phblDataNull;
       QLabel                *m_plblDataNull;

       QString                   m_strBorderImage;
       QPixmap                   m_pixSortIcon;
       QList<CSortStandardItem*> m_lstCurItem;
       QList<QCheckBox*>         m_lstCheckBox;
       QList<CClickLabel*>       m_lstItemLable;
       int                       m_nCheckedCount;

       void                      resetCheckBoxText(QCheckBox* pchkBox, QString str);
       void                      resetLabelItemText(CClickLabel *plblLabel, QString str);
       CClickLabel*              createItemLabel(QString strText);

private slots:
       void                 sltHeaderCheckStateChanged(Qt::CheckState state);
       void                 sltCheckBoxStateChanged(int state);
       void                 sltLocalPolicySectionMoved(int logicalIndex, int oldSize, int newSize);
       void                 sltLinkItemClicked();

signals:
       void                 sigLinkItemClicked(QString str);

//signals:
      // void                  sigHeaderCheckStateChanged(Qt::CheckState state);
};

#endif // CTABLEVIEW_H
