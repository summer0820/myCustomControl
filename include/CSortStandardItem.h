#ifndef CSORTSTANDARDITEM_H
#define CSORTSTANDARDITEM_H
#include "stdafx.h"
typedef enum
{
    Int = 0,
    UInt = 1,
    LongLong = 2,
    ULongLong = 3,
    Float = 4,
    Double = 5,
    Char = 6,
    Date = 7,
    Time = 8,
    DateTime = 9,
    String = 10,
    Pinyin = 11,
    Version = 12,
    SoftName = 13
} SortMode;

class CSortStandardItem : public QStandardItem
{

public:
    CSortStandardItem();
    CSortStandardItem(const QString &text, SortMode sortmode);
    CSortStandardItem(const CSortStandardItem &other, SortMode sortmode);
    CSortStandardItem &operator=(const CSortStandardItem &other);
    virtual bool operator<(const QStandardItem &other)const;

private:
    SortMode    m_sortMode;
};

#endif // CSORTSTANDARDITEM_H
