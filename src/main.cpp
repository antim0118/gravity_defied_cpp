#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>
#include <pspkernel.h>
#include <unistd.h>

#include "Micro.h"

PSP_MODULE_INFO("GravityDefied", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

int main(int argc, char** argv)
{
    chdir("assets");
    try {
        std::unique_ptr<Micro> micro = std::make_unique<Micro>();
        micro->startApp(argc, argv);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    sceKernelExitGame();

    return EXIT_SUCCESS;
};
