#ifndef TITEMSTRUCT_H
#define TITEMSTRUCT_H

#include <QString>
#include <QStringList>

struct TItemData
{
    int         parentId;
    int         id;
    QString     text;
    QString     strKey;
    QString     strNormalIcon;
    QString     strCheckedIcon;
    QString     strFontName;
    int         nFontSize;
    QString     strExpandIcon;
    QString     strCollapseIcon;
    bool        bBold;
    bool        bHasBottomBorder;
    QStringList lstFullPath;
    QStringList lstTableHead;
};

struct TItemSate
{
    QString strKey;

    int     nTotalRecordCount;
    int     nCurrentPage;

    QString strTime;
};


#endif // TITEMSTRUCT_H
