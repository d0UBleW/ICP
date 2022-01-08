#include <stdio.h>
#include <stdlib.h>
#include "var.h"
#include "info.h"
#include "table.h"
#include "input.h"
#include "bubbleSort.h"
#include "file2struct.h"


void listDistRec() {
    int line = countLine("data/dist.txt");
    if (line > 0) {
        distRec *dist = (distRec *)calloc(line, sizeof(distRec));
        int cnt = 0;

        compressed_distToStruct(dist, &cnt);
        dist = (distRec *)realloc(dist, cnt * sizeof(distRec));

        printf("Sort Option\n");
        printf("***********\n");
        printf("0. Back\n");
        printf("1. Ascending\n");
        printf("2. Descending\n");
        printf("***********\n");

        int choice = option(1, 2)-1;

        if (choice == 0) {
            system("@cls||clear");
            return;
        }

        int (*cmp[])(ll, ll) = {asc, desc};

        bubSort(dist, cnt, cmp[choice]);

        printf("\n");

        distTable(5, cnt, dist);

        free(dist);
    }
    else {
        printf("Currently there is no record to be listed.\n");
    }
    enterContinue();
}
