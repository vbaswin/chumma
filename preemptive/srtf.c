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

void srtf(int processNo, processes p[], infos info[], int *size) {

    int time = 0, allZeros = 0;
    while(!allZeros) {
        allZeros = 1;

        for (int i = 0 ; i < processNo; ++i) {
            if (p[i].rem != 0) {
                allZeros = 0;
                break;
            }
        }

        if (allZeros)
            break;

        int present = 0, i;
        for (i = 0; i < processNo; ++i) {
            if (p[i].at <= time && p[i].rem != 0) {
                present = 1;
                break;
            }
        }
        if (!present) {
            ++time;
            continue;
        }

        int smallest = 10000000, idx = -1;
        for (int i = 0; i <  processNo; ++i) {
            if (p[i].at <= time && p[i].rem != 0 && p[i].rem < smallest) {
                smallest = p[i].rem;
                idx = i;
            }
        }

        --p[idx].rem;
        if (*size == 0) {
            info[*size].pno = idx;
            info[*size].bt += 1;
            info[*size].ft += 1;
        }
        else if (info[(*size) -1].pno == idx) {
            --(*size);
            info[*size].bt += 1;
            info[*size].ft += 1;
        }
        else {
            info[*size].pno = idx;
            info[*size].bt += 1;
            info[*size].ft = ((info[(*size)-1].ft)+1) + (time - info[(*size)-1].ft);
        }
        ++(*size);
        ++time;
    }

    for (int i = 0; i < processNo; ++i) {
        for (int j = 0;j < *size; ++j) {
            if (info[j].pno == i && p[i].bt == info[j].bt) {
                p[i].ft = info[j].ft;
                p[i].tat = p[i].ft - p[i].at;
                p[i].wt = p[i].tat - p[i].bt;
                break;
            }
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
    freopen("srtf.in","rt", stdin);
    int processNo; 
    printf("Enter no. of process: ");
    scanf("%d", &processNo);

    processes p[processNo];
    infos info[100];
    for (int i = 0; i < 100; ++i) {
        info[i].pno = -1;
        info[i].bt = 0;
        info[i].ft = 0;
    }
    read(processNo, p);

    int size = 0;
    srtf(processNo, p, info, &size);
    display(info, size, p);

    avgTatWt(p, processNo);

    return 0;
}