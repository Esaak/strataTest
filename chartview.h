#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>

QT_BEGIN_NAMESPACE
class QScatterSeries;
class QToolButton;
QT_END_NAMESPACE

class Button;

QT_USE_NAMESPACE

class ChartView: public QChartView
{
    Q_OBJECT

public:
    explicit ChartView(QWidget *parent = 0);

private:
    QTimer *timer;
    QSize buttonSize = {70,70};

    QChart *chart;
    QScatterSeries *series;

    Button *createButton(const std::string &iconPath, const QSize &buttonSize, const char *member);
private slots:
    void startButtonClicked();
    void pauseButtonClicked();
    void stopButtonClicked();
};

#endif // CHARTVIEW_H
