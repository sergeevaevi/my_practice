#ifndef SEARCH_CONFLICT_ALGORITHM_H
#define SEARCH_CONFLICT_ALGORITHM_H
#include <time.h>
#include <string>
#include <vector>
#include <structure.h>
#include <QString>


using namespace std;
class Schedule{
private:
    xtime_t access_start;
    xtime_t access_end;
    int duration;
    QString asset_name;
    int asset_num; // порядковый от 0
public:
    xtime_t getTimeAccessStart();
    xtime_t getTimeAccessEnd();
    int getDuration();
    QString getAssetName();
    int getAssetNum();
    void setTimeAccessStart(QString day, QString month, QString year, QString hour, QString min, QString sec);
    void setTimeAccessStart(xtime_t tm);
    void setTimeAccessEnd(QString day, QString month, QString year, QString hour, QString min, QString sec);
    void setTimeAccessEnd(xtime_t tm);
    void setDuration(int dur);
    void setAssetName(string nm);
    void setAssetName(QString nm);
    void setAssetNum(int nm);
    int number_of_windows = 0;
};


pair<int, int> getValuesByConflicts(vector<Schedule>& all_satellites);

void setBySearchingConflicts(vector<Schedule> all_satellites, Conflict * ConflictWinSubset, Contact * C);

#endif // SEARCH_CONFLICT_ALGORITHM_H
