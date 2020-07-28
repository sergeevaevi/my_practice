#include "second_window.h"
#include "ui_second_window.h"

second_window::second_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::second_window)
{
    ui->setupUi(this);
}

second_window::~second_window()
{
    delete ui;
}
