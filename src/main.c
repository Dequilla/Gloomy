#include <gloomy/gloomy.h>

#ifdef _TEST_
#include <test/test_main.h>
#endif

int main(int argc, char** argv)
{
#ifdef _TEST_
    
    // Test
    return test_main(argc, argv);

#else

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

#endif
}
