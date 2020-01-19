#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stdlib.h>

typedef struct {
   double x, y, z;
} Point;

int running_total(int x);
void reverse_in_place(int x[], int len);
int * reverse (int x[], int len);
int num_instances (int x[], int len, int val);
Point * map (Point * a, int len, Point (* f_ptr) (Point));
#endif