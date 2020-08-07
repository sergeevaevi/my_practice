#ifndef MAIN_FUNCTION_H
#define MAIN_FUNCTION_H
#include <QVector>
#include <QLabel>
#include <ui_mainwindow.h>
#include <structure.h>
#include <search_conflict_algorithm.h>

int NUM_REQS = 8;               // number of requests количество аппаратов
int NUM_WINS = 14;              // maximum of windows per request
int NUM_OF_CONFLICTS = 25;      // maximum of conflict domains possible


QVector<QLabel*> main_func(Ui::MainWindow * ui, std::vector<Schedule> &data, std::vector<Schedule> &result, bool is_data_loaded);

#endif // MAIN_FUNCTION_H
