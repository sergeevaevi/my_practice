#include <search_conflict_algorithm.h>
#include <QDebug>

std::map<QString, s32_t> months_lit{
    {"Jun", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4}, {"May", 5}, {"June", 6},
    {"July", 7}, {"Aug", 8}, {"Sept", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12},
};

bool checkForCollisions(Schedule i, Schedule j){
    time t;
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
//    qDebug() << "--------";
//    qDebug() << "---min_1";
//    xttotm(&t, min_end_time_i);
//    print_time(&t);
//    qDebug() << "---max_1";
//    xttotm(&t, max_end_time_i);
//    print_time(&t);
//    qDebug() << "---min_2";
//    xttotm(&t, min_end_time_j);
//    print_time(&t);
//    qDebug() << "---max_2";
//    xttotm(&t, max_end_time_j);
//    print_time(&t);
    return false;
}

void search_conflicts(vector<Schedule> all_satellites/*Conflict * ConflictWinSubset, Contact * C, int *WINDOWS_BY_REQUEST*/)
{
    int WINDOWS_BY_REQUEST[100];
    Conflict ConflictWinSubset[100];
    Contact C[100];
    /*
    WINDOWS_BY_REQUEST[0]=13;
    WINDOWS_BY_REQUEST[1]=14;
    WINDOWS_BY_REQUEST[2]=12;
    WINDOWS_BY_REQUEST[3]=12;
    WINDOWS_BY_REQUEST[4]=14;
    WINDOWS_BY_REQUEST[5]=13;
    WINDOWS_BY_REQUEST[6]=12;
    WINDOWS_BY_REQUEST[7]=12;

    ConflictWinSubset[0].lpConfW[0] = &C[1].Win[0];
    ConflictWinSubset[0].lpConfW[1] = &C[4].Win[0];

    // blue1
    ConflictWinSubset[1].lpConfW[0] = &C[2].Win[1];
    ConflictWinSubset[1].lpConfW[1] = &C[6].Win[0];

    // orange
    ConflictWinSubset[2].lpConfW[0] = &C[3].Win[1];
    ConflictWinSubset[2].lpConfW[1] = &C[7].Win[1];


    // green2
    ConflictWinSubset[3].lpConfW[0] = &C[1].Win[1];
    ConflictWinSubset[4].lpConfW[1] = &C[5].Win[1];

    //orange2
    ConflictWinSubset[4].lpConfW[0] = &C[1].Win[2];
    ConflictWinSubset[4].lpConfW[1] = &C[4].Win[2];
    ConflictWinSubset[4].lpConfW[2] = &C[5].Win[2];

    // iight green
    ConflictWinSubset[5].lpConfW[0] = &C[0].Win[2];
    ConflictWinSubset[5].lpConfW[1] = &C[2].Win[2];

    // light blue
    ConflictWinSubset[6].lpConfW[0] = &C[1].Win[3];
    ConflictWinSubset[6].lpConfW[1] = &C[4].Win[3];

    // brown
    ConflictWinSubset[7].lpConfW[0] = &C[2].Win[3];
    ConflictWinSubset[7].lpConfW[1] = &C[7].Win[3];

    // dark green
    ConflictWinSubset[8].lpConfW[0] = &C[4].Win[4];
    ConflictWinSubset[8].lpConfW[1] = &C[6].Win[3];

    // red
    ConflictWinSubset[9].lpConfW[0] = &C[2].Win[4];
    ConflictWinSubset[9].lpConfW[1] = &C[3].Win[3];
    ConflictWinSubset[9].lpConfW[2] = &C[7].Win[4];

    //blueblue
    ConflictWinSubset[10].lpConfW[0] = &C[3].Win[4];
    ConflictWinSubset[10].lpConfW[1] = &C[7].Win[5];

    //yellowyellow
    ConflictWinSubset[11].lpConfW[0] = &C[4].Win[5];
    ConflictWinSubset[11].lpConfW[1] = &C[5].Win[5];

    //greengreen
    ConflictWinSubset[12].lpConfW[0] = &C[3].Win[7];
    ConflictWinSubset[12].lpConfW[1] = &C[7].Win[7];

    //brownbrown
    ConflictWinSubset[13].lpConfW[0] = &C[3].Win[8];
    ConflictWinSubset[13].lpConfW[1] = &C[7].Win[8];

    //ll-blue
    ConflictWinSubset[14].lpConfW[0] = &C[4].Win[8];
    ConflictWinSubset[14].lpConfW[1] = &C[5].Win[8];

    //ll-green
    ConflictWinSubset[15].lpConfW[0] = &C[0].Win[8];
    ConflictWinSubset[15].lpConfW[1] = &C[2].Win[8];

    //nice-orange
    ConflictWinSubset[16].lpConfW[0] = &C[2].Win[9];
    ConflictWinSubset[16].lpConfW[1] = &C[5].Win[9];

    //simple-green
    ConflictWinSubset[17].lpConfW[0] = &C[4].Win[10];
    ConflictWinSubset[17].lpConfW[1] = &C[6].Win[9];

    // fiolent
    ConflictWinSubset[18].lpConfW[0] = &C[2].Win[10];
    ConflictWinSubset[18].lpConfW[1] = &C[3].Win[9];
    ConflictWinSubset[18].lpConfW[2] = &C[7].Win[9];

    //super-green
    ConflictWinSubset[19].lpConfW[0] = &C[4].Win[11];
    ConflictWinSubset[19].lpConfW[1] = &C[6].Win[10];

    //redred
    ConflictWinSubset[20].lpConfW[0] = &C[3].Win[10];
    ConflictWinSubset[20].lpConfW[1] = &C[7].Win[10];

    //next-yellow
    ConflictWinSubset[21].lpConfW[0] = &C[3].Win[11];
    ConflictWinSubset[21].lpConfW[1] = &C[7].Win[11];

    //apelsin
    ConflictWinSubset[22].lpConfW[0] = &C[0].Win[11];
    ConflictWinSubset[22].lpConfW[1] = &C[1].Win[12];

    //sky-blue
    ConflictWinSubset[23].lpConfW[0] = &C[4].Win[12];
    ConflictWinSubset[23].lpConfW[1] = &C[5].Win[12];

    //mandarin
    ConflictWinSubset[24].lpConfW[0] = &C[0].Win[12];
    ConflictWinSubset[24].lpConfW[1] = &C[1].Win[13];
*/
    map<int, int> windows_numbers;
    Schedule d;
    qDebug() << all_satellites.size();
    //    vector<Сollision> collisions;// = parseFile();
    for(auto c: all_satellites){
        WINDOWS_BY_REQUEST[c.getAssetNum()]++;
//        auto find = windows_numbers.find(c.getAssetNum());
//        if(find != windows_numbers.end()){
//            find->second++;
//        }else{
//            windows_numbers.insert(make_pair(c.getAssetNum(), 0));
//        }
    }
    time t;
    int conflicts_num = 0;
    for(int i = 0; i < all_satellites.size(); i++){
        int collision_num = 0;
        auto find = windows_numbers.find(all_satellites[i].getAssetNum());
        if(find != windows_numbers.end()){
            find->second++;
        }else{
            windows_numbers.insert(make_pair(all_satellites[i].getAssetNum(), 0));
        }
        for(int j = i+1; j < all_satellites.size(); j++){
            auto find = windows_numbers.find(all_satellites[j].getAssetNum());
            if(find == windows_numbers.end()){
                windows_numbers.insert(make_pair(all_satellites[j].getAssetNum(), 0));
            }
            if(!checkForCollisions(all_satellites[i], all_satellites[j])){
                qDebug() << "ConflictWinSubset[" << conflicts_num <<  "].lpConfW[" << collision_num <<
                            "]  ==>  &C[" << all_satellites[i].getAssetNum() << "].Win[" << windows_numbers.find(all_satellites[i].getAssetNum())->second << "];" <<
                            all_satellites[i].getAssetName()<< all_satellites[i].getAssetNum() << all_satellites[j].getAssetName();
                qDebug() << "ConflictWinSubset[" << conflicts_num <<  "].lpConfW[" << collision_num+1 <<
                            "]  ==>  &C[" << all_satellites[j].getAssetNum() << "].Win[" << windows_numbers.find(all_satellites[j].getAssetNum())->second << "];" <<
                         all_satellites[j].getAssetName() << all_satellites[j].getAssetNum() << all_satellites[i].getAssetName() ;
                qDebug() ;
//                qDebug() << "1 st";
//                xttotm(&t, all_satellites[i].getTimeAccessStart());
//                print_time(&t);
//                qDebug() << "1 end";
//                xttotm(&t, all_satellites[i].getTimeAccessEnd());
//                print_time(&t);

//                qDebug() << "2 st";
//                xttotm(&t, all_satellites[j].getTimeAccessStart());
//                print_time(&t);
//                qDebug() << "2 end";
//                xttotm(&t, all_satellites[j].getTimeAccessEnd());
//                print_time(&t);
//                qDebug() << "============";
                // ConflictWinSubset[collisions[i].getAssetNum()].lpConfW[collision_num] = &C[collisions[i].getAssetNum()].Win[collisions[i].number_of_collisions];
                collision_num++;
                conflicts_num++;

            }
        }
        all_satellites[i].number_of_windows++;

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
    //    qDebug() << t.tm_mday << day;
    //    qDebug() <<t.tm_mon << month;
    //    qDebug() <<t.tm_year << year;
    //    qDebug() <<t.tm_hour << hour;
    //    qDebug() <<t.tm_min << min;
    //    qDebug() <<t.tm_sec << sec;
    //    qDebug() << timeU;
}

