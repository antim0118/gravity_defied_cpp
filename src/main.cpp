#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>
#include <pspkernel.h>
#include <unistd.h>

#include "Micro.h"
#include "psp/glib2d.h"
#include "psp/intra/intraFont.h"

PSP_MODULE_INFO("GravityDefied", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

int exit_callback(int arg1, int arg2, void *common) {
    g2dTerm();
    intraFontShutdown();
    sceKernelExitGame();

    return 0;
}

int CallbackThread(SceSize args, void *argp) {
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();

    return 0;
}

int SetupCallbacks(void) {
    int thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);

    if (thid >= 0)
        sceKernelStartThread(thid, 0, 0);

    return thid;
}

int main(int argc, char **argv) {
    SetupCallbacks();
    chdir("assets");
    try {
        std::unique_ptr<Micro> micro = std::make_unique<Micro>();
        micro->startApp(argc, argv);
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    sceKernelExitGame();

    return EXIT_SUCCESS;
};
