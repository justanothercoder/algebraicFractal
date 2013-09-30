#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFormLayout>
#include <QDebug>

#include <functional>
#include "complex.h"
#include "fractalwidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    QLayout *layout;

    FractalWidget *fractal;

    QWidget *input;
    QFormLayout *input_layout;

    QLineEdit *c_re_edit,
              *c_im_edit,
              *infinity_edit,
              *iterations_edit,
              *red_factor_edit,
              *green_factor_edit,
              *blue_factor_edit;

   QLineEdit *upper_left_corner_x_edit,
             *upper_left_corner_y_edit,
             *lower_right_corner_x_edit,
             *lower_right_corner_y_edit;

    QPushButton *paint_button;

    int image_width,
        image_height;

    QImage *image;

    Complex upper_left_corner,
            lower_right_corner,
            c;

    double infinity,
           red_factor,
           green_factor,
           blue_factor;

    int iterations;

    Complex get_complex(int i, int j);

    int when_goes_to_infinity(Complex z);

    std::function<Complex(Complex)> func;

signals:

public slots:
    void paint_slot();
    void button_paint_slot();
    void mouse_released_slot(int xt, int yt, int xb, int yb);
};

#endif // MAINWINDOW_H
