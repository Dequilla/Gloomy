#ifndef __GLMY_GLOOMY_H__
#define __GLMY_GLOOMY_H__

#include <stdlib.h>

#include <GLFW/glfw3.h>

#include <gloomy/utility.h>
#include <gloomy/config.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Gloomy"

typedef struct {
    GLFWwindow* instance;
} GLMY_Window;

typedef struct {
    GLMY_Window* window;
    GLMY_Config* config;
} GLMY_App;


GLMY_App* GLMY_AppInit();
void GLMY_AppExit(GLMY_App* app);

int GLMY_Main(int argc, char** argv);

#endif
