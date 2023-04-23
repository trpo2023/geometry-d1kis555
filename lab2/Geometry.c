#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED_FLASH "\e[5;31m"
#define END "\e[0m"
#define MAX 100

struct Point {
    double x;
    double y;
};

struct Circle {
    struct Point center;
    double radius;
};

enum Bugs {
    BUG_NAME,
    BUG_STAPLES,
    BUG_NUMBER,
    BUG_UNIDENTIFIED_VARIABLES,
    BUG_EXPECT_COMMA,
    BUG_STAPLES_2,
    BUG_EXTRA_POINT,
};

void output_bugs(int errors, int num, char* ch)
{
    for (int i = 0; i < num; i++) {
        putchar(' ');
    }
    printf("^\n");

    switch (errors) {
    case BUG_NAME:
        printf("An error %d was found in the input line %s'Circle'%s\n",
               num,
               RED_FLASH,
               END);
        break;
    case BUG_STAPLES:
        if (*ch == ')') {
            printf("An error %d was found in the input line %s')'%s\n",
                   num,
                   RED_FLASH,
                   END);
            break;
        } else {
            printf("An error %d was found in the input line %s'('%s\n",
                   num,
                   RED_FLASH,
                   END);
            break;
        }
    case BUG_STAPLES_2:
        printf("An error %d was found in the input line %s')'%s\n",
               num,
               RED_FLASH,
               END);
        break;
    case BUG_NUMBER:
        printf("An error %d was found in the input line %s'double'%s\n",
               num,
               RED_FLASH,
               END);
        break;
    case BUG_UNIDENTIFIED_VARIABLES:
        printf("An error %d was found in the input line %s'variable'%s\n",
               num,
               RED_FLASH,
               END);
        break;
    case BUG_EXPECT_COMMA:
        printf("An error %d was found in the input line %s','%s\n",
               num,
               RED_FLASH,
               END);
        break;
    case BUG_EXTRA_POINT:
        printf("An error %d was found in the input line %s'.'%s\n",
               num,
               RED_FLASH,
               END);
        break;
    }
}

void to_lower(char* str, int ch)
{
    for (int i = 0; i < ch; i++) {
        str[i] = tolower(str[i]);
    }
}

double x_data(char* arr, int* num)
{
    char free_space[20];
    int i = 0;

    while (!isdigit(arr[*num]) && arr[*num] != '-') {
        if (arr[*num] == '(') {
            *num += 1;
        } else {
            if (arr[*num] == ')') {
                output_bugs(BUG_STAPLES, *num, &arr[*num]);
                exit(1);
            }
            if (arr[*num] == ' ') {
                output_bugs(BUG_STAPLES, *num, &arr[*num]);
                exit(1);
            } else {
                output_bugs(BUG_NUMBER, *num, NULL);
                exit(1);
            }
        }
    }

    while (isdigit(arr[*num]) || arr[*num] == '-' || arr[*num] == '.') {
        free_space[i] = arr[*num];
        i++;
        *num += 1;
    }

    if (arr[*num] != ' ') {
        output_bugs(BUG_UNIDENTIFIED_VARIABLES, *num, NULL);
        exit(1);
    }
    char* dumpster;
    return strtod(free_space, &dumpster);
}

double y_data(char* arr, int* num)
{
    char free_space[20];
    int i = 0;

    while (!isdigit(arr[*num]) && arr[*num] != '-') {
        if (arr[*num] == ' ') {
            *num += 1;
        } else {
            output_bugs(BUG_NUMBER, *num, NULL);
            exit(1);
        }
    }

    while (isdigit(arr[*num]) || arr[*num] == '-' || arr[*num] == '.') {
        free_space[i] = arr[*num];
        i++;
        *num += 1;
    }

    while (arr[*num] != ',') {
        if (arr[*num] == ' ') {
            *num += 1;
        } else {
            output_bugs(BUG_EXPECT_COMMA, *num, NULL);
            exit(1);
        }
    }
    char* dumpster;
    return strtod(free_space, &dumpster);
}