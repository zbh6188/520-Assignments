#include <stdio.h>
#include <math.h>

#include "solutions.h"

int running_total (int x) {
    static double list[100];
    int top = 0;
    list[top] = x;
    top++;
    list[top] += x;
    int result = list[top];
    return result;
}

void reverse_in_place (int x[], int len) {
    int temp[len];
    for (int j = 0; j < len; j++) {
        temp[j] = x[j];
    }
    for (int i = 0; i < len; i++) {
        x[i] = temp[(len - 1) - i];
    }
}

int * reverse (int x[], int len) {
    int * y;
    y = (int *) calloc(len, sizeof(int));
    for (int i = 0; i < len; i++) {
        y[i] = x[(len -1) - i];
    }

    return y;

}

int num_instances (int x[], int len, int val) {
    int count  = 0;
    for (int i = 0; i < len; i++) {
        if (x[i] == val) {
            count++;
        }
    }
    return count;
}

Point * map (Point * a, int len, Point (* f_ptr) (Point)) {
    Point * b;
    b = (Point *) calloc(len, sizeof(Point));
    for (int i = 0; i < len; i++) {
        b[i] = f_ptr(a[i]);
    }
    
    return b;
}