#include "CanvasImpl.h"

#include <stdexcept>
#include <iostream>

#include "Canvas.h"

CanvasImpl::CanvasImpl(Canvas* canvas)
{
    this->canvas = canvas;

    controls_init();
    intraFontInit();
    g2dInit();

    g2dClear(G2D_RGBA(255, 255, 255, 255));
}

CanvasImpl::~CanvasImpl()
{
    g2dTerm();
    intraFontShutdown();
}

void CanvasImpl::repaint()
{
    g2dFlip(G2D_VSYNC);
    g2dClear(G2D_RGBA(255, 255, 255, 255));
}

int CanvasImpl::getWidth()
{
    return width;
}

int CanvasImpl::getHeight()
{
    return height;
}

void CanvasImpl::processEvents()
{
    int analog = 80;
    printf("controls_AnalogX() = %d\n", controls_AnalogX());
    controls_read();

    if (controls_pressed(PSP_CTRL_START))// if (controls_released(PSP_CTRL_START))
        canvas->pressedEsc();

    /* PRESSED */
    if (controls_pressed(PSP_CTRL_CROSS))
        canvas->publicKeyPressed(Canvas::Keys::FIRE);
    
    if (controls_pressed(PSP_CTRL_LEFT)
        || (!AnalogLeft && controls_AnalogX() < -analog)) {
        AnalogLeft = true;
        canvas->publicKeyPressed(Canvas::Keys::LEFT);
    }
    if (controls_pressed(PSP_CTRL_RIGHT)
        || (!AnalogRight && controls_AnalogX() > analog)) {
        AnalogRight = true;
        canvas->publicKeyPressed(Canvas::Keys::RIGHT);
    }
    if (controls_pressed(PSP_CTRL_UP) || controls_pressed(PSP_CTRL_RTRIGGER)) canvas->publicKeyPressed(Canvas::Keys::UP);
    if (controls_pressed(PSP_CTRL_DOWN) || controls_pressed(PSP_CTRL_LTRIGGER)) canvas->publicKeyPressed(Canvas::Keys::DOWN);

    /* RELEASED */
    if (controls_released(PSP_CTRL_CROSS))
        canvas->publicKeyReleased(Canvas::Keys::FIRE);

    if (controls_released(PSP_CTRL_LEFT)
        || (AnalogLeft && controls_AnalogX() > -analog)) {
        AnalogLeft = false;
        canvas->publicKeyReleased(Canvas::Keys::LEFT);
    }
    if (controls_released(PSP_CTRL_RIGHT)
        || (AnalogRight && controls_AnalogX() < analog)) {
        AnalogRight = false;
        canvas->publicKeyReleased(Canvas::Keys::RIGHT);
    }
    if (controls_released(PSP_CTRL_UP) || controls_released(PSP_CTRL_RTRIGGER)) canvas->publicKeyReleased(Canvas::Keys::UP);
    if (controls_released(PSP_CTRL_DOWN) || controls_released(PSP_CTRL_LTRIGGER)) canvas->publicKeyReleased(Canvas::Keys::DOWN);
}

void CanvasImpl::setWindowTitle(const std::string& title)
{
}