#include <search_conflict_algorithm.h>

bool checkForCollisions(Сollision i, Сollision j){
    long max_end_time_i = i.getTimeAccessEnd() + i.getDuration();
    long max_end_time_j = j.getTimeAccessEnd() + j.getDuration();
    long min_end_time_j = j.getTimeAccessStart() + j.getDuration();
    long min_end_time_i = i.getTimeAccessStart() + i.getDuration();
    bool different_time_l = (i.getTimeAccessStart() < j.getTimeAccessStart() && i.getTimeAccessEnd() < j.getTimeAccessEnd());
    bool different_time_m = (i.getTimeAccessStart() > min_end_time_j && i.getTimeAccessEnd() > max_end_time_j );
    bool not_collided_l = (min_end_time_i < j.getTimeAccessStart()) &&  (max_end_time_i < j.getTimeAccessEnd()) ;
    bool not_collided_m = (min_end_time_i < min_end_time_j) &&  (max_end_time_i < max_end_time_j) ;
    if((different_time_l && not_collided_l) || (different_time_m && not_collided_m)){
        return true;
    }
    return false;
}

void search_conflicts(Conflict * ConflictWinSubset, Contact * C, int *WINDOWS_BY_REQUEST)
{
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
    Сollision d;
    vector<Сollision> collisions;// = parseFile();
    for(auto c: collisions){
        WINDOWS_BY_REQUEST[c.getAssetNum()]++;
    }
    int conflicts_num = 0;
    for(int i = 0; i < collisions.size(); i++){
        int collision_num = 0;
        for(int j = 0; j < collisions.size(); j++){
            if(i == j){
                continue;
            }
            if(checkForCollisions(collisions[i], collisions[j])){
                ConflictWinSubset[conflicts_num].lpConfW[collision_num] = &C[collisions[i].getAssetNum()].Win[collisions[i].number_of_collisions];
                collision_num++;
                collisions[i].number_of_collisions++;
            }
        }
        conflicts_num++;
    }
}

xtime_t Сollision::getTimeAccessStart()
{
    return access_start;
}

xtime_t Сollision::getTimeAccessEnd()
{
    return access_end;
}

int Сollision::getDuration()
{
    return duration;
}

string Сollision::getAssetName()
{
    return asset_name;
}

void Сollision::setTimeAccessStart(xtime_t tm)
{
    access_start = tm;
}

void Сollision::setTimeAccessEnd(xtime_t tm)
{
    access_end = tm;
}

void Сollision::setDuration(int dur)
{
    duration = dur;
}

void Сollision::setAssetName(string nm)
{
    asset_name = nm;
}

void Сollision::setAssetNum(int nm)
{
    asset_num = nm;
}

int Сollision::getAssetNum()
{
    return asset_num;
}
