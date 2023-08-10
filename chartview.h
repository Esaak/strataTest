#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>
#include<QFuture>

QT_BEGIN_NAMESPACE
class QScatterSeries;
QT_END_NAMESPACE

class Button;

QT_USE_NAMESPACE

class ChartView: public QChartView
{
    Q_OBJECT

public:
    explicit ChartView(QWidget *parent = 0);

private:
    QSize buttonSize = {70,70};
    QFuture<void> thread;
    QChart *chart;
    QScatterSeries *series;
    Button *startButton;
    Button *pauseButton;
    Button *stopButton;

    Button *createButton(const std::string &iconPath, const QSize &buttonSize, const char *member);
private slots:
    void startButtonClicked();
    void pauseButtonClicked();
    void stopButtonClicked();
};

#endif // CHARTVIEW_H
