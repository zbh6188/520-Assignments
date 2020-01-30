#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <float.h>

/* private functions *********************************************************/
static int count = 0;
static int countForDestroy = 0;

// static DynamicArray * forDestroy [100];

// int DynamicArray_num_arrays() {
//     return count;
// }

// int DynamicArray_is_valid(const DynamicArray * da) {
//     if (da->buffer != NULL) {
//         return 1;
//     } else {
//         return 0;
//     }
// }

// int DynamicArray_destroy_all() {
//     for (int i = 0; i < countForDestroy; i++) {
//         if (DynamicArray_is_valid(forDestroy[i]) == 1) {
//             DynamicArray_destroy(forDestroy[i]);
//         }
//     }
//     count = 0;
//     return countForDestroy;
// }



/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;
    count++;
    countForDestroy++;
    return da;
    // forDestroy[countForDestroy] = da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    count--;
    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_last(da);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_first(da);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_copy(da);
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(result, i)));
    }
    return result;
}

DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {

    assert(da->buffer != NULL);
    assert(b >= a);

    DynamicArray * result = DynamicArray_new();

    for (int i=a; i<b; i++) {
        DynamicArray_push(result,DynamicArray_get(da, i));
    }
    return result;
}

double DynamicArray_min (const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    double minimum = DBL_MAX;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        if (DynamicArray_get(da,i) < minimum) {
            minimum = DynamicArray_get(da,i);
        }
    }
    return minimum;
}

double DynamicArray_max (const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    double maximum = DBL_MIN;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        if (DynamicArray_get(da,i) > maximum) {
            maximum = DynamicArray_get(da,i);
        }
    }
    return maximum;
}

double DynamicArray_mean (const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    double sum = 0.0;
    double mean = 0.0;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        sum += DynamicArray_get(da,i);
    }
    mean = sum / DynamicArray_size(da);
    return mean;
}

double DynamicArray_median ( const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    DynamicArray * sort = DynamicArray_copy(da);
    double temp = 0.0;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        for (int j = 0; j < DynamicArray_size(da)-1; j++) {
            if (DynamicArray_get(sort, j) > DynamicArray_get(sort, j+1)) {
                temp = DynamicArray_get(sort, j);
                DynamicArray_set(sort, j, DynamicArray_get(sort, j+1));
                DynamicArray_set(sort, j+1, temp);
            }
        }
    }
    double median = 0.0;
    if (DynamicArray_size(da)%2 == 0) {
        median = (DynamicArray_get(sort, (DynamicArray_size(sort)-1)/2) + DynamicArray_get(sort, (DynamicArray_size(sort)/2))) / 2.0;
    } else {
        median = DynamicArray_get(sort, (DynamicArray_size(sort)/2));
    }
    return median;
    DynamicArray_destroy(sort);
}

double DynamicArray_sum (const DynamicArray * da ) {
    double sum = 0.0;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        sum += DynamicArray_get(da,i);
    }
    return sum;
}

double DynamicArray_last ( const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    double last;
    last = DynamicArray_get(da, (DynamicArray_size(da) - 1));
    return last;
}

double DynamicArray_first ( const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    double first;
    first = DynamicArray_get(da, 0);
    return first;
}

DynamicArray * DynamicArray_copy ( const DynamicArray * da ) {
    DynamicArray * copy = DynamicArray_new();
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(copy, i, (DynamicArray_get(da, i)));
    }
    return copy;
}

DynamicArray * DynamicArray_range ( double a, double b, double step) {
    DynamicArray * linspace = DynamicArray_new();
    double value = a;
    if (b >= a && step > 0) {
        for (int i = 0; i < abs((b-a)/step)+1; i++) {
            if (value <= b) {
                value = a + i * step;
                DynamicArray_set(linspace, i, value); 
            }
        }
    } else if (b <= a && step < 0) {
        for (int i = 0; i < abs((b-a)/step)+1; i++) {
            if (value >= b) {
                value = a + i * step;
                DynamicArray_set(linspace, i, value);
            }
        }
    }       
    
    return linspace;
}

DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b ) {
    assert(DynamicArray_size(a) > 0);
    assert(DynamicArray_size(b) > 0);
    DynamicArray * c = DynamicArray_copy(a);
    for (int i = 0; i < DynamicArray_size(b); i++) {
        DynamicArray_push(c, DynamicArray_get(b,i));
    }
    return c;
}

DynamicArray * DynamicArray_take ( const DynamicArray * a, int n ) {
    assert(DynamicArray_size(a) > 0);
    DynamicArray * temp = DynamicArray_copy(a);
    DynamicArray * sub = DynamicArray_new();
    if (n > 0) {
        if (n < DynamicArray_size(a)) {
            sub = DynamicArray_subarray(temp, 0, n);
        } else {
            sub = DynamicArray_copy(a);
            for (int i = 0; i < n-DynamicArray_size(a); i++) {
                DynamicArray_push(sub, 0.0);
            }
        }
    } else if (n < 0 && abs(n) < DynamicArray_size(a)) {
        sub = DynamicArray_subarray(temp, DynamicArray_size(a)+n, DynamicArray_size(a));
    } else if (n < 0 && abs(n) > DynamicArray_size(a)) {
        sub = DynamicArray_copy(a);
        for (int i = 0; i < abs(n)-DynamicArray_size(a); i++) {
                DynamicArray_push_front(sub, 0.0);
            }
    }
    return sub;
    DynamicArray_destroy(temp);
}




