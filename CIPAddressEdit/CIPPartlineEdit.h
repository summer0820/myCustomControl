#ifndef CIPPARTLINEEDIT
#define CIPPARTLINEEDIT
#include "stdafx.h"

class CIPPartlineEdit : public QLineEdit
{
    Q_OBJECT
public:
    CIPPartlineEdit(QWidget *parent = 0);
    ~CIPPartlineEdit(void);

    void              setNtextTabEdit(QLineEdit *nexttab);
    void              setPrevEdit(QLineEdit *prevEdit);


protected:
    virtual void     focusInEvent(QFocusEvent *e);
    virtual void     keyPressEvent(QKeyEvent *event);

private slots:
    void             sltTextEdited(const QString& text);

private:
    QLineEdit        *m_pletNextTab;
    QLineEdit        *m_pletPrevEdit;
};

#endif // CIPPARTLINEEDIT

