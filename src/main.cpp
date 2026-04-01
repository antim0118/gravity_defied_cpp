#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>

#include "Micro.h"
#include "psp/glib2d.h"
#include "psp/intra/intraFont.h"

#include "psp/pspSetup.c"

int main(int argc, char **argv) {
    InitGame();

    try {
        std::unique_ptr<Micro> micro = std::make_unique<Micro>();
        micro->startApp(argc, argv);
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    ExitGame();

    return EXIT_SUCCESS;
};
