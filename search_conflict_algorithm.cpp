#include <search_conflict_algorithm.h>
#include <QDebug>

std::map<QString, s32_t> months_lit{
    {"Jun", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4}, {"May", 5}, {"June", 6},
    {"July", 7}, {"Aug", 8}, {"Sept", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12},
};

void gebugConflicts(long min_end_time_i, long max_end_time_i, long min_end_time_j, long max_end_time_j){
        time t;
        qDebug() << "--------";
        qDebug() << "---min_1";
        xttotm(&t, min_end_time_i);
        print_time(&t);
        qDebug() << "---max_1";
        xttotm(&t, max_end_time_i);
        print_time(&t);
        qDebug() << "---min_2";
        xttotm(&t, min_end_time_j);
        print_time(&t);
        qDebug() << "---max_2";
        xttotm(&t, max_end_time_j);
        print_time(&t);
}

bool checkForCollisions(Schedule i, Schedule j){

    long max_end_time_i = i.getTimeAccessEnd() ;//+ i.getDuration();

    long max_end_time_j = j.getTimeAccessEnd() ;//+ j.getDuration();

    long min_end_time_j = j.getTimeAccessStart() + j.getDuration();

    long min_end_time_i = i.getTimeAccessStart() + i.getDuration();

    bool different_time_l = (i.getTimeAccessStart() < j.getTimeAccessStart() && i.getTimeAccessEnd() < j.getTimeAccessEnd());
    bool different_time_m = (i.getTimeAccessStart() > min_end_time_j && i.getTimeAccessEnd() > max_end_time_j );
    bool not_collided_l = (min_end_time_i < j.getTimeAccessStart()) &&  (max_end_time_i < j.getTimeAccessEnd()) ;
    bool not_collided_m = (min_end_time_i > min_end_time_j) &&  (max_end_time_i > max_end_time_j) ;
    if((different_time_l && not_collided_l) || (different_time_m && not_collided_m)){

        return true;
    }

    return false;
}

pair<int, int> getValuesByConflicts(vector<Schedule> all_satellites){
    map<int, int> windows_numbers;
    map<int, int> windows_numbers_for_each;
    Schedule d;
    int max_num_of_win = 0;
    int num = 0;
    unsigned long i, j;
    for(i = 0; i < all_satellites.size(); i++){
        auto find = windows_numbers.find(all_satellites[i].getAssetNum());
        num = 0;
        if(find != windows_numbers.end()){
            find->second++;
            num = find->second;
        }else{
            windows_numbers.insert(make_pair(all_satellites[i].getAssetNum(), 0));
        }
        if(num > max_num_of_win){
            max_num_of_win = num;
        }
        all_satellites[i].number_of_windows = num;
        windows_numbers_for_each.insert(make_pair(i, num));
    }

    int all_conflicts_num = 0;
    int skip = 1;
    for(i = 0; i < all_satellites.size(); i+=skip){
        skip = 1;
        int collision_num = 0;
        for(j = i+1; j < all_satellites.size(); j++){
            if(!checkForCollisions(all_satellites[i], all_satellites[j])){
                if(collision_num != 0){
                    skip++;
                    all_conflicts_num--;
                }else{
//                    qDebug() ;
//                    qDebug() << "ConflictWinSubset[" << all_conflicts_num <<  "].lpConfW[" << collision_num <<
//                                "]  ==>  &C[" << all_satellites[i].getAssetNum() << "].Win[" << windows_numbers_for_each.find(i)->second << "];" <<
//                                all_satellites[i].getAssetName()<< all_satellites[i].getAssetNum() << all_satellites[j].getAssetName();
                    skip = 1;
                }
//                qDebug() << "ConflictWinSubset[" << all_conflicts_num <<  "].lpConfW[" << collision_num+1 <<
//                            "]  ==>  &C[" << all_satellites[j].getAssetNum() << "].Win[" << windows_numbers_for_each.find(j)->second << "];" <<
//                            all_satellites[j].getAssetName() << all_satellites[j].getAssetNum() << all_satellites[i].getAssetName() ;

                collision_num++;
                all_conflicts_num++;
            }
        }

        skip = collision_num + 1;
    }
    return make_pair(max_num_of_win+1, all_conflicts_num);
}

void debugTiming(Schedule i, Schedule j){
    time t;
    qDebug() << "1 st";
    xttotm(&t, i.getTimeAccessStart());
    print_time(&t);
    qDebug() << "1 end";
    xttotm(&t, i.getTimeAccessEnd());
    print_time(&t);

    qDebug() << "2 st";
    xttotm(&t, j.getTimeAccessStart());
    print_time(&t);
    qDebug() << "2 end";
    xttotm(&t, j.getTimeAccessEnd());
    print_time(&t);
    qDebug() << "============";
}

