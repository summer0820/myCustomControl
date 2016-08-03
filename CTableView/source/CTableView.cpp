#include "../../include/CTableView.h"
#include "../CHeaderView.h"

CTableView::CTableView(QWidget *parent)
    :QTableView(parent)
{
    setContentsMargins(10, 0, 0, 0);
    m_pViewModel = NULL;
    m_plblDataNull = NULL;
    m_lstCurItem.clear();
    m_lstCheckBox.clear();
    m_lstItemLable.clear();
    m_nCheckedCount = 0;
    setFrameShape(QFrame::NoFrame);    //设置无边框
    verticalHeader()->setVisible(false);
    setFocusPolicy(Qt::NoFocus); //去除选中虚线框

    m_pViewHorizontalHeader = new CHeaderView(Qt::Horizontal, this);
    setHorizontalHeader(m_pViewHorizontalHeader);
    //connect(m_pViewHorizontalHeader, SIGNAL(sigCheckStateChanged(Qt::CheckState)), this, SIGNAL(sigHeaderCheckStateChanged(Qt::CheckState)));
    connect(m_pViewHorizontalHeader, SIGNAL(sigCheckStateChanged(Qt::CheckState)), this, SLOT(sltHeaderCheckStateChanged(Qt::CheckState)));
    connect(m_pViewHorizontalHeader, SIGNAL(sectionResized(int,int,int)), this, SLOT(sltLocalPolicySectionMoved(int, int, int)));

    m_nListLayoutItemHeight = verticalHeader()->defaultSectionSize();
    setLayoutModel(ListModel);
    setWordWrap(false);
    setItemDelegate(new ItemDelegate);

    m_phblDataNull = new QHBoxLayout();
    m_phblDataNull->setContentsMargins(0, 0, 0, 0);
    setLayout(m_phblDataNull);

    if(m_plblDataNull == NULL)
    {
        m_plblDataNull = new QLabel(this);
        m_plblDataNull->setAlignment(Qt::AlignCenter);
        m_plblDataNull->setStyleSheet("QLabel{font: 14px 'Microsoft YaHei';"
                                      "color: #cccccc}");
        m_plblDataNull->setText(QString::fromLocal8Bit("暂无数据"));
        m_phblDataNull->addWidget(m_plblDataNull, 0, Qt::AlignCenter);
    }
}

/*
*  重置表格排序，表格获取到数据显示之后，沿用之前的排序规则重新排序，默认升序排序
*/
void CTableView::resetSort()
{
    int nIndex = horizontalHeader()->sortIndicatorSection();
    Qt::SortOrder nSortOrder = horizontalHeader()->sortIndicatorOrder();
    horizontalHeader()->setSortIndicator(nIndex, nSortOrder);
}

/*
*  重置表格数据
*  @param: int 表格显示列表项数目。为了处理无数据时，表格依然显示网格，必须设置此项
*/
void CTableView::resetModel(int nItemCount)
{
    m_nCheckedCount = 0;
    if(m_pViewModel == NULL)
    {
        return;
    }
    if(m_pViewHorizontalHeader != NULL)
    {
        m_pViewHorizontalHeader->setChecked(false);
        m_pViewHorizontalHeader->update();
    }
    int nCount = m_pViewModel->rowCount();
    if(m_lstCheckBox.isEmpty() == false)
    {
        for(int i = 0; i < m_lstCheckBox.count(); i++)
        {
            QCheckBox *pCheckBox = m_lstCheckBox.at(i);
            if(pCheckBox != NULL)
            {
                pCheckBox->setParent(0);
                delete pCheckBox;
                pCheckBox = NULL;
            }
        }
        m_lstCheckBox.clear();
    }
    m_lstCurItem.clear();

    if(m_lstItemLable.isEmpty() == false)
    {
        for(int i = 0; i < m_lstItemLable.count(); i++)
        {
            QLabel *plblLable = m_lstItemLable.at(i);
            if(plblLable != NULL)
            {
                plblLable->setParent(0);
                delete plblLable;
                plblLable = NULL;
            }
        }
        m_lstItemLable.clear();
    }
    m_pViewModel->removeRows(0, nCount);
    m_pViewModel->setRowCount(nItemCount);
}

