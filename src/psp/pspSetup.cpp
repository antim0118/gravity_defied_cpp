#include <pspkernel.h>
#include <psppower.h>
#include <unistd.h>
#include "glib2d.h"
#include <intraFont.h>
#include "../lcdui/FontStorage.h"

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

    if (scePowerGetCpuClockFrequency() != 333)
        scePowerSetClockFrequency(333, 333, 166);
}

void ShowError(const char *error) {
    auto defaultFont = FontStorage::getFont(Font::STYLE_PLAIN, Font::SIZE_MEDIUM);
    intraFontSetStyle(defaultFont.get()->getTtfFont(), 1.f, BLACK, 0, 0.f, 0);
    intraFontActivate(defaultFont.get()->getTtfFont());

    while (1) {
        g2dClear(WHITE);

        intraFontPrintColumn(defaultFont.get()->getTtfFont(), 20, 30, 480 - 50 * 2, "Error");
        intraFontPrintColumn(defaultFont.get()->getTtfFont(), 20, 50, 480 - 50 * 2, error);

        g2dFlip(G2D_VSYNC);
    }
}