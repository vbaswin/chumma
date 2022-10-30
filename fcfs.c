#include <stdio.h>

typedef struct processInfo {
    int at;
    int bt;
    int ft;
    int tat;
    int wt;
} processes;

void read(int processNo, processes process[]) {
    printf("Enter\tat\tbt\n");
    for (int i = 0; i < processNo; ++i) {
        printf("p[%d]\t", i);
        scanf("%d %d", &process[i].at, &process[i].bt);
    }
}

void fcfs(int processNo, processes p[]) {
    int time = 0;
    for (int i = 0; i < processNo;) {
        if (p[i].at > time) {
            ++time;
            continue;
        }
        time += p[i].bt;
        p[i].ft = time;
        p[i].tat = p[i].ft - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        ++i;
    }
}

void display(int processNo, processes p[]) {
    printf("\n ");
    for (int i = 0; i < processNo; ++i) {
        for (int j = 0; j < p[i].bt; ++j)
            printf("--");
        printf(" ");
    }

    printf("\n|");
    for (int i = 0; i < processNo; ++i) {
        for (int j = 0; j < p[i].bt -1; ++j)
            printf(" ");
        printf("p%d", i);
        for (int j = 0; j < p[i].bt -1; ++j)
            printf(" ");
        printf("|");
    }

    printf("\n ");
    for (int i = 0; i < processNo; ++i) {
        for (int j = 0; j < p[i].bt; ++j)
            printf("--");
        printf(" ");
    }

    printf("\n%d", p[0].at);
    for (int i = 0; i < processNo; ++i) {
        for (int j = 0; j < p[i].bt; ++j) 
            printf("  ");
        if (p[i].ft > 9)
            printf("\b");
        printf("%d", p[i].ft);
    }
    printf("\n");
}

int main() {
    freopen("fcfs.in", "rt", stdin);
    int processNo; 
    printf("Enter no. of process: ");
    scanf("%d", &processNo);

    processes p[processNo];
    read(processNo, p);

    fcfs(processNo, p);
    display(processNo, p);

    return 0;
}