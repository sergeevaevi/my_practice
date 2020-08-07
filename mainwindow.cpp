#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "structure.h"
#include "datarequest.h"
#include <QErrorMessage>
#include <QMessageBox>
#include <main_function.h>
#include <search_conflict_algorithm.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix (":/img/img/e92727.jpg");
    int w = ui->img->width();
    int h = ui->img->height();
    ui->img->setPixmap(pix.scaled(w, h));
    ui->front_img->setPixmap(pix.scaled(w, h));
    ui->statusbar->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isDataLoaded()
{
    return data_loaded;
}

void MainWindow::setDataLoaded(bool val)
{
    data_loaded = val;
}


void findAllSubstrs(QString &str, QString sym, QVector<QVector<QString>> &time){
    QVector<QString> schedule;
    int k = 0, j = 0;
    while ((j = str.indexOf(sym, j)) != -1) {
        k = j+1;
        if((k = str.indexOf(sym, k)) != -1){
            schedule.push_back(str.mid(j+1, k-j-1));
            k++;
        }
        if(k == -1){
            schedule.push_back(str.mid(j+1, str.length()));
            k++;
        }
        j = j+1;
    }
    time.push_back(schedule);
}

void findAllSubstrsInStream(QString sym, QVector<QVector<QString>> &time, QTextStream & stream){
    QString str;
    while (!stream.atEnd()){
        str = stream.readLine();
        findAllSubstrs(str, sym, time);
    }
}


bool MainWindow::on_actionLoad_data_triggered()
{
    QVector<QVector<QString>> all_info;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open DataFile"), QDir::root().path() , tr("Image Files (*.txt)"));
    QFile file (fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        findAllSubstrsInStream(",", all_info, stream);

        if(stream.status()!= QTextStream::Ok)
        {
            qDebug() << "Err";
            return false;
        }
        file.close();
        data_loaded = true;
        QVector<QVector<QString>> pair_of_times;
        int n = 0;
        for(auto t : all_info){
            for(auto s : t){
                if(n == 4){
                    n = 0;
                }
                if(n < 2){
                    QString str = " " + s;
                    findAllSubstrs(str, " ", pair_of_times);
                }
                n++;
            }
        }
        QVector<QVector<QString>> hours;
        for(auto t : pair_of_times){
            QString str = " :" + t[3];
            findAllSubstrs(str, ":", hours);
        }
        map<QString, int> name_num;
        int asset_num = -1, pair_count = 0;
        vector<Schedule> collision;
        for(auto t : all_info){
            Schedule c;
            c.setDuration((int)t[2].toDouble());
            c.setAssetName(t[3]);
            auto res = name_num.find(t[3]);
            if(res != name_num.end()){
                asset_num = res->second;
            }else{
                asset_num = name_num.size();

                name_num.insert(make_pair(t[3], name_num.size()));
            }
            c.setAssetNum(name_num.size());

            auto ins = name_num.insert(make_pair(t[3], asset_num));
            if(ins.second){
                c.setAssetNum(asset_num);
                asset_num++;
            }else{
                c.setAssetNum(ins.first->second);
            }
            QString day = pair_of_times[pair_count][0];
            QString month = pair_of_times[pair_count][1];
            QString year = pair_of_times[pair_count][2];
            QString hour = hours[pair_count][0];
            QString min = hours[pair_count][1];
            QString sec = hours[pair_count][2];
            c.setTimeAccessStart(day, month, year, hour, min, sec);
            pair_count++;
            day = pair_of_times[pair_count][0];
            month = pair_of_times[pair_count][1];
            year = pair_of_times[pair_count][2];
            hour = hours[pair_count][0];
            min = hours[pair_count][1];
            sec = hours[pair_count][2];
            c.setTimeAccessEnd(day, month, year, hour, min, sec);
            pair_count++;
            collision.push_back(c);
        }
        NUM_REQS = name_num.size();
        auto res = getValuesByConflicts(collision);
        NUM_WINS = res.first;
        NUM_OF_CONFLICTS = res.second;
        data = collision;
//        for(auto o: data){
//            qDebug() << o.number_of_windows;
//        }
        return true;
    }
    return false;
}

void MainWindow::on_actionSave_triggered()
{
    QFile file("output.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        auto labels = main_func(ui, data, result, data_loaded);
        int count = 0;

        for(int j = 0; j < NUM_WINS;j++){
            for(int i = 0; i < NUM_REQS;i++){

                QString str = labels[count]->text()+"\t";
                if(str == "-----\t"){
                    str+="\t";
                }
                stream << str;
                count++;

            }
            stream << "\r\n";

        }
        for (int k = 0; k < NUM_REQS; k++) {

            QString str = labels[count]->text()+"\t\t";
            count++;
            stream << str;

        }

        file.close();
        if (stream.status() != QTextStream::Ok)
        {
            qDebug() << "Error";
        }
    }
}

void MainWindow::on_actionSave_data_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                    tr("Text Files (*.txt)"));
    if (fileName != "") {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream stream(&file);
            auto labels = main_func(ui, data, result, data_loaded);
            int count = 0;

            for(int j = 0; j < NUM_WINS;j++){
                for(int i = 0; i < NUM_REQS;i++){

                    QString str = labels[count]->text()+"\t";
                    if(str == "-----\t"){
                        str+="\t";
                    }
                    stream << str;
                    count++;

                }
                stream << "\r\n";
            }
            for (int k = 0; k < NUM_REQS; k++) {

                QString str = labels[count]->text()+"\t\t";
                count++;
                stream << str;

            }
            file.close();
            if (stream.status() != QTextStream::Ok)
            {
                qDebug() << "Error!";
            }
        } else {
            qDebug() << "Error!";
        }
    }
}

void MainWindow::on_actionRun_triggered()
{
    main_func(ui, data, result, data_loaded);
}

void MainWindow::on_InputAndStart_clicked()
{
    bool check = MainWindow::on_actionLoad_data_triggered();
    if(!check){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Введенные данные некорректны!");
        messageBox.setFixedSize(500,200);
        return;
    }

    MainWindow::on_actionRun_triggered();

}

void MainWindow::on_InputAndStart_2_clicked()
{
    main_func(ui, data, result, data_loaded);
}

void MainWindow::on_action_2_triggered()
{
    QApplication::quit();
}



void MainWindow::on_plot_triggered()
{


        DataRequest* wForm = new DataRequest(this);
        if(data_loaded){
            wForm->plotResult(result, NUM_WINS, NUM_REQS);

        }
        wForm->exec();

        delete wForm;

}
