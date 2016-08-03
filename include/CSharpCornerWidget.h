#ifndef CSHARPCORNERWIDGET_H
#define CSHARPCORNERWIDGET_H

#include "stdafx.h"

#include "CShadowWidget.h"

class CCustomToolButton;

class CSharpCornerWidget : public CShadowWidget
{
    Q_OBJECT
public:
    CSharpCornerWidget(QWidget *parent = 0, QPixmap pixShadow = QPixmap(""));
    ~CSharpCornerWidget();

    void            setTitle(QString strTitle);
    void            addActionItem(QString strIcon,QString strText,QString strKey);

protected:
    void            mousePressEvent(QMouseEvent *event);
    void            mouseReleaseEvent(QMouseEvent *event);
    void            hideEvent(QHideEvent * event);

private:
    void            updateItems();

private slots:
    void            sltItemClicked();

private:
    QVBoxLayout     *m_pMainLayout;
    QLabel          *m_pTitleLabel;

    QList<CCustomToolButton *> m_lstItem;


signals:
    void            sigItemClicked(QString strKey);
    void            sigHidden();

};

#endif // CSHARPCORNERWIDGET_H
