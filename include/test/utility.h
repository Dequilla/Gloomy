#ifndef __GLMY_TEST_UTILITY_H__
#define __GLMY_TEST_UTILITY_H__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include <time.h>

void GLMY_TestSection(char* sectionName)
{
    printf("\n\n------[ %s ]------\n\n", sectionName);
}

void GLMY_TestSubSection(char* sectionName)
{
    size_t count = 0,
           size = strlen(sectionName);
    for(; count < size; count++)
        printf("_");

    printf("\n%s\n\n", sectionName);
}

void GLMY_InitRandom()
{
    static bool isInitialized = false;
    if(!isInitialized)
    {
        srand(time(NULL));
        isInitialized = true;
    }
}

int GLMY_IntRandom(int min, int max)
{
    if(min > max)
    {
        int inter = max;
        max = min;
        max = inter;
    }

    GLMY_InitRandom();

    return (rand() % (max - min + 1)) + min;
}

char* GLMY_StringGenerateRandom(size_t size)
{
    char* str = (char*)calloc(sizeof(char), size);
    if(str == NULL) return NULL;

    size_t index = 0;
    for(; index < size - 1; index++)
        str[index] = (char)GLMY_IntRandom(32, 126);

    str[size - 1] = '\0';

    return str;
}

#endif
