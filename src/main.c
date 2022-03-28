#include <gloomy/gloomy.h>

#ifdef _TEST_
#include <test/test_main.h>
#endif

int main(int argc, char** argv)
{
#ifdef _TEST_
    
    // Test
    return GLMY_TestMain(argc, argv);

#else

    // Main GLMY
    return GLMY_Main(argc, argv);

#endif
}
