#pragma once

#include <memory>
#include "../psp/ctrl/controls.h"
#include "../psp/intra/intraFont.h"
#include "../psp/glib2d.h"

class Canvas;

class CanvasImpl {
private:
    Canvas *canvas;
    bool AnalogLeft = false;
    bool AnalogRight = false;

    const int width = 480;
    const int height = 272;

public:
    CanvasImpl(Canvas* canvas);
    ~CanvasImpl();

    void repaint();
    int getWidth();
    int getHeight();

    void processEvents();
    void setWindowTitle(const std::string& title);
};