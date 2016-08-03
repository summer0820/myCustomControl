#ifndef CPATHEDIT_H
#define CPATHEDIT_H
#include "stdafx.h"

/*
*  自定义QLineEdit
*  重写QLineEdit::focusInEvent事件，在鼠标进入焦点时，向父窗体发送进入编辑状态信号，用于设置父窗体鼠标状态的显示
*  重新QLineEdit::focusOutEvent事件，在鼠标离开焦点是，向父窗体发送退出编辑状态信号，用于设置父窗体鼠标状态的显示
*/
class CLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    CLineEdit(QWidget *parent = 0);
    ~CLineEdit();

protected:
    void focusInEvent (QFocusEvent* event);
    void focusOutEvent (QFocusEvent* event);

signals:
    void sigFocusIn();
    void sigFocusOut();
};


/*
*  路径编辑框（可点击浏览按钮输入路径，也可以手动输入需要的路径）
*  提供路径长度限制功能
*  提供手动输入路径功能开关
*/
class CPathEdit : public QLabel
{
    Q_OBJECT
public:
    enum
    {
        FILE = 0,
        DIR = 1,
    };

    CPathEdit(QWidget *parent = 0, int fileDlgFlag = FILE);
    ~CPathEdit();

    /*
    * 设置路径长度限制，以字节计算， nSize = -1为长度限制
    */
    void      setTextSize(int nSize);

    /*
    * 获取路径限制长度， -1为无限制
    */
    int       getTextSize();

    void      setBrowserButtonHeight(int nHeight);
    void      updateBrowserState();

    /*
    * 设置浏览按钮的objectName，用来通过Qss文件设置风格，如果不调用这个函数，则使用默认风格
    */
    void      setBrowserObjectName(QString objectName);
    QString   getBrowserObjectName();

    /*
    *  设置路径输入框objectName, 用来通过qss文件设置风格，如果不调用这个函数，则使用默认风格
    */
    void      setLineEditObjectName(QString objectName);
    QString   getLineEditObjectName();

    /*
    * 设置鼠标移动到控件上样式 eg:
    * QString style = "QLable{border:1px solid gray};"
    *                 "QLineEdit{background: gray;}"
    *                 "QPushButton{background:blue;}"
    */
    void      setMouseHoverStyle(QString styleSheet);

    /*
    * 设置鼠标有焦点处于编辑状态时控件样式 eg:
    * QString style = "QLable{border:1px solid gray};"
    *                 "QLineEdit{background: gray;}"
    *                 "QPushButton{background:blue;}"
    */
    void      setMouseFocusStyle(QString styleSheet);

    /*
    * 设置控件正常状态下样式 eg:
    * QString style = "QLable{border:1px solid gray};"
    *                 "QLineEdit{background: gray;}"
    *                 "QPushButton{background:blue;}"
    */
    void      setNormalstyle(QString styleSheet);

    /*
    * 设置占位符文本
    */
    void      setPlaceholderText(QString strText);
    QString   getPlaceHolderText();

    /*
    * 设置是否允许手动输入，b == true只读，不允许手动输入
    */
    void      setReadOnly(bool b);
    bool      isReadOnly();

    /*
    *  获取选择或者输入的路径
    */
    QString   getPath();

    /*
     * 设置文本显示的路径
     * strPath   用户选择的路径
     */
    void      setPath(QString strPath);

    void      setWarinPixmap(QString pixmap);
    QString   getWarinPixmap();

    /*
    *  设置QFileDialog文件过滤器
    */
    void      setFilter(QString filter);
    QString   getFilter();

    void      clearText();

protected:
    void      enterEvent (QEvent * event);
    void      leaveEvent(QEvent *event);

private:
    void         initUI();

    CLineEdit    *m_pwndLineEdit;
    QPushButton  *m_pbtnBrowser;
    QString      m_strPath;

    QString      m_strBroserObject;
    QString      m_strLineEditObject;

    QString      m_strNormalStyle;
    QString      m_strHoverStyle;
    QString      m_strFocusStyle;

    QString      m_strPlaceholderText;
    QString      m_strFilter;

    QString      m_strWarinPixmap;
    int          m_nFileDlgFlag;

    int          m_nLenth;

private slots:
    /*
    * 触发浏览按钮点击事件，弹出浏览框
    */
    void         sltBrowserSavePath();

    /*
    * 根据路径长度限制，检测路径长度合法性，不合法弹出警告框
    */
    void         sltCheckPathLength(QString strText);

    /*
    * 设置编辑状态风格
    */
    void         sltSetFocusStyle();

    /*
    * 设置非编辑状态风格
    */
    void         sltSetNorStyle();

signals:
    /*
    * 路径选择完成，发送信号，参数为选择的路径
    */
    void         sigSelectedPath(QString strPath);
    void         sigInput();
};

#endif // CPATHEDIT_H
