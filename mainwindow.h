#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "optim_param.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    const double XMIN = 70;
    const double XMAX = 674;
    const double YMIN = 14;
    const double YMAX = 661;
public:
    MainWindow(QWidget * parent = nullptr);
    ~MainWindow();
    void Draw(QCustomPlot * customPlot);
    Optim_param optim_param;
private slots:
    void on_functionBox_currentIndexChanged(int index);
    void on_x1SpinBox_valueChanged(double arg1);
    void on_x2SpinBox_valueChanged(double value);
    void on_y1SpinBox_valueChanged(double value);
    void on_y2SpinBox_valueChanged(double value);
    void on_num_iter_PRCGBox_valueChanged(int value);
    void on_num_iter_RSSBox_valueChanged(int value);
    void on_optimButton_clicked();
    void mouseClick(QMouseEvent * event);
private:
    Ui::MainWindow * ui;
};

#endif // MAINWINDOW_H
