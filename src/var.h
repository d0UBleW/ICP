#ifndef VAR_H
#define VAR_H

typedef long long ll;

typedef struct {
    char name[64];
    char code[64];
    char country[64];
    int dosage;
    float population;
    ll qty;
} record;

typedef struct {
    char code[64];
    ll qty;
    char dest[64];
} distRec;

#endif
