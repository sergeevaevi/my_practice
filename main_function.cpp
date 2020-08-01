#include <main_function.h>
#include <mainwindow.cpp>

/*******************************************************
                Get Ground Station Priority
*******************************************************/

static int GetGndStationPriority(int Gs) {
    int res = 0;
    switch (Gs) {
    case GS_1:
        res = HI_PRIO;
        break;
    case GS_2:
        res = MEDUIM_PRIO;
        break;
    case GS_3:
        res = LOW_PRIO;
        break;
    default:
        res = LOW_PRIO;
    }
    return res;
}

/*******************************************************
                Get Satellite Priority
*******************************************************/

static int GetSatellitePriority(int Sat) {
    int res = 0;
    switch (Sat) {
    case SAT_1:
        res = LOW_PRIO;
        break;
    case SAT_2:
        res = LOW_PRIO;
        break;
    case SAT_3:
        res = LOW_PRIO;
        break;
    default:
        res = LOW_PRIO;
    }
    return res;
}

/*******************************************************
                Get User Priority
*******************************************************/

static int GetUserPriority(int User) {
    int res = 0;
    switch (User) {
    case USER_1:
        res = HI_PRIO;
        break;
    case USER_2:
        res = MEDUIM_PRIO;
        break;
    case USER_3:
        res = LOW_PRIO;
        break;
    default:
        res = LOW_PRIO;
    }
    return res;
}


/*******************************************************
                Calculate Gamma1
*******************************************************/

static int calc_gamma1(Contact *C, Request *R) {

    int summ = 0;
    int val = 0;
    int res = 0;
    int i, j;
    int total_priority_value;

    int wR = 1; // weights
    int wG = 1;
    int wS = 1;
    int wU = 1;

    for (i = 0; i < NUM_REQS; i++) {
        for (j = 0; j < C[i].num_wins; j++) {
            total_priority_value =
                    wR * R[i].Pr + wG * GetGndStationPriority(C[i].Win[j].G) + wS * GetSatellitePriority(R[i].S) +
                    wU * GetUserPriority(R[i].U);
            val = total_priority_value * C[i].Win[j].is_final;
            summ += val;
        }
    }
    int gamma1 = summ; // weighted sum of assigned priority values
    return gamma1;
}

/*******************************************************
                Calculate Gamma2
*******************************************************/
static int calc_gamma2(Contact *C, Request *R) {

    int summ = 0;
    int val = 0;
    int res = 0;
    int i, j;

    int *Rb = (int*)malloc(NUM_REQS * sizeof(int));
    //[NUM_REQS];
    int * kR = (int*)malloc(NUM_REQS * sizeof(int));
    //[NUM_REQS];

    for (i = 0; i < NUM_REQS; i++) {
        for (j = 0; j < C[i].num_wins; j++)
            summ += C[i].Win[j].is_final;
        Rb[i] = summ; // actual number of assigned contact windows Cij for request Ri
        summ = 0;
    }


    int Rb_max = 0; // maximum number of available contact windows of single request
    for (i = 0; i < NUM_REQS; i++)
        if(Rb_max < C[i].num_wins) Rb_max = C[i].num_wins; // find max

    for (i = 0; i < NUM_REQS; i++)
        kR[i] = Rb_max - Rb[i];

    float lyamda = 3; // parameter, empirically
    for (i = 0; i < NUM_REQS; i++) {
        val = (int) pow(lyamda, kR[i]);
        summ += val;
    }

    int gamma2 = summ;
    free(Rb);
    free(kR);
    return gamma2;
}

void setWindowsByRequestByExample(int *WINDOWS_BY_REQUEST){
        WINDOWS_BY_REQUEST[0]=13;
        WINDOWS_BY_REQUEST[1]=14;
        WINDOWS_BY_REQUEST[2]=12;
        WINDOWS_BY_REQUEST[3]=12;
        WINDOWS_BY_REQUEST[4]=14;
        WINDOWS_BY_REQUEST[5]=13;
        WINDOWS_BY_REQUEST[6]=12;
        WINDOWS_BY_REQUEST[7]=12;
}

void setConflictsByExample(Conflict * ConflictWinSubset, Contact * C){
    //********** conflicts of windows, taken from STK for example  ***************
    // yellow
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

}

void copy(Contact* C_final, Contact* C){
    for (int i = 0; i < NUM_REQS; i++) {
        for (int j = 0; j < C[i].num_wins; j++) {
            C_final[i].Win[j].is_final = C[i].Win[j].is_final;
            C_final[i].Win[j].is_available = C[i].Win[j].is_available;
            C_final[i].Win[j].G = C[i].Win[j].G;
            C_final[i].Win[j].t_AOS = C[i].Win[j].t_AOS;
            C_final[i].Win[j].t_LOS = C[i].Win[j].t_LOS;
        }
    }
}

/*******************************************************
                Main program body
*******************************************************/


