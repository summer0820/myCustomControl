#ifndef CPIXMAPLABEL_H
#define CPIXMAPLABEL_H
#include "stdafx.h"

class CPixmapLabel : public QWidget
{
public:
    explicit CPixmapLabel(QWidget *parent = 0, QString text = "");
    explicit CPixmapLabel(QWidget *parent = 0, QPixmap pixmap = QPixmap(""), QString str = "");
    ~CPixmapLabel();

    void           setMarginsValue(int left, int top, int right, int bottom);

    void           setSpacing(int space);
    int            getSpacing();

    void           setLeftPixmap(QPixmap pix);
    const QPixmap  *getLfetPixmap();

    void            setShowText(QString str);
    QString         getShowText();

private:
    QString  m_strText;
    QPixmap  m_pixLeft;

    QLabel         *m_plblPixmap;
    QLabel         *m_plblText;
    QHBoxLayout    *m_phblMain;

    void           initUI();
};

#endif // CPIXMAPLABEL_H
