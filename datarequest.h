#ifndef DATAREQUEST_H
#define DATAREQUEST_H

#include <QDialog>

namespace Ui {
class DataRequest;
}

class DataRequest : public QDialog
{
    Q_OBJECT

public:
    explicit DataRequest(QWidget *parent = nullptr);
    void setNumReq(int num);
    void setNumWin(int num);
    void setNumOfConflicts(int num);
    void failEnd();
    void successEnd();
    void setClicked();
    bool getClickFlag();
    bool getResult();
    int getNumReq();
    int getNumWin();
    int getNumOfConflicts();
    ~DataRequest();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DataRequest *ui;
    int NumReqs = 8;               // number of requests количество аппаратов
    int NumWins = 14;              // maximum of windows per request
    int NumOfConflicts = 25;      // maximum of conflict domains possible
    bool success = false;
    bool clicked = false;
};

#endif // DATAREQUEST_H
