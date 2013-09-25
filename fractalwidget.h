#ifndef FRACTALWIDGET_H
#define FRACTALWIDGET_H

#include <QtWidgets/QLabel>
#include <QtWidgets/QRubberBand>
#include <QMouseEvent>

class FractalWidget : public QLabel
{
    Q_OBJECT
public:
    FractalWidget(QWidget *parent = 0);

    QRubberBand *select_rect;

    QPoint origin;

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

    void mouse_released(int xt, int yt, int xb, int yb);

public slots:
};

#endif // FRACTALWIDGET_H
