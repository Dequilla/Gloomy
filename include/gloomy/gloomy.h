#ifndef __GLMY_GLOOMY_H__
#define __GLMY_GLOOMY_H__

#include <GLFW/glfw3.h>

#include <gloomy/utility.h>


GLMY_BOOL glmyInit()
{
    if(!glfwInit())
        return GLMY_FALSE;

    return GLMY_TRUE;
}

void glmyExit()
{
    glfwTerminate();
}

#endif