void setBySearchingConflicts(vector<Schedule> all_satellites, Conflict * ConflictWinSubset, Contact * C)
{
    map<int, int> windows_numbers;
    map<int, int> windows_numbers_for_each;
    Schedule d;
    int num = 0;
    for(unsigned int i = 0; i < all_satellites.size(); i++){
        auto find = windows_numbers.find(all_satellites[i].getAssetNum());
        num = 0;
        if(find != windows_numbers.end()){
            find->second++;
            num = find->second;
        }else{
            windows_numbers.insert(make_pair(all_satellites[i].getAssetNum(), 0));
        }
        windows_numbers_for_each.insert(make_pair(i, num));
    }
    int all_conflicts_num = 0;
    int skip = 1;
    for(unsigned int i = 0; i < all_satellites.size(); i+=skip){
        skip = 1;
        int collision_num = 0;
        for(unsigned int j = i+1; j < all_satellites.size(); j++){

            if(!checkForCollisions(all_satellites[i], all_satellites[j])){
                if(collision_num != 0){
                    skip++;
                    all_conflicts_num--;

                }else{
//                   qDebug() ;
//                    qDebug() << "ConflictWinSubset[" << all_conflicts_num <<  "].lpConfW[" << collision_num <<
//                                "]  ==>  &C[" << all_satellites[i].getAssetNum() << "].Win[" << windows_numbers_for_each.find(i)->second << "];"

//                                << all_satellites[i].getAssetName()<< all_satellites[i].getAssetNum() << all_satellites[j].getAssetName()
                                ;

                    ConflictWinSubset[all_conflicts_num].lpConfW[collision_num] = &C[all_satellites[i].getAssetNum()].Win[windows_numbers_for_each.find(i)->second];

                    skip = 1;
                }

//                qDebug() << "ConflictWinSubset[" << all_conflicts_num <<  "].lpConfW[" << collision_num+1 <<
//                            "]  ==>  &C[" << all_satellites[j].getAssetNum() << "].Win[" << windows_numbers_for_each.find(j)->second << "];"
//                            << all_satellites[j].getAssetName() << all_satellites[j].getAssetNum() << all_satellites[i].getAssetName()
                            ;
                ConflictWinSubset[all_conflicts_num].lpConfW[collision_num+1] = &C[all_satellites[j].getAssetNum()].Win[windows_numbers_for_each.find(j)->second];

                collision_num++;
                all_conflicts_num++;

            }
        }
        skip = collision_num + 1;
    }
}

xtime_t Schedule::getTimeAccessStart()
{
    return access_start;
}

xtime_t Schedule::getTimeAccessEnd()
{
    return access_end;
}

int Schedule::getDuration()
{
    return duration;
}

QString Schedule::getAssetName()
{
    return asset_name;
}

void Schedule::setTimeAccessStart(xtime_t tm)
{
    access_start = tm;
}

void Schedule::setTimeAccessEnd(QString day, QString month, QString year, QString hour, QString min, QString sec)
{
    int month_num = 0;
    auto find_month_int = months_lit.find(month);
    if(find_month_int != months_lit.end()){
        month_num = find_month_int->second;
    }else{
        qDebug() << "Error";
    }
    time t;
    t.tm_mday = day.toInt();
    t.tm_mon = month_num;
    t.tm_year = year.toInt();
    t.tm_hour = hour.toInt();
    t.tm_min = min.toInt();
    t.tm_sec = (long)sec.toDouble();
    xtime_t timeU = xtmtot(&t);
    access_end = timeU;
    // qDebug() << timeU;

}

void Schedule::setTimeAccessEnd(xtime_t tm)
{
    access_end = tm;
}

void Schedule::setDuration(int dur)
{
    duration = dur;
}

void Schedule::setAssetName(string nm)
{
    asset_name = QString(nm.c_str());
}

void Schedule::setAssetName(QString nm)
{
    asset_name = nm;
}

void Schedule::setAssetNum(int nm)
{
    asset_num = nm;
}

int Schedule::getAssetNum()
{
    return asset_num;
}

void Schedule::setTimeAccessStart(QString day, QString month, QString year, QString hour, QString min, QString sec)
{
    int month_num = 0;
    auto find_month_int = months_lit.find(month);
    if(find_month_int != months_lit.end()){
        month_num = find_month_int->second;
    }else{
        qDebug() << "Error";
    }
    time t;
    t.tm_mday = day.toInt();
    t.tm_mon = month_num;
    t.tm_year = year.toInt();
    t.tm_hour = hour.toInt();
    t.tm_min = min.toInt();
    t.tm_sec = (long)sec.toDouble();
    xtime_t timeU = xtmtot(&t);
    access_start = timeU;
}

