#ifndef SECOND_WINDOW_H
#define SECOND_WINDOW_H


enum {
    GS_1 = 0,
    GS_2,
    GS_3
};

enum {
    SAT_1 = 0,
    SAT_2,
    SAT_3
};

enum {
    USER_1 = 0,
    USER_2,
    USER_3
};

enum {
    LOW_PRIO = 1,
    MEDUIM_PRIO,
    HI_PRIO
};

typedef struct tagR // comm request
{
    int Pr;// priority
    int ts; //t of start,
    int te; //t of end
    int dur;// min duration of contact
    int Rd;// =-1;// (3.2), degree of redundancy
    int U; // User
    int S;// satellite
} Request;

typedef struct tagWindow {
    long t_AOS; // time of Asquisition of signal
    long t_LOS; // time of Lost of signal
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


#endif // SECOND_WINDOW_H
