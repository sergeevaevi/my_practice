#ifndef SEARCH_CONFLICT_ALGORITHM_H
#define SEARCH_CONFLICT_ALGORITHM_H
#include <time.h>
#include <string>
#include <vector>

typedef struct tagWindow {
    int t_AOS; // time of Asquisition of signal
    int t_LOS; // time of Lost of signal
    int G; // Ground station ID
    bool is_available; //if we want to include it in schedule
    bool is_final;//if it is really part of the final schedule
} Window;

typedef struct tagC // comm window
{
    int num_wins; // number of comm windows for request
    Window *Win;
   // Window Win[NUM_WINS]; // window parameters
} Contact;

typedef struct tagConflict {
    Window **lpConfW; // conflict windows
   // Window *lpConfW[NUM_REQS]; // conflict windows
} Conflict;


using namespace std;
class Сollision{
private:
    xtime_t access_start;
    xtime_t access_end;
    int duration;
    string asset_name;
    int asset_num; // порядковый от 0
public:
    xtime_t getTimeAccessStart();
    xtime_t getTimeAccessEnd();
    int getDuration();
    string getAssetName();
    int getAssetNum();
    void setTimeAccessStart(xtime_t tm);
    void setTimeAccessEnd(xtime_t tm);
    void setDuration(int dur);
    void setAssetName(string nm);
    void setAssetNum(int nm);
    int number_of_collisions = 0;
};

void search_conflicts();

#endif // SEARCH_CONFLICT_ALGORITHM_H
