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
    main_func(ui);

}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::on_actionLoad_data_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open DataFile"), QDir::root().path() , tr("Image Files (*.txt)"));
    QFile file (fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        while (!stream.atEnd())
        {
            str = stream.readLine();
            int j = 0;

            while ((j = str.indexOf(" ", j)) != -1) {
                qDebug() << "Found " " tag at index position" << j;
                ++j;
            }
            qDebug() << str;
        }
        if(stream.status()!= QTextStream::Ok)
        {
            qDebug() << "Err";
            return false;
        }
        file.close();
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
