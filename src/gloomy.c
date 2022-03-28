#include <gloomy/gloomy.h>

GLMY_App* glmyInit()
{
    if(!glfwInit())
        return NULL;

    GLMY_App* app = (GLMY_App*)calloc(sizeof(GLMY_App), 1);
    if(app == NULL)
    {
        glmyExit(app);
        return NULL;
    }

    app->window = (GLMY_Window*)calloc(sizeof(GLMY_Window), 1);
    if(app->window == NULL)
    {
        glmyExit(app);
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
        glmyExit(app);
        return NULL;
    }

    glfwMakeContextCurrent(app->window->instance);

    return app;
}

void glmyExit(GLMY_App* app)
{
    if(app && app->window && app->window->instance)
    {
        glfwDestroyWindow(app->window->instance);
        free(app->window);
        app->window = NULL;
        
        free(app);
        app = NULL;
    }

    glfwTerminate();
}

int GLMY_Main(int argc, char** argv)
{
    // Main
    GLMY_App* app = glmyInit();
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

    glmyExit(app);
    return 0;
}

