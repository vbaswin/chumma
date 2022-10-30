#include <stdio.h>

typedef struct processInfo {
    int at;
    int bt;
    int ft;
    int tat;
    int wt;
    int rem;
} processes;

typedef struct procInfo {
    int pno;
    int bt;
    int ft;
} infos;

void read(int processNo, processes p[]) {
    printf("Enter\tat\tbt\n");
    for (int i = 0; i < processNo; ++i) {
        printf("p[%d]\t", i);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rem = p[i].bt;
    }
}

void rr(int processNo, processes p[], infos info[], int *size) {
    int timeQuntm;
    printf("\nEnter time quantum: ");
    scanf("%d", &timeQuntm);

    int time = 0, Change = 1;
    while(Change) {
        Change = 0;
        for (int i = 0; i < processNo;) {
            if (p[i].rem == 0) {
                ++i;
                continue;
            }

            if (p[i].at > time) {
                ++time;
                continue;
            }
            if (p[i].rem > timeQuntm) {
                info[*size].pno = i;
                info[*size].bt = timeQuntm;
                p[i].rem -= timeQuntm;
                time += timeQuntm;
                info[*size].ft = time;
            }
            else {  
                info[*size].pno = i;
                info[*size].bt = p[i].rem;
                time += p[i].rem;
                p[i].rem = 0;
                p[i].ft = time;
                p[i].tat = p[i].ft - p[i].at;
                p[i].wt = p[i].tat - p[i].bt;
                info[*size].ft = time;
            }
            (*size)++;
            Change = 1;
            ++i;
        }
    }
}

void display(infos info[], int size, processes p[]) {
    printf("\n ");
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < info[i].bt; ++j)
            printf("--");
        printf(" ");
    }

    printf("\n|");
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < info[i].bt -1; ++j)
            printf(" ");
        printf("p%d", info[i].pno);
        for (int j = 0; j < info[i].bt -1; ++j)
            printf(" ");
        printf("|");
    }

    printf("\n ");
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < info[i].bt; ++j)
            printf("--");
        printf(" ");
    }

    printf("\n%d", p[0].at);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < info[i].bt; ++j) 
            printf("  ");
        if (info[i].ft > 9)
            printf("\b");
        printf("%d", info[i].ft);
    }
    printf("\n");
}

void avgTatWt(processes p[], int processNo) {
    int avgTat = 0, avgWt = 0;
    for (int i = 0; i < processNo; ++i)  {
        avgTat += p[i].tat;
        avgWt += p[i].wt;
    }
    printf("\nAvg Tat: %d\nAvg Wt: %d\n", avgTat/processNo, avgWt/processNo);
}

int main() {
    int processNo; 
    printf("Enter no. of process: ");
    scanf("%d", &processNo);

    processes p[processNo];
    infos info[50];
    read(processNo, p);

    int size = 0;
    rr(processNo, p, info, &size);
    display(info, size, p);

    avgTatWt(p, processNo);

    return 0;
}