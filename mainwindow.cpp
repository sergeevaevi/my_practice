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
    //ui->img->hide();
    // main_func(ui);

}

MainWindow::~MainWindow()
{
    delete ui;
}



//    QString t_a;
//    QString t_e;
//    QString dur;
//    QString name;


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

        //        for(auto s : all_info){
        //            qDebug() << "Begin";
        //            qDebug() << "  ;  " << s;
        //            qDebug() << "End";
        //        }
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
//            qDebug() << str;
            findAllSubstrs(str, ":", hours);
        }

//        for(auto s : hours){
//            qDebug() << "in";
//            qDebug() << "    " << s;
//            qDebug() << "out";
//        }
        map<QString, int> name_num;
        int asset_num = 0, pair_count = 0;
        vector<Сollision> collision;
        for(auto t : all_info){
            Сollision c;
            c.setDuration((int)t[2].toDouble());
            c.setAssetName(t[3]);
            auto res = name_num.insert(make_pair(t[3], asset_num));
            if(res.second){
                c.setAssetNum(asset_num);
                asset_num++;
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
        search_conflicts(collision);
        return true;

        //        time tt{30, 23, 5, 10, 7, 2020};
        //        auto timeU = xtmtot(&tt);
        //        qDebug() << timeU;

    }
    return false;
}

void MainWindow::on_actionSave_triggered()
{
    QFile file("output.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        auto labels = main_func(ui);
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
            auto labels = main_func(ui);
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
    main_func(ui);
}

void MainWindow::on_InputAndStart_clicked()
{
    bool check = MainWindow::on_actionCorrect_data_triggered();
    if(!check){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Введенные данные некорректны!");
        messageBox.setFixedSize(500,200);
        return;
    }
    check = MainWindow::on_actionLoad_data_triggered();
    if(!check){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Введенные данные некорректны!");
        messageBox.setFixedSize(500,200);
        return;
    }
    MainWindow::on_actionRun_triggered();

}

bool MainWindow::on_actionCorrect_data_triggered()
{
    bool result = false;
    DataRequest* wForm = new DataRequest;
    wForm->exec();
    while(!wForm->getClickFlag()){
        ;;
    }
    if(wForm->getResult()){
        result = true;
        NUM_REQS = wForm->getNumReq();
        NUM_WINS = wForm->getNumWin();
        NUM_OF_CONFLICTS = wForm->getNumOfConflicts();
    }
    delete wForm;
    return result;
}

