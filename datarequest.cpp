#include "datarequest.h"
#include "ui_datarequest.h"
#include "QDebug"

DataRequest::DataRequest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataRequest)
{
    ui->setupUi(this);
}

void DataRequest::setNumReq(int num){
    NumReqs = num;
}

void DataRequest::setNumWin(int num){
    NumWins = num;
}

void DataRequest::setNumOfConflicts(int num){
    NumOfConflicts = num;
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

int DataRequest::getNumReq(){
    return NumReqs;
}

int DataRequest::getNumWin(){
    return NumWins;
}

int DataRequest::getNumOfConflicts(){
    return NumOfConflicts;
}

DataRequest::~DataRequest()
{
    delete ui;
}

void DataRequest::on_pushButton_clicked()
{
    successEnd();
    bool check = false;
    int buf[3];
    buf[0] = this->NumReqs;
    this->setNumReq(ui->NumReqLine->text().toInt(&check));
    if(!check){
        failEnd();
        NumReqs = buf[0];
        this->close();
    }
    buf[1] = this->NumWins;
    this->setNumWin(ui->NumWinLine->text().toInt(&check));
    if(!check){
        failEnd();
        NumReqs = buf[0];
        NumWins = buf[1];
        this->close();
    }
    buf[2] = this->NumOfConflicts;
    this->setNumOfConflicts(ui->NumConfLine->text().toInt(&check));
    if(!check){
        failEnd();
        NumReqs = buf[0];
        NumWins = buf[1];
        NumOfConflicts = buf[2];
    }
    this->close();
    setClicked();
}

void DataRequest::on_pushButton_2_clicked()
{
   this->close();
}
