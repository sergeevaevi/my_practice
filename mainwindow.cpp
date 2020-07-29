#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "second_window.h"
#include "datarequest.h"
#include <QErrorMessage>
#include <QMessageBox>
#include <main_function.h>

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
        //                qDebug() << "J Found , tag at index position" << j;
        k = j+1;
        if((k = str.indexOf(sym, k)) != -1){
            //                    qDebug() << "To J K Found , tag at index position" << k;
            schedule.push_back(str.mid(j+1, k-j-1));
            //                    qDebug() << str.mid(j+1, k-j-1);
            k++;
        }
        if(k == -1){
            //                    qDebug() << "To J Found , tag at index position" << k;
            schedule.push_back(str.mid(j+1, str.length()));
            //                    qDebug() << str.mid(j+1, str.length());
            k++;
        }
        j = j+1;
    }
    //            qDebug() << str;
    time.push_back(schedule);
}

void findAllSubstrsInStream(QString sym, QVector<QVector<QString>> &time, QTextStream & stream){
    QString str;
    while (!stream.atEnd()){
        str = stream.readLine();
        findAllSubstrs(str, sym, time);
//        int k, j = 1;
//        QVector<QString> schedule;

//        while ((j = str.indexOf(sym, j)) != -1) {
//            //                qDebug() << "J Found , tag at index position" << j;
//            k = j+1;
//            if((k = str.indexOf(sym, k)) != -1){
//                //                    qDebug() << "To J K Found , tag at index position" << k;
//                schedule.push_back(str.mid(j+1, k-j-1));
//                //                    qDebug() << str.mid(j+1, k-j-1);
//                k++;
//            }
//            if(k == -1){
//                //                    qDebug() << "To J Found , tag at index position" << k;
//                schedule.push_back(str.mid(j+1, str.length()));
//                //                    qDebug() << str.mid(j+1, str.length());
//                k++;
//            }
//            j = j+1;
//        }
//        //            qDebug() << str;
//        time.push_back(schedule);
    }
}


bool MainWindow::on_actionLoad_data_triggered()
{
    QVector<QVector<QString>> time;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open DataFile"), QDir::root().path() , tr("Image Files (*.txt)"));
    QFile file (fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        findAllSubstrsInStream(",", time, stream);
        //        QString str;
        //        while (!stream.atEnd())
        //        {
        //            str = stream.readLine();
        //            int k, j = 1;
        //            QVector<QString> schedule;

        //            while ((j = str.indexOf(",", j)) != -1) {
        ////                qDebug() << "J Found , tag at index position" << j;
        //                k = j+1;
        //                if((k = str.indexOf(",", k)) != -1){
        ////                    qDebug() << "To J K Found , tag at index position" << k;
        //                    schedule.push_back(str.mid(j+1, k-j-1));
        ////                    qDebug() << str.mid(j+1, k-j-1);
        //                    k++;
        //                }
        //                if(k == -1){
        ////                    qDebug() << "To J Found , tag at index position" << k;
        //                    schedule.push_back(str.mid(j+1, str.length()));
        ////                    qDebug() << str.mid(j+1, str.length());
        //                    k++;
        //                }
        //                j = j+1;
        //            }
        ////            qDebug() << str;
        //            time.push_back(schedule);


        if(stream.status()!= QTextStream::Ok)
        {
            qDebug() << "Err";
            return false;
        }
        file.close();

        for(auto s : time){
            qDebug() << "Begin";
            qDebug() << "  ;  " << s;
            qDebug() << "End";
        }
        QVector<QVector<QString>> times;
        for(auto t : time){
            int n = 0;
            for(auto s : t){
                if(n < 2){
                    findAllSubstrs(s, " ", times);

                }
            }
        }

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