void printContact(Contact * C){
    printf("Contact is\n");
    for (int i = 0; i < NUM_REQS; i++) {
        for (int j = 0; j < C[i].num_wins; j++) {
            printf("C{%u,%u].%u;%u;%u;%u;%u\n", i + 1, j + 1, C[i].Win[j].is_final, C[i].Win[j].G, C[i].Win[j].t_AOS, C[i].Win[j].t_LOS, C[i].Win[j].is_available);
        }
        printf("\n");
    }
    printf("\n");
}

void printRequest(Request * R){
    for (int j = 0; j < NUM_REQS; j++) {
        printf("R[%u].%u;%u;%u;%u;%u%u;%u\n", j + 1, R[j].S, R[j].U, R[j].Pr, R[j].Rd, R[j].te, R[j].ts, R[j].dur);
    }
}

void printConflict(Conflict* C){
    printf("Conflict is\n");
    for (int i = 0; i < NUM_OF_CONFLICTS; i++) {
        for (int j = 0; j < NUM_REQS; j++) {
            if(C[i].lpConfW[j]){
                printf("C{%u,%u].%u;%u;%u;%u;%u\n",i + 1, j + 1, C[i].lpConfW[j]->G, C[i].lpConfW[j]->t_AOS, C[i].lpConfW[j]->t_LOS, C[i].lpConfW[j]->is_final, C[i].lpConfW[j]->is_available);
            } else{
                printf("-ZERO-\n");
            }
        }
        printf("\n");
    }
    printf("\n");
}


void addLabels(Ui::MainWindow * ui, Contact * C, Contact * C_final, int * qqq, QVector<QLabel*>& labels){
    //ui->front_img->hide();
//    QVector<QLabel*> labels;
    int count = 0;
    for(int j = 0; j < NUM_WINS;j++){
        for(int i = 0; i < NUM_REQS;i++){

            QLabel * label = new QLabel(ui->gridLayoutWidget);
            label->setStyleSheet("color: AliceBlue; padding: 25px;");

            if(j < C[i].num_wins){
                label->setText("C["+QString::number(i + 1)+","+QString::number(j + 1)+"]="+QString::number(C_final[i].Win[j].is_final));
            }
            else{
                label->setText("-----");
            }
            label->setObjectName("label_"+QString::number(count));
            ui->gridLayout->addWidget(label, j, i, 1, 1);
            count++;
            labels.push_back(label);
        }
    }
    for (int k = 0; k < NUM_REQS; k++) {
        QLabel * label = new QLabel(ui->gridLayoutWidget);
        label->setStyleSheet("color: AliceBlue;padding: 25px;");
        label->setText("Summ="+QString::number(qqq[k]));
        label->setObjectName("label_sum"+QString::number(count));
        ui->gridLayout->addWidget(label, NUM_WINS+1, k, 1, 1);
        count++;
        labels.push_back(label);
    }
}