/*
*  设置表格显示数据
*  @param: QStandardItemModel* 表格数据
*/
void CTableView::setViewModel(QStandardItemModel *model)
{
    m_pViewModel = model;
    setModel(model);
}

void CTableView::setDataNullMode(bool b)
{
    if(b == true)
    {
        m_plblDataNull->show();
    }
    else
    {
        m_plblDataNull->hide();
    }
}

/*
* 设置表格布局模式
* @param: ETableLayoutModel 布局模式
*         layoutModel == ListModel 列表形式显示
*         layoutModel == IconModel 缩略图形式显示
*/
void CTableView::setLayoutModel(ETableLayoutModel layoutModel)
{
    m_etableLayoutModel = layoutModel;
    switch(layoutModel)
    {
    case IconModel:
        setIconLayout();
        break;
    case ListModel:
    default:
        setListLayout();
        break;
    }
}

/*
*  获取表格布局模式
*  @return: ETableLayoutModel布局模式
*           layoutModel == ListModel 列表形式显示
*         layoutModel == IconModel 缩略图形式显示
*/
ETableLayoutModel CTableView::getLayoutModel()
{
    return m_etableLayoutModel;
}

/*
*  设置表格以列表的形式显示。
*  表格显示表头，可进行排序，可整行选中，表格列表之间以两种颜色间隔显示，不显示网格线
*/
void CTableView::setListLayout()
{
    setSortingEnabled(true);
    horizontalHeader()->setVisible(true);
    horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
    setAlternatingRowColors(true);   //表格背景相间
    //setSelectionBehavior(QAbstractItemView::SelectRows); //整行选择
    setSelectionMode(QAbstractItemView::NoSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setShowGrid(false);  //不显示表格线

#if QT_VERSION >= 0x050000
    horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
#else
    horizontalHeader()->setResizeMode(QHeaderView::Interactive);
#endif

    horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->setDefaultSectionSize(36);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
}

/*
*  设置表格以缩略图的形式显示
*  表格不显示表头，不可排序，不可整行选中，表格不做颜色间隔显示，显示网格线
*/
void CTableView::setIconLayout()
{
    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(false);
    setAlternatingRowColors(false);   //表格背景相间
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::NoSelection);    
    horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
#if QT_VERSION >= 0x050000
    horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
#else
    horizontalHeader()->setResizeMode(QHeaderView::Interactive);
#endif

    setShowGrid(false);  //不显示表格线
    verticalHeader()->setDefaultSectionSize(100);

}

void CTableView::resizeToContent()
{
    resizeColumnsToContents();
    horizontalHeader()->setStretchLastSection(true);
}

void CTableView::setHeaderBorderImage(Qt::Orientation orientation, QString str)
{
    m_strBorderImage = str;
    if(orientation == Qt::Horizontal)
    {
        m_pViewHorizontalHeader->setBoderImage(str);
    }
}

void CTableView::setHeaderCheckable(Qt::Orientation orientation, bool chekable)
{
    if(orientation == Qt::Horizontal)
    {
        m_pViewHorizontalHeader->setCheckable(chekable);
    }
}

void CTableView::addItem(QString strText, int nColum, int nRow, bool bCheckable, SortMode sortMode)
{
    if(m_pViewModel != NULL)
    {
        CSortStandardItem *item = new CSortStandardItem(strText, sortMode);
        item->setForeground(QBrush("#797979"));
        m_pViewModel->setItem(nRow, nColum, item);
        item->setToolTip(strText);
        m_lstCurItem<<item;

        if(bCheckable == true)
        {
            item->setForeground(QColor(0, 0, 0, 0));
            QCheckBox *pCheckBox = new QCheckBox(this);
            pCheckBox->setProperty("userData", QVariant(strText));
            pCheckBox->setCheckable(true);
            pCheckBox->setObjectName("localPolicy");
            pCheckBox->setStyleSheet(pCheckBox->styleSheet().append("background-color: rgba(0, 0, 0, 0);"));
            pCheckBox->setFixedWidth(m_pViewHorizontalHeader->sectionSize(0));
            resetCheckBoxText(pCheckBox, strText);
            m_lstCheckBox<<pCheckBox;
            setIndexWidget(m_pViewModel->index(nRow, nColum), pCheckBox);
            connect(pCheckBox, SIGNAL(stateChanged(int)), this, SLOT(sltCheckBoxStateChanged(int)));
        }
        else
        {
            m_pViewModel->setItem(nRow, nColum, item);
        }
    }
}

