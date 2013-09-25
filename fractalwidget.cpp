#include "fractalwidget.h"

FractalWidget::FractalWidget(QWidget *parent) : QLabel(parent)
{
    select_rect = new QRubberBand(QRubberBand::Rectangle, this);
}

void FractalWidget::mousePressEvent(QMouseEvent *e)
{
    origin = e->pos();
    select_rect->setGeometry(QRect(origin, QSize()));
    select_rect->show();
}

void FractalWidget::mouseMoveEvent(QMouseEvent *e)
{
//    select_rect->setGeometry(QRect(origin, e->pos()).normalized());
    select_rect->setGeometry(QRect(origin, QPoint(e->pos().x(), origin.y() + e->pos().x() - origin.x())).normalized());
}

void FractalWidget::mouseReleaseEvent(QMouseEvent *e)
{
    select_rect->hide();

    emit mouse_released(select_rect->geometry().topLeft().x(),
                        select_rect->geometry().topLeft().y(),
                        std::min(select_rect->geometry().bottomRight().x(), width()),
                        std::min(select_rect->geometry().bottomRight().y(), height())
                        );
}
