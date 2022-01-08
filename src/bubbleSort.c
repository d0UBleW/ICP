#include <stdlib.h>
#include <string.h>
#include "var.h"

void swapDist(distRec *a, distRec *b) {
    distRec *temp = malloc(sizeof(distRec));

    strcpy(temp->code, a->code);
    temp->qty = a->qty;

    strcpy(a->code, b->code);
    a->qty = b->qty;

    strcpy(b->code, temp->code);
    b->qty = temp->qty;

    free(temp);
}

int asc(ll l, ll r) {
    // if left > right then swap equivalent to if left - right > 0 then swap
    // simply subtracting l from r is subjected to overflow
    // source: https://stackoverflow.com/a/53821630
    return (l > r) - (l < r);
}

int desc(ll l, ll r) {
    // if right > left then swap equivalent to if right - left > 0 then swap
    // simply subtracting l from r is subjected to overflow
    // source: https://stackoverflow.com/a/53821630
    return (r > l) - (r < l);
}

void bubSort(distRec *dist, int line, int (*compare)(ll, ll)) {
    int swapped = 0;
    for (int i = 0; i < line-1; i++) {
        for (int j = 0; j < line-i-1; j++) {
            if ((*compare)((dist+j)->qty, (dist+j+1)->qty) > 0) {
                swapDist((dist+j), (dist+j+1));
                swapped = 1;
            }
        }
        if (swapped == 0) break;
        swapped = 0;
    }
}
