#ifndef DATAREQUEST_H
#define DATAREQUEST_H

#include <QDialog>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChartView>

// Used to draw bars representing data provided
// grouped into categories
#include <QtCharts/QBarSeries>

// Represents 1 set of bars in a bar chart
#include <QtCharts/QBarSet>

// Displays the color used to represent each
// QBarSet
#include <QtCharts/QLegend>

// Adds categories to the charts axes
#include <QtCharts/QBarCategoryAxis>

// Used to create stacked bar charts
#include <QtCharts/QHorizontalStackedBarSeries>

// Used to create a line chart
#include <QtCharts/QLineSeries>

// Used to change names on axis
#include <QtCharts/QCategoryAxis>

// Used to make Pie Charts
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <search_conflict_algorithm.h>
#include <vector>
namespace Ui {
class DataRequest;
}

class DataRequest : public QDialog
{
    Q_OBJECT

public:
    explicit DataRequest(QWidget *parent = nullptr);

    void failEnd();
    void successEnd();
    void setClicked();
    bool getClickFlag();
    bool getResult();
    void plotResult(std::vector<Schedule> &result, int NUM_WINS, int NUM_REQS);
    ~DataRequest();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DataRequest *ui;
//    QCustomPlot *wGraphic;      // Объявляем объект QCustomPlot
//    QCPCurve *verticalLine;     // Объявляем объект для вертикальной линии
//    QCPItemTracer *tracer;      // Трасировщик по точкам графика
    bool success = false;
    bool clicked = false;
};

#endif // DATAREQUEST_H
