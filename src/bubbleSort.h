#ifndef BUBBLESORT_H_INCLUDED
#define BUBBLESORT_H_INCLUDED

void swapDist(distRec *a, distRec *b);

int asc(ll l, ll r);

int desc(ll l, ll r);

void bubSort(distRec *dist, int line, int (*compare)(ll, ll));

#endif // BUBBLESORT_H_INCLUDED
