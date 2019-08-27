#include "dialog.h"
#include "ui_dialog.h"
#include <QMouseEvent>
#include <QResizeEvent>
#include <QPoint>
#include <QDebug>
#include <QCursor>

#define BorderSize 5

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    m_bLeftBtnPress(false),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setMouseTracking(true);
    ui->widget->setAttribute(Qt::WA_TransparentForMouseEvents,true);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bLeftBtnPress){
        m_MouseMovePos = event->globalPos();
        int move_width_range = m_MouseMovePos.rx() - m_MousePressPos.rx();
        int move_height_range = m_MouseMovePos.ry() - m_MousePressPos.ry();
        switch (m_cursorType) {
        case Ver_Top:{
            QRect rect = this->geometry();
            rect.setTop(rect.top() + move_height_range);
            if((rect.bottom() - rect.top()) >= 100)
                this->setGeometry(rect);
            m_MousePressPos = m_MouseMovePos;
            break;
        }
        case Ver_Bottom:{
            QRect rect = this->geometry();
            rect.setBottom(rect.bottom() + move_height_range);
            if((rect.bottom() - rect.top()) >= 100)
                this->setGeometry(rect);
            m_MousePressPos = m_MouseMovePos;
            break;
        }
        case Hor_Left:{
            QRect rect = this->geometry();
            rect.setLeft(rect.left() + move_width_range);
            if((rect.right() - rect.left()) >= 100)
                this->setGeometry(rect);
            m_MousePressPos = m_MouseMovePos;
            break;
        }
        case Hor_Right:{
            QRect rect = this->geometry();
            rect.setRight(rect.right() + move_width_range);
            if((rect.right() - rect.left()) >= 100)
                this->setGeometry(rect);
            m_MousePressPos = m_MouseMovePos;
            break;
        }
        case FDiag_LT:{
            QRect rect = this->geometry();
            rect.setTop(rect.top() + move_height_range);
            rect.setLeft(rect.left() + move_width_range);
            if((rect.bottom() - rect.top()) >= 100 && (rect.right() - rect.left()) >= 100)
                this->setGeometry(rect);
            m_MousePressPos = m_MouseMovePos;
            break;
        }
        case FDiag_RB:{
            QRect rect = this->geometry();
            rect.setBottom(rect.bottom() + move_height_range);
            rect.setRight(rect.right() + move_width_range);
            if((rect.bottom() - rect.top()) >= 100 && (rect.right() - rect.left()) >= 100)
                this->setGeometry(rect);
            m_MousePressPos = m_MouseMovePos;
            break;
        }
        case BDiag_LB:{
            QRect rect = this->geometry();
            rect.setBottom(rect.bottom() + move_height_range);
            rect.setLeft(rect.left() + move_width_range);
            if((rect.bottom() - rect.top()) >= 100 && (rect.right() - rect.left()) >= 100)
                this->setGeometry(rect);
            m_MousePressPos = m_MouseMovePos;
            break;
        }
        case BDiag_RT:{
            QRect rect = this->geometry();
            rect.setTop(rect.top() + move_height_range);
            rect.setRight(rect.right() + move_width_range);
            if((rect.bottom() - rect.top()) >= 100 && (rect.right() - rect.left()) >= 100)
                this->setGeometry(rect);
            m_MousePressPos = m_MouseMovePos;
            break;
        }
        case Arrow:{
            m_MouseMovePos = event->globalPos();
            this->move(this->pos() + m_MouseMovePos - m_MousePressPos);
            m_MousePressPos = m_MouseMovePos;
            break;
        }
        default:
            break;
        }
    }
    else{
        m_cursorType = this->chageMouseCursor(event->pos());
    }
    event->accept();
}

void Dialog::resizeEvent(QResizeEvent *event)
{
    ui->widget->setGeometry(1,1,this->width() - 2,this->height() - 2);
    event->accept();
}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        m_bLeftBtnPress = true;
        m_MousePressPos = event->globalPos();
    }
}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    m_bLeftBtnPress = false;
}

SizeChangeMode Dialog::chageMouseCursor(QPoint point)
{
    //judge the mouse point if in custom border change the mouse cursor

    /* Ver_Top */
    if(point.rx() >= BorderSize
            && point.rx() <= (this->width() - 2*BorderSize)
            && point.ry() <= BorderSize){
        this->setCursor(Qt::SizeVerCursor);
        return Ver_Top;
    }

    /* Ver_Bottom */
    if(point.rx() >= BorderSize
            && point.rx() <= (this->width() - 2*BorderSize)
            && point.ry() >= (this->height() - 2*BorderSize)){
        this->setCursor(Qt::SizeVerCursor);
        return Ver_Bottom;
    }

    /* Hor_Left */
    if(point.rx() <= BorderSize
            && point.ry() >= BorderSize
            && point.ry() <= (this->height() - 2*BorderSize)){
        this->setCursor(Qt::SizeHorCursor);
        return Hor_Left;
    }

    /* Hor_Right */
    if(point.rx() >= (this->width() - 2*BorderSize)
            && point.ry() >= BorderSize
            && point.ry() <= (this->height() - 2*BorderSize)){
        this->setCursor(Qt::SizeHorCursor);
        return Hor_Right;
    }

    /* FDiag_LT */
    if(point.rx() <= BorderSize
            && point.ry() <= BorderSize){
        this->setCursor(Qt::SizeFDiagCursor);
        return FDiag_LT;
    }

    /* FDiag_RB */
    if(point.rx() >= (this->width() - 2*BorderSize)
            && point.ry() >= (this->height() - 2*BorderSize)){
        this->setCursor(Qt::SizeFDiagCursor);
        return FDiag_RB;
    }

    /* BDiag_LB */
    if(point.rx() <= BorderSize
            && point.ry() >= (this->height() - 2*BorderSize)){
        this->setCursor(Qt::SizeBDiagCursor);
        return BDiag_LB;
    }

    /* BDiag_RT */
    if(point.rx() >= (this->width() - 2*BorderSize)
            && point.ry() <= BorderSize){
        this->setCursor(Qt::SizeBDiagCursor);
        return BDiag_RT;
    }

    /* Arrow */
    this->setCursor(Qt::ArrowCursor);
    return Arrow;
}
