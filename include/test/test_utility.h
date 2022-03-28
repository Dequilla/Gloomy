#ifndef __GLMY_TEST_UTILITY_H__
#define __GLMY_TEST_UTILITY_H__

#include <stdio.h>
#include <string.h>

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

#endif
