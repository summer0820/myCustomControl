#ifndef CCLICKLABEL_H
#define CCLICKLABEL_H

#include "stdafx.h"

class CClickLabelPrivate;

class CClickLabel : public QLabel
{

    Q_OBJECT
   public:
       CClickLabel(QWidget *parent = 0, Qt::WindowFlags f = 0);
       CClickLabel(const QString &text, QWidget *parent = 0,
               Qt::WindowFlags f = 0);
       virtual ~CClickLabel();
   Q_SIGNALS:
       /// @brief emit when mouse click label
       void clicked();
       void sigTextClicked();

   protected:
       virtual void mousePressEvent(QMouseEvent *e);
       virtual void mouseReleaseEvent(QMouseEvent *e);

   private:
       Q_DISABLE_COPY(CClickLabel)
       Q_DECLARE_PRIVATE(CClickLabel)
       CClickLabelPrivate* const d_ptr;
       bool                m_bTextClicked;
};

#endif // CCLICKLABEL_H
