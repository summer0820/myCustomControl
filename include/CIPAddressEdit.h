#ifndef CIPADDRESSEDIT_H
#define CIPADDRESSEDIT_H
#include "stdafx.h"
class CIPPartlineEdit;

class  CIPAddressEdit : public QFrame
{
    Q_OBJECT
public:
    CIPAddressEdit(QWidget* pParent = 0);
    ~CIPAddressEdit();

    void      setText(const QString &getext);
    QString   getText();
    void      setStyleSheet(const QString &styleSheet);
    void      setHeight(int nHeight);
    void      setDotAlignment(Qt::Alignment n);
    void      setDotObjectName(QString name);

    void      setReadOnly(bool b);

signals:
    void sigTextchanged(const QString& getext);
    void sitTextEdited(const QString &getext);

private slots:
    void sltTextChanged(const QString& getext);
    void sltTextEdited(const QString &getext);

private:
    CIPPartlineEdit *m_pIpPart1;
    CIPPartlineEdit *m_pIpPart2;
    CIPPartlineEdit *m_pIpPart3;
    CIPPartlineEdit *m_pIpPart4;

    QLabel         *m_plblDot1;
    QLabel         *m_plblDot2;
    QLabel         *m_plblDot3;
};

#endif // CIPADDRESSEDIT_H
