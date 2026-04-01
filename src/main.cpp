#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>

#include "Micro.h"

#include "psp/pspSetup.cpp"

int main(int argc, char **argv) {
    InitGame();

    try {
        std::unique_ptr<Micro> micro = std::make_unique<Micro>();
        micro->startApp(argc, argv);
    }
    catch (std::exception &e) {
        ShowError(e.what());
        return EXIT_FAILURE;
    }

    ExitGame();

    return EXIT_SUCCESS;
};
