#include "../CIPPartlineEdit.h"

CIPPartlineEdit::CIPPartlineEdit(QWidget *parent)
: QLineEdit(parent)
{
    m_pletNextTab = NULL;
    m_pletPrevEdit = NULL;
    setObjectName("noborder");

    this->setMaxLength(3);
    this->setFrame(false);
    this->setAlignment(Qt::AlignCenter);

    QValidator *validator = new QIntValidator(0, 255, this);
    setValidator(validator);

    connect(this, SIGNAL(textEdited(const QString&)), this, SLOT(sltTextEdited(const QString&)));
    setStyleSheet("border:0px solid gray");

    setFixedHeight(30);

    //ScreenDisPlay screenDisplay;
    //screenDisplay.resetHeight(this);
}

CIPPartlineEdit::~CIPPartlineEdit(void)
{
}

void CIPPartlineEdit::setNtextTabEdit(QLineEdit *nexttab)
{
     m_pletNextTab = nexttab;
}

void CIPPartlineEdit::setPrevEdit(QLineEdit *prevEdit)
{
    m_pletPrevEdit = prevEdit;
}

void CIPPartlineEdit::focusInEvent(QFocusEvent *e)
{
    //selectAll();
    QLineEdit::focusInEvent(e);
}

void CIPPartlineEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Period)
    {
        if (m_pletNextTab)
        {
            if(text().isEmpty() == false)
            {
                m_pletNextTab->setFocus();
                m_pletNextTab->selectAll();
            }
        }
    }
    else if(event->key() == Qt::Key_Backspace)
    {
        if(m_pletPrevEdit)
        {
            if(text().isEmpty() == true)
            {
                QString strPrevText = m_pletPrevEdit->text();
                m_pletPrevEdit->setText(strPrevText.remove(strPrevText.length() - 1, 1));
                m_pletPrevEdit->setFocus();
            }
        }
    }
    QLineEdit::keyPressEvent(event);
}

void CIPPartlineEdit::sltTextEdited(const QString& text)
{
    QIntValidator v(0, 255, this);
    QString ipaddr = text;
    int pos = 0;
    QValidator::State state = v.validate(ipaddr, pos);
    if(state == QValidator::Acceptable)
    {
        if(ipaddr.size() > 1)
        {
            if(ipaddr.size() == 2)
            {
                int ipnum = ipaddr.toInt();

                if(ipnum > 25)
                {
                    if(m_pletNextTab)
                    {
                        m_pletNextTab->setFocus();
                        m_pletNextTab->selectAll();
                    }
                }
            }
            else
            {
                if(m_pletNextTab)
                {
                    m_pletNextTab->setFocus();
                    m_pletNextTab->selectAll();
                }
            }
        }
    }
}
