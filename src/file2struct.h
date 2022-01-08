#ifndef FILE2STRUCT_H_INCLUDED
#define FILE2STRUCT_H_INCLUDED

void vacToStruct(record *inventory);

void structToVac (record *inventory);

void compressed_distToStruct(distRec *dist, int *cnt);

void distToStruct(distRec *dist);

void structToDist (distRec *dist, int line);

#endif // FILE2STRUCT_H_INCLUDED
