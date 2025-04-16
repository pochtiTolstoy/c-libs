#ifndef INSERT_H
#define INSERT_H
#include "../../s21_string.h"
const char *input_string1[] = {
    "Alpha", "Beta", "Gamma", "Delta", "Epsilon",

};

const char *input_string2[] = {
    "Bravo", "Charlie", "Delta", "Echo", "Foxtrot",

};

int insert_indices[] = {
    1, 2, 3, 4, 0,

};

const char *output_string[] = {
    "ABravolpha", "BeCharlieta", "GamDeltama", "DeltEchoa", "FoxtrotEpsilon",

};

const s21_size_t count_strings =
    sizeof(input_string1) / sizeof(input_string1[0]);
s21_size_t test_num = 0;

#endif