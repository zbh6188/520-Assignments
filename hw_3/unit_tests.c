#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "gtest/gtest.h"

#define X 1.2345

namespace {

    TEST(DynamicArray, CreateAndDestroy) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, DeathTests) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
        DynamicArray_destroy(a);
        ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
    }    

    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);              
    }

    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);              
    }  

    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        printf("Push test Intermediate Result: %s\n", 
               DynamicArray_to_string(da));
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    } 

    TEST(DynamicArray,ToString) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
        free(str);
    }

    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ASSERT_NEAR(
                DynamicArray_get(y,i),sin(0.1*i), 0.0001
            );
        }
        DynamicArray_destroy(t);    
        DynamicArray_destroy(y);                    
    }

    TEST(DynamicArray, Math) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        DynamicArray * db = DynamicArray_new();
        DynamicArray_push(db, 10);
        DynamicArray_push(db, 5);
        DynamicArray_push(db, 6);
        DynamicArray_push(db, 9);
        DynamicArray_push(db, 8);
        DynamicArray_push(db, 3);
        DynamicArray_push(db, 4);
        DynamicArray_push(db, 2);
        DynamicArray_push(db, 1);
        DynamicArray_push(db, 7);
        ASSERT_EQ(DynamicArray_min(da),1);
        ASSERT_EQ(DynamicArray_max(da),5);
        ASSERT_EQ(DynamicArray_mean(da),3);
        ASSERT_EQ(DynamicArray_median(db),5.5);
        ASSERT_EQ(DynamicArray_sum(da),15);
        DynamicArray_destroy(da);
        DynamicArray_destroy(db);          
    }

    TEST(DynamicArray, Range) {
        DynamicArray * a = DynamicArray_range (1, 0, -0.1);
        char * str = DynamicArray_to_string(a);
        printf("ToString Example: %s\n", str);
        DynamicArray_destroy(a);
        free(str);
    }

    TEST(DynamicArray, Concat) {
        DynamicArray * a = DynamicArray_range (0, 1, 0.1);
        DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
        DynamicArray * c = DynamicArray_concat(a, b);
        char * str = DynamicArray_to_string(c);
        printf("ToString Example: %s\n", str);
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
        free(str);
    }

    TEST(DynamicArray, Take) {
        DynamicArray * a = DynamicArray_range (1, 5, 1);
        DynamicArray * b = DynamicArray_take(a, 2);
        DynamicArray * c = DynamicArray_take(a, 0);
        DynamicArray * d = DynamicArray_take(a, -7);
        char * str1 = DynamicArray_to_string(b);
        char * str2 = DynamicArray_to_string(c);
        char * str3 = DynamicArray_to_string(d);
        printf("str1: %s\nstr2: %s\nstr3: %s\n", str1, str2, str3);
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
        DynamicArray_destroy(d);
        free(str1);
        free(str2);
        free(str3);
    }

//     TEST(DynamicArray, Count) {
//         DynamicArray * a = DynamicArray_range(0, 1, 0.1);
//         DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
//         DynamicArray * c = DynamicArray_concat(a, b);
//         ASSERT_EQ(DynamicArray_is_valid(a), 1);
//         ASSERT_EQ(DynamicArray_num_arrays(), 9);
//         DynamicArray_destroy_all();
//         ASSERT_EQ(DynamicArray_is_valid(a), 0);
//         ASSERT_EQ(DynamicArray_num_arrays(), 0);
//         free(a);
//         free(b);
//         free(c);
//    }
}