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



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    bool on_actionLoad_data_triggered();

    void on_actionSave_triggered();

    void on_actionSave_data_triggered();

    void on_actionRun_triggered();

    void on_InputAndStart_clicked();

    bool on_actionCorrect_data_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
