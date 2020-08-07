#include "datarequest.h"
#include "ui_datarequest.h"
#include "QDebug"
#include <QtCharts/QBarSeries>
#include <structure.h>
// Define the scope for your variables and functions
QT_CHARTS_USE_NAMESPACE

DataRequest::DataRequest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataRequest)
{
    ui->setupUi(this);

    //    // Assign names to the set of bars used
    //    QBarSet *set0 = new QBarSet("Altuve");
    //    QBarSet *set1 = new QBarSet("Martinez");
    //    QBarSet *set2 = new QBarSet("Segura");
    //    QBarSet *set3 = new QBarSet("Simmons");
    //    QBarSet *set4 = new QBarSet("Trout");

    //    // Assign values for each bar
    //    *set0 << 283 << 341 << 313 << 338 << 346 << 335;
    //    *set1 << 250 << 315 << 282 << 307 << 303 << 330;
    //    *set2 << 294 << 246 << 257 << 319 << 300 << 325;
    //    *set3 << 248 << 244 << 265 << 281 << 278 << 313;
    //    *set4 << 323 << 287 << 299 << 315 << 306 << 313;

    //    // Add all sets of data to the chart as a whole
    //    // 1. Bar Chart
    ////    QBarSeries *series = new QBarSeries();

    //    // 2. Stacked bar chart
    //    QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
    //    series->append(set0);
    //    series->append(set1);
    //    series->append(set2);
    //    series->append(set3);
    //    series->append(set4);

    //    // Used to define the bar chart to display, title
    //    // legend,
    //    QChart *chart = new QChart();

    //    // Add the chart
    //    chart->addSeries(series);

    //    // Set title
    //    chart->setTitle("Test");

    //    // Define starting animation
    //    // NoAnimation, GridAxisAnimations, SeriesAnimations
    //    chart->setAnimationOptions(QChart::AllAnimations);

    //    // Holds the category titles
    //    QStringList categories;
    //    categories << "2013" << "2014" << "2015" << "2016" << "2017" << "2018";

    //    // Adds categories to the axes
    //    QBarCategoryAxis *axis = new QBarCategoryAxis();
    //    axis->append(categories);
    //    chart->createDefaultAxes();

    //    // 1. Bar chart
    ////    chart->setAxisX(axis, series);

    //    // 2. Stacked Bar chart
    //     chart->setAxisY(axis, series);

    //    // Define where the legend is displayed
    //    chart->legend()->setVisible(true);
    //    chart->legend()->setAlignment(Qt::AlignBottom);

    //    // Used to display the chart
    //    QChartView *chartView = new QChartView(chart);
    //    chartView->setRenderHint(QPainter::Antialiasing);

    //    // Used to change the palette
    //    QPalette pal = qApp->palette();

    //    // Change the color around the chart widget and text
    //    pal.setColor(QPalette::Window, QRgb(0xffffff));
    //    pal.setColor(QPalette::WindowText, QRgb(0x404044));

    //    // Apply palette changes to the application
    //    qApp->setPalette(pal);
    //  // Create the main app window
    //      ui->gridLayout->addWidget(chartView);


    //     3. Line chart example
    //     Other options here https://doc.qt.io/qt-5.11/qtcharts-customchart-example.html
//    Contact* C_f;
//    QLineSeries *series = new QLineSeries();
//    series->append(0, 1);
//    series->append(1, 1);
//    // Create chart, add data, hide legend, and add axis
//    QChart *chart = new QChart();
//    chart->legend()->hide();
//    chart->addSeries(series);

//    QLineSeries *series2 = new QLineSeries();
//    series2->append(1, 15);
//    series2->append(2, 15);
//    chart->addSeries(series2);
//    QPen pen2;
//    pen2.setWidth(15);
//    series2->setPen(pen2);
//    chart->createDefaultAxes();

//    // Customize the title font
//    QFont font;
//    font.setPixelSize(18);
//    chart->setTitleFont(font);
//    chart->setTitleBrush(QBrush(Qt::black));
//    chart->setTitle("Barry Bonds HRs as Pirate");

//    // Change the line color and weight
//    QPen pen(QRgb(0x000000));
//    pen.setWidth(15);
//    series->setPen(pen);

//    chart->setAnimationOptions(QChart::AllAnimations);

//    // Change the x axis categories
//    //                QCategoryAxis *axisX = new QCategoryAxis();
//    //                for(int i = 5; i < 10; i++){
//    //                    axisX->append("1986",i);
//    //                }
//    //                axisX->append("1986",0);
//    //                axisX->append("1987",1);
//    //                axisX->append("1988",2);
//    //                axisX->append("1989",3);
//    //                axisX->append("1990",4);
//    //                axisX->append("1991",5);
//    //                axisX->append("1992",6);
//    //                chart->setAxisX(axisX, series);

//    // Used to display the chart
//    QChartView *chartView = new QChartView(chart);
//    chartView->setRenderHint(QPainter::Antialiasing);



//    //                  // Create the main app window
//    //                  QMainWindow window;

//    //                  // Set the main window widget
//    //                  window.setCentralWidget(chartView);
//    //                  window.resize(420, 300);
//    //                  window.show();

//    ui->gridLayout->addWidget(chartView);

}