QVector<QLabel*> main_func(Ui::MainWindow * ui, std::vector<Schedule> &data, bool is_data_loaded) {
    int *WINDOWS_BY_REQUEST;

    WINDOWS_BY_REQUEST = (int*)malloc(NUM_REQS * sizeof(int));

    ///this shit must be rewritten later
    if(is_data_loaded){
        for(int i = 0; i < NUM_REQS; i++){
            WINDOWS_BY_REQUEST[i] = 0;
        }
        qDebug() << "Yeah, you are here!" << NUM_REQS << NUM_WINS << NUM_OF_CONFLICTS;
        for(auto c: data){
            WINDOWS_BY_REQUEST[c.getAssetNum()]++;
        }

        for(int i = 0; i < NUM_REQS; i++){
            qDebug() << WINDOWS_BY_REQUEST[i];
        }
    }else{
        setWindowsByRequestByExample(WINDOWS_BY_REQUEST);
    }
    ///
    //------------------
    int summ = 0;
    int i, j, k;
    //------------------

    ///mem alloc and how stupid I am?
    ///
    Contact * C = (Contact*)malloc(NUM_REQS * sizeof(Contact));
    //C[NUM_REQS]; Cij = F( Ri, t_AOS, t_LOS, G ); // j contact windows of request Ri
    for (i = 0; i < NUM_REQS; i++) {
        C[i].Win =  (Window*)malloc(NUM_WINS * sizeof(Window));
        //Window Win[NUM_WINS]; // window parameters
    }

    Request * R = (Request*)malloc(NUM_REQS * sizeof(Request));
    //[NUM_REQS]; //	Ri = f( S,U,ts,te,dur, Rd); - communication request number i

    Contact * C_final = (Contact*)malloc(NUM_REQS * sizeof(Contact));
    //[NUM_REQS];
    for (i = 0; i < NUM_REQS; i++) {
        C_final[i].Win =  (Window*)malloc(NUM_WINS * sizeof(Window));
        //Window Win[NUM_WINS]; // window parameters
    }

    Conflict * ConflictWinSubset = (Conflict*)malloc(NUM_OF_CONFLICTS * sizeof(Conflict));
    //[NUM_OF_CONFLICTS];
    for (i = 0; i < NUM_OF_CONFLICTS; i++) {
        ConflictWinSubset[i].lpConfW = (Window**)malloc(NUM_REQS * sizeof(Window*));
        //Window *lpConfW[NUM_REQS]; // conflict windows
    }
    //********** request initialization ***************

    for (i = 0; i < NUM_OF_CONFLICTS; i++) {
        for (j = 0; j < NUM_REQS; j++){
            ConflictWinSubset[i].lpConfW[j] = nullptr;
        }
    }

    for (i = 0; i < NUM_REQS; i++) {
        C[i].num_wins = WINDOWS_BY_REQUEST[i];
    }

    for (i = 0; i < NUM_REQS; i++) {
        R[i].Pr = LOW_PRIO;
        R[i].S = SAT_1;
        R[i].U = USER_3;
        //
        R[i].Rd = 0;
        R[i].te = 0;
        R[i].ts = 0;
        R[i].dur = 0;
        //
        for (j = 0; j < C[i].num_wins; j++){
            C[i].Win[j].G = GS_3;
            //
            C[i].Win[j].t_AOS = 0;
            C[i].Win[j].t_LOS = 0;
            //
        }
    }

    //    //********** set all as available  ***************

    for (i = 0; i < NUM_REQS; i++) {
        for (j = 0; j < C[i].num_wins; j++) {
            C[i].Win[j].is_final = true;
            C[i].Win[j].is_available = true;
        }
    }

    bool ** flag = (bool**)malloc(NUM_REQS * sizeof(bool*));
    for (i = 0; i < NUM_REQS; i++) {
        flag[i] =  (bool*)malloc(NUM_REQS * sizeof(bool));
        for (j = 0; j < NUM_REQS; j++){
            if(i == j){
                flag[i][j] = true;
            }else{
                flag[i][j] = false;
            }
        }
    }

    if(is_data_loaded){
        setBySearchingConflicts(data, ConflictWinSubset, C);
    }else{
        setConflictsByExample(ConflictWinSubset, C);
    }


    // ************* Optimization: 'is_final' flag variation ***************************

    int gamma_max = -500000; // initial value
    for (int next_var = 0; next_var < NUM_REQS; next_var++) {
        for (int next_subset = 0; next_subset < NUM_OF_CONFLICTS; next_subset++) {

            for (k = 0; k < NUM_OF_CONFLICTS; k++) {
                for (j = 0; j < NUM_REQS; j++) {
                    if(ConflictWinSubset[k].lpConfW[j]) {
                        ConflictWinSubset[k].lpConfW[j]->is_final = flag[j][next_var];
                    } else {
                        break;
                    }
                }
            }


            for (i = 0; i < NUM_REQS; i++) {
                for (j = 0; j < NUM_REQS; j++) {
                    if(ConflictWinSubset[next_subset].lpConfW[j]) {
                        ConflictWinSubset[next_subset].lpConfW[j]->is_final = flag[j][i];
                    } else
                        break;
                }

                int gamma1 = calc_gamma1(C, R);
                int gamma2 = calc_gamma2(C, R);
                int gamma = gamma1 - gamma2;
                if(gamma > gamma_max) {
                    qDebug() << "HERE";
                    gamma_max = gamma;
                    // memmove(C_final, C, sizeof(Contact) * NUM_REQS);
                    copy(C_final, C);
                }

            }
        }
    }

    // ************* Output  ***************************

    int * qqq = (int*)malloc(NUM_REQS * sizeof(int));
    // [NUM_REQS];

    for (i = 0; i < NUM_REQS; i++) {
        for (j = 0; j < C[i].num_wins; j++) {
            summ += C_final[i].Win[j].is_final;
        }
        qqq[i] = summ; // actual number of assigned contact windows Cij for request Ri
        summ = 0;
    }

    ui->front_img->hide();
    QVector<QLabel*> labels;
    addLabels(ui, C, C_final, qqq, labels);

    // free all memory
    for (i = 0; i < NUM_REQS; i++) {
        free(C[i].Win);
    }
    free(C);
    for (i = 0; i < NUM_REQS; i++) {
        free(C_final[i].Win);
    }
    free(C_final);

    free(WINDOWS_BY_REQUEST);

    free(R);

    for (i = 0; i < NUM_OF_CONFLICTS; i++) {
        free(ConflictWinSubset[i].lpConfW);
    }
    free(ConflictWinSubset);

    free(qqq);

    return labels;
}

void test(){
    Contact * C = (Contact*)malloc(NUM_REQS * sizeof(Contact));
    for (int i = 0; i < NUM_REQS; i++) {
        C[i].Win =  (Window*)malloc(NUM_WINS * sizeof(Window));
    }

    for (int i = 0; i < NUM_WINS; i++) {
        free(C[i].Win);
    }
    free(C);
}
