#include "chartview.h"
#include "button.h"
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLegendMarker>
#include <QTimer>
#include <QtMath>
#include <QtCore/QRandomGenerator>
#include<QGraphicsLayout>
#include <QIcon>
#include <QGridLayout>
#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include<QDebug>

ChartView::ChartView(QWidget *parent):
    QChartView(new QChart(), parent)
{

    chart = new QChart;
    startButton = createButton(std::string{"icon_btn/play-button.png"}, buttonSize, SLOT(startButtonClicked()));
    pauseButton = createButton("icon_btn/pause-button.png", buttonSize, SLOT(pauseButtonClicked()));
    stopButton = createButton("icon_btn/stop-button.png", buttonSize, SLOT(stopButtonClicked()));


    series = new QScatterSeries();
    series->setBorderColor(QColor(0,0,255));
    series->setColor(QColor(0,0,255));
    series->setName("scatter");
    series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series->setMarkerSize(10.0);




    chart->addSeries(series);

    chart->createDefaultAxes();
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);

    chart->setDropShadowEnabled(false);

    chart->legend()->setVisible(false);

    auto chartView = new QChartView(chart, this);


    auto controlWidget = new QWidget(this);
    auto controlLayout = new QGridLayout(controlWidget);


    controlLayout->addWidget(startButton, 0, 0);
    controlLayout->addWidget(pauseButton, 0, 1);
    controlLayout->addWidget(stopButton, 0, 2);
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(chartView);
    mainLayout->addWidget(controlWidget);


}

Button *ChartView::createButton(const std::string &iconPath, const QSize &buttonSize, const char *member)
{
    Button *button = new Button(iconPath, buttonSize);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void ChartView::startButtonClicked()
{
    thread = QtConcurrent::run(
                [this](QPromise<int> &promise) -> void
                {
                    while(true){
                        promise.suspendIfRequested();
                        if (promise.isCanceled())
                            return;
                        series->append(QRandomGenerator::global()->bounded(1.), QRandomGenerator::global()->bounded(1.));
                        QThread::currentThread()->msleep(1000);

                    }
                }

                );
    startButton->setEnabled(false);
}

void ChartView::pauseButtonClicked()
{
    thread.suspend();
    startButton->setEnabled(true);
}

void ChartView::stopButtonClicked()
{
    thread.cancel();
    series->clear();
    startButton->setEnabled(true);
}


