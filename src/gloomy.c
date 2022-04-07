#include <gloomy/gloomy.h>

GLMY_App* GLMY_AppInit()
{
    if(!glfwInit())
        return NULL;

    GLMY_App* app = (GLMY_App*)calloc(sizeof(GLMY_App), 1);
    if(app == NULL)
    {
        GLMY_AppExit(app);
        return NULL;
    }

    app->window = (GLMY_Window*)calloc(sizeof(GLMY_Window), 1);
    if(app->window == NULL)
    {
        GLMY_AppExit(app);
        return NULL;
    }

    app->window->instance = glfwCreateWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        WINDOW_TITLE,
        NULL,
        NULL
    );

    if(!app->window->instance)
    {
        GLMY_AppExit(app);
        return NULL;
    }

    glfwMakeContextCurrent(app->window->instance);

    return app;
}

void GLMY_AppExit(GLMY_App* app)
{
    if(app)
    {
        if(app->window && app->window->instance)
        {
            glfwDestroyWindow(app->window->instance);
            free(app->window);
            app->window = NULL;
        }
        
        free(app);
        app = NULL;
    }

    glfwTerminate();
}

int GLMY_Main(int argc, char** argv)
{
    // Main
    GLMY_App* app = GLMY_AppInit();
    if (!app)
        return -1;

    // Red clear color to see it working
    glClearColor(1.f, 0.f, 0.f, 1.f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(app->window->instance))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(app->window->instance);

        /* Poll for and process events */
        glfwPollEvents();
    }

    GLMY_AppExit(app);
    return 0;
}