void CTableView::addItem(QString strText, int nColum, int nRow, int bLink, SortMode sortMode, QString objectname)
{
    if(m_pViewModel != NULL)
    {
        CSortStandardItem *item = new CSortStandardItem(strText, sortMode);
        item->setForeground(QBrush("#797979"));
        m_pViewModel->setItem(nRow, nColum, item);
        item->setToolTip(strText);
        m_lstCurItem<<item;

        if(bLink == 1)
        {
            item->setForeground(QColor(0, 0, 0, 0));
            //CClickLabel *pClickLabel = this->createItemLabel(strText);
            CClickLabel *plblIndexWidget = new CClickLabel(strText);
            plblIndexWidget->setStyleSheet("background-color:rgba(0,0,0,0);"
                                           "font-size: 12px;"
                                           "color: #797979");
            QFont font = plblIndexWidget->font();
            font.setUnderline(true);
            plblIndexWidget->setFont(font);
            plblIndexWidget->setIndent(10);
            plblIndexWidget->setProperty("userData", QVariant(objectname));
            resetLabelItemText(plblIndexWidget, strText);
            m_lstItemLable<<plblIndexWidget;
            connect(plblIndexWidget, SIGNAL(sigTextClicked()), this, SLOT(sltLinkItemClicked()));
            setIndexWidget(m_pViewModel->index(nRow, nColum), plblIndexWidget);
        }
        else
        {
            m_pViewModel->setItem(nRow, nColum, item);
        }
    }
}

QStringList CTableView::getCheckedText()
{
    QStringList lstText;
    lstText.clear();
    for(int i = 0; i < m_lstCheckBox.count(); i++)
    {
        QCheckBox *pcheckBox = m_lstCheckBox.at(i);
        if(pcheckBox->isChecked())
        {
            QString strText = pcheckBox->property("userData").toString();
            lstText.append(strText);
        }
    }
    return lstText;
}

QList<int> CTableView::getCheckedIndex()
{
    QList<int> lstCheckIndex;
    lstCheckIndex.clear();
    for(int i = 0; i < m_lstCheckBox.count(); i++)
    {
        QCheckBox *pcheckBox = m_lstCheckBox.at(i);
        if(pcheckBox->isChecked())
        {
            lstCheckIndex<< i;
        }
    }
    return lstCheckIndex;
}

void CTableView::resetCheckBoxText(QCheckBox *pchkBox, QString str)
{
    QFontMetrics fm = pchkBox->fontMetrics();
    pchkBox->setText(fm.elidedText(str, Qt::ElideRight, pchkBox->width() - 50));
}

void CTableView::resetLabelItemText(CClickLabel *plblLabel, QString str)
{
    QFontMetrics fm = plblLabel->fontMetrics();
    plblLabel->setText(fm.elidedText(str, Qt::ElideRight, m_pViewHorizontalHeader->sectionSize(0) - 20));
}

CClickLabel* CTableView::createItemLabel(QString strText)
{
    CClickLabel *plblIndexWidget = new CClickLabel(strText);
    plblIndexWidget->setStyleSheet("background-color:rgba(0,0,0,0);"
                                   "font-size: 12px;"
                                   "color: #797979");
    QFont font = plblIndexWidget->font();
    font.setUnderline(true);
    plblIndexWidget->setFont(font);
    plblIndexWidget->setIndent(10);
    plblIndexWidget->setProperty("userData", QVariant(strText));
    resetLabelItemText(plblIndexWidget, strText);
    m_lstItemLable<<plblIndexWidget;
    return plblIndexWidget;
}

void CTableView::sltHeaderCheckStateChanged(Qt::CheckState state)
{
    if(m_lstCheckBox.isEmpty())
    {
        return;
    }
    for(int i = 0; i < m_lstCheckBox.count(); i++)
    {
        m_lstCheckBox.at(i)->setCheckState(state);
    }
}

