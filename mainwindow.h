#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <time.h>
#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QLabel>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <vector>
#include <search_conflict_algorithm.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool isDataLoaded();
    void setDataLoaded(bool val);

    std::vector<Schedule> result;
private slots:
    bool on_actionLoad_data_triggered();

    void on_actionSave_triggered();

    void on_actionSave_data_triggered();

    void on_actionRun_triggered();

    void on_InputAndStart_clicked();

    void on_InputAndStart_2_clicked();

    void on_action_2_triggered();

    void on_plot_triggered();

private:
    Ui::MainWindow *ui;
    bool data_loaded = false;
    std::vector<Schedule> data;
};

#endif // MAINWINDOW_H