void DataRequest::failEnd()
{
    qDebug() << "Error!";
    success = false;
}

void DataRequest::successEnd()
{
    success = true;
}

void DataRequest::setClicked()
{
    clicked = true;
}

bool DataRequest::getClickFlag()
{
    return clicked;
}

bool DataRequest::getResult()
{
    return success;
}

void DataRequest::plotResult(std::vector<Schedule> &result, int NUM_WINS, int NUM_REQS)
{
//
//
//    series->append(1, 1);
    // Create chart, add data, hide legend, and add axis
//    QChart *chart = new QChart();
    QChartView *chartView = new QChartView;
    chartView->chart()->legend()->hide();
    qDebug() << "max num" << NUM_WINS;
    for(int j = 0; j < result.size();j++){
        qDebug() << result[j].number_of_windows;
    }
    qDebug() << "========";

    for(int j = 0; j < NUM_WINS;j++){
        for(int i = 0; i < NUM_REQS;i++){
            QLineSeries *series = new QLineSeries();
            QCategoryAxis *axisX = new QCategoryAxis();
            axisX->setMin(1577887300);
            axisX->setMax(1578050200);
            if(result[j+i].number_of_windows < NUM_WINS){
                time t;

                auto time_1 = result[j+i].getTimeAccessStart();
                xttotm(&t, time_1);
                qreal x_1 = (qreal)(time_1);
                axisX->append("get_time(&t)",x_1);
                auto time_2 = result[j+i].getTimeAccessEnd();
                xttotm(&t, time_2);
                qreal x_2 = (qreal)(time_2);
                axisX->append("get_time(&t)",x_2);
                qDebug() << j << x_1 << result[j+i].getTimeAccessStart() << x_2 << result[j+i].getTimeAccessEnd();
                series->append(x_1, i);
                series->append(x_2, i);
                chartView->chart()->addSeries(series);
                chartView->chart()->setAxisX(axisX, series);
                QPen pen(QRgb(i+j));
                pen.setWidth(10);
                series->setPen(pen);
            }
        }
    }
//    chartView->chart()->createDefaultAxes();

    // Customize the title font
    QFont font;
    font.setPixelSize(18);
    chartView->chart()->setTitleFont(font);
    chartView->chart()->setTitleBrush(QBrush(Qt::black));
    chartView->chart()->setTitle("Plot");

    // Change the line color and weight



    chartView->chart()->setAnimationOptions(QChart::AllAnimations);

    // Change the x axis categories
    //                QCategoryAxis *axisX = new QCategoryAxis();
    //                for(int i = 5; i < 10; i++){
    //                    axisX->append("1986",i);
    //                }
    //                axisX->append("1986",0);
    //                axisX->append("1987",1);
    //                axisX->append("1988",2);
    //                axisX->append("1989",3);
    //                axisX->append("1990",4);
    //                axisX->append("1991",5);
    //                axisX->append("1992",6);
    //                chart->setAxisX(axisX, series);

    // Used to display the chart
  //  QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->gridLayout->addWidget(chartView);
}


DataRequest::~DataRequest()
{
    delete ui;
}

void DataRequest::on_pushButton_clicked()
{

}

void DataRequest::on_pushButton_2_clicked()
{
    failEnd();
    setClicked();
    this->close();
}
