#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>


MainWindow::MainWindow(QWidget * parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Graph, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(mouseClick(QMouseEvent *)));

    optim_param.func_num = ui->functionBox->currentIndex();
    optim_param.dom_x1 = ui->x1SpinBox->value();
    optim_param.dom_x2 = ui->x2SpinBox->value();
    optim_param.dom_y1 = ui->y1SpinBox->value();
    optim_param.dom_y2 = ui->y2SpinBox->value();
    optim_param.x0 = ui->x0Box->value();
    optim_param.y0 = ui->y0Box->value();
    optim_param.sc_num = ui->scBox->currentIndex();
    optim_param.eps = ui->EPSBox->value();
    optim_param.method_num = ui->methodWidget->currentIndex();
    optim_param.num_iter = ui->num_iter_PRCGBox->value();
    optim_param.p = ui->probBox->value();
    optim_param.coef = ui->coefBox->value();

    optim_param.change_func();
    optim_param.change_rect();
    optim_param.change_init();
    optim_param.change_sc();
    optim_param.change_method();

    Draw(ui->Graph);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_functionBox_currentIndexChanged(int index)
{
    optim_param.func_num = index;
    optim_param.change_func();
    Draw(ui->Graph);
}

void MainWindow::on_x1SpinBox_valueChanged(double value)
{
    optim_param.dom_x1 = value;
    Draw(ui->Graph);
}

void MainWindow::on_x2SpinBox_valueChanged(double value)
{
    optim_param.dom_x2 = value;
    Draw(ui->Graph);
}

void MainWindow::on_y1SpinBox_valueChanged(double value)
{
    optim_param.dom_y1 = value;
    Draw(ui->Graph);
}

void MainWindow::on_y2SpinBox_valueChanged(double value)
{
    optim_param.dom_y2 = value;
    Draw(ui->Graph);
}

void MainWindow::on_num_iter_PRCGBox_valueChanged(int value)
{
    ui->num_iter_RSSBox->setValue(value);
}

void MainWindow::on_num_iter_RSSBox_valueChanged(int value)
{
    ui->num_iter_PRCGBox->setValue(value);
}

void MainWindow::Draw(QCustomPlot * customPlot)
{
    int nX = 200;
    int nY = 200;

    customPlot->clearPlottables();
    customPlot->axisRect()->setupFullAxesBox(true);
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    QCPColorMap * colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    colorMap->data()->setSize(nX, nY);
    colorMap->data()->setRange(QCPRange(optim_param.dom_x1, optim_param.dom_x2), QCPRange(optim_param.dom_y1, optim_param.dom_y2));

    Vector vect(2);
    for (int i = 0; i < nX; ++i)
        for (int j = 0; j < nY; ++j)
        {
            colorMap->data()->cellToCoord(i, j, &vect[0], &vect[1]);
            colorMap->data()->setCell(i, j, (*optim_param.f)(vect));
        }

    QCPColorScale * colorScale = new QCPColorScale(customPlot);
    customPlot->plotLayout()->addElement(0, 1, colorScale);
    colorScale->setType(QCPAxis::atRight);
    colorMap->setColorScale(colorScale);
    colorMap->setGradient(QCPColorGradient::gpPolar);
    colorMap->rescaleDataRange();

    QCPMarginGroup * marginGroup = new QCPMarginGroup(customPlot);
    customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    customPlot->rescaleAxes();
    customPlot->replot();
}

void MainWindow::on_optimButton_clicked()
{
    ui->result->clear();

    optim_param.x0 = ui->x0Box->value();
    optim_param.y0 = ui->y0Box->value();
    optim_param.sc_num = ui->scBox->currentIndex();
    optim_param.eps = ui->EPSBox->value();
    optim_param.method_num = ui->methodWidget->currentIndex();
    optim_param.num_iter = ui->num_iter_PRCGBox->value();
    optim_param.p = ui->probBox->value();
    optim_param.coef = ui->coefBox->value();

    optim_param.change_rect();
    optim_param.change_init();
    optim_param.change_sc();
    optim_param.change_method();
    optim_param.m->optimize();

    QVector <double> xPath = QVector<double>(optim_param.m->xPath.begin(), optim_param.m->xPath.end());
    QVector <double> yPath = QVector<double>(optim_param.m->yPath.begin(), optim_param.m->yPath.end());

    Vector argmin = Vector(2);
    argmin[0] = xPath.back();
    argmin[1] = yPath.back();

    QVector <double> xArgmin = { argmin[0] };
    QVector <double> yArgmin = { argmin[1] };

    QCPCurve * Path = new QCPCurve(ui->Graph->xAxis, ui->Graph->yAxis);
    Path->setData(xPath, yPath);
    Path->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::white), QBrush(Qt::white), 5));
    Path->setPen(QPen(Qt::gray, 2));

    QCPCurve * End = new QCPCurve(ui->Graph->xAxis, ui->Graph->yAxis);
    End->setData(xArgmin, yArgmin);
    End->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::red), QBrush(Qt::red), 8));

    ui->Graph->replot(); 

    ui->result->insertPlainText
            ("Argmin: (" + QString::number(argmin[0]) + "," +
            QString::number(argmin[1]) + ")\n");
    ui->result->insertPlainText
            ("Value: " + QString::number((*optim_param.f)(argmin)) + "\n");
    ui->result->insertPlainText
            ("Number of iterations: " +
             QString::number(optim_param.m->get_total_iter()));

    ui->Graph->QCustomPlot::removePlottable(Path);
    ui->Graph->QCustomPlot::removePlottable(End);
}

void MainWindow::mouseClick(QMouseEvent * event)
{
    ui->Graph->mouseMove(event);
    double xClick = optim_param.dom_x1 + (optim_param.dom_x2 - optim_param.dom_x1) * ((double) event->x() - XMIN)/(XMAX - XMIN);
    double yClick = optim_param.dom_y2 + (optim_param.dom_y1 - optim_param.dom_y2) * ((double) event->y() - YMIN)/(YMAX - YMIN);
    ui->x0Box->setValue(xClick);
    ui->y0Box->setValue(yClick);
    MainWindow::on_optimButton_clicked();
}
