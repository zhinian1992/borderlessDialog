#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

enum SizeChangeMode{
    Ver_Top,//向上
    Ver_Bottom,//向下
    Hor_Left,//向左
    Hor_Right,//向右
    FDiag_LT,//左上
    FDiag_RB,//右下
    BDiag_LB,//左下
    BDiag_RT,//右上
    Arrow//正中
};

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    virtual void mouseMoveEvent(QMouseEvent *event)Q_DECL_OVERRIDE;
    virtual void resizeEvent(QResizeEvent *event)Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent *event)Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event)Q_DECL_OVERRIDE;

private:
    SizeChangeMode chageMouseCursor(QPoint point);
private:
    Ui::Dialog *ui;
    bool m_bLeftBtnPress;
    SizeChangeMode m_cursorType;//鼠标状态
    QPoint m_MousePressPos; //鼠标按下位置
    QPoint m_MouseMovePos;  //鼠标移动位置
};

#endif // DIALOG_H
