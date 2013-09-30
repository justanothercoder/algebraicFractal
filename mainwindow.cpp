#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    func = [this](Complex z){ return z * z + this->c; };

    image_width = 300;
    image_height = 300;
    image = new QImage(image_width, image_height, QImage::Format_ARGB32);

    layout = new QVBoxLayout(this);

    fractal = new FractalWidget();
    fractal->setPixmap(QPixmap::fromImage(*image));

    c_re_edit = new QLineEdit("0.37");
    c_im_edit = new QLineEdit("0.41");

    infinity_edit = new QLineEdit("2");
    iterations_edit = new QLineEdit("50");

    red_factor_edit = new QLineEdit("3.0");
    green_factor_edit = new QLineEdit("2.0");
    blue_factor_edit = new QLineEdit("3.0");

    upper_left_corner_x_edit = new QLineEdit("-5");
    upper_left_corner_y_edit = new QLineEdit("-5");
    lower_right_corner_x_edit = new QLineEdit("5");
    lower_right_corner_y_edit = new QLineEdit("5");

    input = new QWidget();
    input_layout = new QFormLayout(input);
    input_layout->addRow("C_x: ", c_re_edit);
    input_layout->addRow("C_y: ", c_im_edit);
    input_layout->addRow("infinity: ", infinity_edit);
    input_layout->addRow("iterations: ", iterations_edit);
    input_layout->addRow("red factor: ", red_factor_edit);
    input_layout->addRow("green factor: ", green_factor_edit);
    input_layout->addRow("blue factor: ", blue_factor_edit);

    input_layout->addRow("upper left corner x: ", upper_left_corner_x_edit);
    input_layout->addRow("upper left corner y: ", upper_left_corner_y_edit);
    input_layout->addRow("lower right corner x: ", lower_right_corner_x_edit);
    input_layout->addRow("lower right corner y: ", lower_right_corner_y_edit);

    paint_button = new QPushButton("paint");

    layout->addWidget(fractal);
    layout->addWidget(input);
    layout->addWidget(paint_button);

    connect(paint_button, SIGNAL(clicked()), this, SLOT(button_paint_slot()));
    connect(fractal, SIGNAL(mouse_released(int, int, int, int)), this, SLOT(mouse_released_slot(int, int, int, int)));
}

int MainWindow::when_goes_to_infinity(Complex z)
{
    int iteration = 1;
    while ( z.abs() < infinity && iteration <= iterations )
    {
        z = func(z);
        ++iteration;
    }

//    return (z.abs() >= infinity ? iteration : 0);
    return iteration - 1;
}

Complex MainWindow::get_complex(int i, int j)
{
    Complex d = (lower_right_corner - upper_left_corner);

    return upper_left_corner + Complex(d.x * i / image_width, d.y * j / image_height);
}

void MainWindow::button_paint_slot()
{
    upper_left_corner.x = upper_left_corner_x_edit->text().toDouble();
    upper_left_corner.y = upper_left_corner_y_edit->text().toDouble();

    lower_right_corner.x = lower_right_corner_x_edit->text().toDouble();
    lower_right_corner.y = lower_right_corner_y_edit->text().toDouble();

    emit paint_slot();
}

void MainWindow::paint_slot()
{
    c = Complex(c_re_edit->text().toDouble(), c_im_edit->text().toDouble());
    infinity = infinity_edit->text().toDouble();
    iterations = iterations_edit->text().toInt();

    red_factor = red_factor_edit->text().toDouble();
    green_factor = green_factor_edit->text().toDouble();
    blue_factor = blue_factor_edit->text().toDouble();

    uchar* bit = image->bits();

    for ( int i = 0; i < image_height; ++i )
    {
        for ( int j = 0; j < image_width; ++j )
        {
            Complex z0 = get_complex(j, i);
            int iter = when_goes_to_infinity(z0);

            double sum = (blue_factor + green_factor + red_factor) / 3;

//            iter = (iterations - iter);
/*
 *  normal
 *
            *bit = std::min(255, (int)(255 * blue_factor / sum * iter * iter / iterations)); ++bit;  //blue
            *bit = std::min(255, (int)(255 * green_factor / sum * iter * iter / iterations)); ++bit;  //green
            *bit = std::min(255, (int)(255 * red_factor / sum * iter * iter / iterations)); ++bit;  //red
*/
/*
 *  modular
 *
            *bit = (int)(255 * blue_factor * iter * iter / iterations / sum); ++bit;  //blue
            *bit = (int)(255 * green_factor * iter * iter / iterations / sum); ++bit;  //green
            *bit = (int)(255 * red_factor * iter * iter / iterations / sum); ++bit;  //red
*/
            *bit = 255; ++bit;  //alpha
        }
    }

    fractal->setPixmap(QPixmap::fromImage(*image));
}

void MainWindow::mouse_released_slot(int xt, int yt, int xb, int yb)
{
    Complex tmp1 = get_complex(xt, yt), tmp2 = get_complex(xb, yb);

    upper_left_corner = tmp1;
    lower_right_corner = tmp2;

    upper_left_corner_x_edit->setText(QString("%1").arg(upper_left_corner.x));
    upper_left_corner_y_edit->setText(QString("%1").arg(upper_left_corner.y));

    lower_right_corner_x_edit->setText(QString("%1").arg(lower_right_corner.x));
    lower_right_corner_y_edit->setText(QString("%1").arg(lower_right_corner.y));

    emit paint_button->clicked();
}
