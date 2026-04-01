#include <pspkernel.h>
#include <psppower.h>
#include <unistd.h>

PSP_MODULE_INFO("GravityDefied", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

void ExitGame() {
    g2dTerm();
    intraFontShutdown();
    sceKernelExitGame();
}

int exit_callback(int arg1, int arg2, void *common) {
    ExitGame();

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

void InitGame() {
    SetupCallbacks();
    chdir("assets");

    if (scePowerGetCpuClockFrequency() != 333)
        scePowerSetClockFrequency(333, 333, 166);
}