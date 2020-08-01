#ifndef SEARCH_CONFLICT_ALGORITHM_H
#define SEARCH_CONFLICT_ALGORITHM_H
#include <time.h>
#include <string>
#include <vector>
#include <structure.h>
#include <QString>
//typedef struct tagWindow {
//    int t_AOS; // time of Asquisition of signal
//    int t_LOS; // time of Lost of signal
//    int G; // Ground station ID
//    bool is_available; //if we want to include it in schedule
//    bool is_final;//if it is really part of the final schedule
//} Window;

//typedef struct tagC // comm window
//{
//    int num_wins; // number of comm windows for request
//    Window *Win;
//   // Window Win[NUM_WINS]; // window parameters
//} Contact;

//typedef struct tagConflict {
//    Window **lpConfW; // conflict windows
//   // Window *lpConfW[NUM_REQS]; // conflict windows
//} Conflict;


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
//    int getNumOfWindow() const;
//    void setNumOfWindow(int value);
};

void search_conflicts(vector<Schedule> all_satellites);

#endif // SEARCH_CONFLICT_ALGORITHM_H
