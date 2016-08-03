#include "../../include/CSortStandardItem.h"
#include "../pinyin1alpha.h"

bool versionSort(QString str1, QString str2)
{
    QStringList verList1 = str1.split('.');

    QStringList verList2 = str2.split('.');

    int nCountFor = verList1.count() < verList2.count() ? verList1.count() : verList2.count();

    bool bLessThan = true;
    for(int i = 0; i < nCountFor; i++)
    {
        if(verList1.at(i).toInt() < verList2.at(i).toInt())
        {
            bLessThan = true;
            break;
        }
        else if(verList1.at(i).toInt() > verList2.at(i).toInt())
        {
            bLessThan = false;
            break;
        }
        else
        {
            continue;
        }
    }

    return bLessThan;
}

bool isChinese(QChar ch)
{
    ushort co = ch.unicode();
    return isUnicodeHz(co);
}

bool softNameSort(QString str1, QString str2)
{
    bool bLessThan = true;
    int nCount1 = str1.count();
    int nCount2 = str2.count();
    int nCount = nCount1 > nCount2 ? nCount2 : nCount1;

    for(int i = 0; i < nCount; i++)
    {
        QChar ch1 = str1.at(i);
        QChar ch2 = str2.at(i);

        if(isChinese(ch1))
        {
            if(isChinese(ch2))
            {
                QChar strLetter1 = getPinyin2Astr(ch1);
                QChar strLetter2 = getPinyin2Astr(ch2);
                if(strLetter1 == strLetter2)
                {
                    continue;
                }
                else
                {
                    bLessThan = strLetter1 < strLetter2;
                    break;
                }
            }
            else
            {
                bLessThan = false;
                break;
            }
        }
        else
        {
            if(isChinese(ch2))
            {
                bLessThan = true;
                break;
            }
            else
            {
                if( ch1.toLower() == ch2.toLower() )
                {
                    continue;
                }
                else
                {
                    bLessThan = ch1.toLower() < ch2.toLower();
                    break;
                }
            }
        }
    }
    return bLessThan;
}


CSortStandardItem::CSortStandardItem()
{
    m_sortMode = String;
}

CSortStandardItem::CSortStandardItem(const QString &text, SortMode sortmode)
{
    setText(text);
    m_sortMode = sortmode;
}

CSortStandardItem::CSortStandardItem(const CSortStandardItem &other, SortMode sortmode)
{
    m_sortMode = sortmode;
}

CSortStandardItem &CSortStandardItem::operator=(const CSortStandardItem &other)
{
    QStandardItem::operator=(other);
    return *this;
}

bool CSortStandardItem::operator<(const QStandardItem &other) const
{
    QVariant templ = data(Qt::DisplayRole), tempr = other.data(Qt::DisplayRole);
    if(m_sortMode == Int || m_sortMode ==  UInt || m_sortMode == LongLong
            || m_sortMode == ULongLong || m_sortMode == Float || m_sortMode == Double)
    {
        QString strTempl = templ.toString();
        if(strTempl.endsWith("%"))
        {
            strTempl = strTempl.remove("%");
        }
        else if(strTempl.endsWith("kb",Qt::CaseInsensitive) || strTempl.endsWith("GB",Qt::CaseInsensitive))
        {
            strTempl = strTempl.left(strTempl.length() - 2);
            //qDebug("==============strTempl = %s", qPrintable(strTempl));
            if(strTempl.contains(","))
            {
                strTempl = strTempl.remove(",");
                //qDebug("==============strTempl = %s", qPrintable(strTempl));
            }
        }
        templ.clear();
        templ = QVariant(strTempl);

        QString strTempr = tempr.toString();						     
        if(strTempr.endsWith("%"))							       
        {
            strTempr = strTempr.remove("%");
        }
        else if(strTempr.endsWith("kb",Qt::CaseInsensitive) || strTempr.endsWith("GB",Qt::CaseInsensitive))
        {
            strTempr = strTempr.left(strTempr.length() - 2);
             //qDebug("==============strTempr = %s", qPrintable(strTempr));
            if(strTempr.contains(","))
            {
                strTempr = strTempr.remove(",");
               // qDebug("==============strTempl = %s", qPrintable(strTempr));
            }
        }
        tempr.clear();
        tempr = QVariant(strTempr);
    }

    QVariant l = templ, r = tempr;
    //qDebug("============l.string = %s",qPrintable(l.toString()));
    switch(m_sortMode)
    {
    case Int:
        if(l.toInt() == r.toInt())
        {
            return true;
        }
        else
        {
            return l.toInt() < r.toInt();
        }
    case UInt:
        if(l.toUInt() == r.toUInt())
        {
            return true;
        }
        else
        {
            return l.toUInt() < r.toUInt();
        }
    case LongLong:
        if(l.toLongLong() == r.toLongLong())
        {
            return true;
        }
        else
        {
            return l.toLongLong() < r.toLongLong();
        }
    case ULongLong:
        if(l.toULongLong() == r.toULongLong())
        {
            return true;
        }
        else
        {
            return l.toULongLong() < r.toULongLong();
        }
    case Float:
        if(l.toFloat() == r.toFloat())
        {
            //qDebug("==========l.toFloat = %f, r.toFloat", l.toFloat(), r.toFloat());
            return true;
        }
        else
        {
            return l.toFloat() < r.toFloat();
        }
    case Double:
        if(l.toDouble() == r.toDouble())
        {
            return true;
        }
        else
        {
            return l.toDouble() < r.toDouble();
        }
    case Char:
        if(l.toChar() == r.toChar())
        {
            return true;
        }
        else
        {
            return l.toChar() < r.toChar();
        }
    case Date:
        if(l.toDate() == r.toDate())
        {
            return true;
        }
        else
        {
            return l.toDate() < r.toDate();
        }
    case Time:
        if(l.toTime() == r.toTime())
        {
            return true;
        }
        else
        {
            return l.toTime() < r.toTime();
        }
    case DateTime:
        if(l.toDateTime() == r.toDateTime())
        {
            return true;
        }
        else
        {
            return l.toDateTime() < r.toDateTime();
        }
    case Pinyin:
        //Pinyin Sort用Unicode查表得拼音首字母排序，比较准确！
        if(getPinyin1Astr(l.toString()) == getPinyin1Astr(r.toString()))
        {
            return true;
        }
        else
        {
            return getPinyin1Astr(l.toString()) < getPinyin1Astr(r.toString());
        }
    case Version:
    {
        return versionSort(l.toString(),r.toString());
    }
    case SoftName:
    {
        return softNameSort(l.toString(),r.toString());
    }
    case String:
    default:
        if(l.toString().toLower() == r.toString().toLower())
        {
            return true;
        }
        else
        {
            return l.toString().toLower() < r.toString().toLower();
        }
    }
    return QStandardItem::operator<(other);
}


