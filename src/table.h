#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

#include "var.h"

void vacSpacing(int *width, record *rec, int line);

void vacAttr(char **attr);

void vacTable(int col, int row, record *content);

void distSpacing(int *width, distRec *dist, int line);

void distAttr(char **attr);

void distTable(int col, int row, distRec *content);

#endif // TABLE_H_INCLUDED