void CTableView::sltCheckBoxStateChanged(int state)
{
    QCheckBox *pchkBox = qobject_cast<QCheckBox *>(sender());
    int nRow = indexAt(pchkBox->pos()).row();
    int ncolumnCount = m_pViewModel->columnCount();
    if(pchkBox == NULL)
    {
        return;
    }
    if(m_pViewHorizontalHeader == NULL)
    {
        return;
    }
    if(state == Qt::Unchecked)
    {
        m_pViewHorizontalHeader->setChecked(false);
        m_pViewHorizontalHeader->update();
        m_nCheckedCount = m_nCheckedCount - 1;
        QString strStyleSheet = pchkBox->styleSheet();
        strStyleSheet.remove("background-color: #d3e9fc;");
        strStyleSheet.append("background-color: rgba(0, 0, 0, 0);");
        pchkBox->setStyleSheet(strStyleSheet);

        for(int i = 1; i < ncolumnCount; i++)
        {
            QStandardItem *item = m_pViewModel->item(nRow, i);
            item->setBackground(QColor(0,0,0,0));
        }
    }
    else if(state == Qt::Checked)
    {
        QString strStyleSheet = pchkBox->styleSheet();
        strStyleSheet.remove("background-color: rgba(0, 0, 0, 0);");
        strStyleSheet.append("background-color: #d3e9fc;");
        pchkBox->setStyleSheet(strStyleSheet);
        m_nCheckedCount = m_nCheckedCount + 1;
        for(int i = 1; i < ncolumnCount; i++)
        {
            QStandardItem *item = m_pViewModel->item(nRow, i);
            item->setBackground(QBrush("#d3e9fc"));
        }
    }

    if(m_nCheckedCount == m_lstCheckBox.count())
    {
        m_pViewHorizontalHeader->setChecked(true);
        m_pViewHorizontalHeader->update();
    }
}

void CTableView::sltLocalPolicySectionMoved(int logicalIndex, int oldSize, int newSize)
{
    //qDebug()<<"======tableView item newSize = "<<newSize;
    if(m_pViewModel == NULL )
    {
        return;
    }
    if(logicalIndex == 0)
    {
        if(m_lstItemLable.isEmpty() == false)
        {
            for(int i = 0; i < m_lstItemLable.count(); i++)
            {
                CClickLabel *plblLabelItem = m_lstItemLable.at(i);
                if(plblLabelItem != NULL)
                {
                    plblLabelItem->setFixedWidth(newSize);
                    QString strText = plblLabelItem->property("userData").toString();
                    //qDebug()<<"====Clicked lable text = "<<strText;
                    resetLabelItemText(plblLabelItem, strText);
                }
            }
        }
    }

    if(logicalIndex == 0)
    {
        if( m_lstCheckBox.isEmpty() == false)
        {
            for(int i = 0; i < m_lstCheckBox.count(); i++)
            {
                QCheckBox *pCheckbox = m_lstCheckBox.at(i);
                if(pCheckbox != NULL)
                {
                    pCheckbox->setFixedWidth(newSize);
                    QString strSoftName = m_pViewModel->item(i)->text();
                    resetCheckBoxText(pCheckbox, strSoftName);
                }
            }
        }
    }
}

void CTableView::sltLinkItemClicked()
{
    CClickLabel *pLabel = qobject_cast<CClickLabel *>(sender());
    QString strText = pLabel->property("userData").toString();
    emit sigLinkItemClicked(strText);

}

QString CTableView::getHeaderBorderImage(Qt::Orientation orientation)
{
    if(orientation == Qt::Horizontal)
    {
        return m_strBorderImage;
    }
    else
    {
        return "";
    }
}

void CTableView::setSortUpIcon(Qt::Orientation orientation, QString pixmap)
{
    if(orientation == Qt::Horizontal)
    {
        m_pViewHorizontalHeader->setSortUpIcon(orientation, pixmap);
    }
}

void CTableView::setSortDownIcon(Qt::Orientation orientation, QString pixmap)
{
    if(orientation == Qt::Horizontal)
    {
        m_pViewHorizontalHeader->setSortDownIcon(orientation, pixmap);
    }
}

void CTableView::setHeaderCheckedIcon(QString icon)
{
    m_pViewHorizontalHeader->setCheckedPixmap(icon);
}

void CTableView::setHeaderUnCheckedIcon(QString icon)
{
    m_pViewHorizontalHeader->setUnCheckedPixmap(icon);
}

