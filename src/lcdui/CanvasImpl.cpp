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
    controls_read();

    if (controls_pressed(PSP_CTRL_START))// if (controls_released(PSP_CTRL_START))
        canvas->pressedEsc();

    /* PRESSED */
    if (controls_pressed(PSP_CTRL_CROSS))
        canvas->publicKeyPressed(Canvas::Keys::FIRE);
    
    if (controls_pressed(PSP_CTRL_LEFT)) canvas->publicKeyPressed(Canvas::Keys::LEFT);
    if (controls_pressed(PSP_CTRL_RIGHT)) canvas->publicKeyPressed(Canvas::Keys::RIGHT);
    if (controls_pressed(PSP_CTRL_UP)) canvas->publicKeyPressed(Canvas::Keys::UP);
    if (controls_pressed(PSP_CTRL_DOWN)) canvas->publicKeyPressed(Canvas::Keys::DOWN);

    /* RELEASED */
    if (controls_released(PSP_CTRL_CROSS))
        canvas->publicKeyReleased(Canvas::Keys::FIRE);

    if (controls_released(PSP_CTRL_LEFT)) canvas->publicKeyReleased(Canvas::Keys::LEFT);
    if (controls_released(PSP_CTRL_RIGHT)) canvas->publicKeyReleased(Canvas::Keys::RIGHT);
    if (controls_released(PSP_CTRL_UP)) canvas->publicKeyReleased(Canvas::Keys::UP);
    if (controls_released(PSP_CTRL_DOWN)) canvas->publicKeyReleased(Canvas::Keys::DOWN);
}

void CanvasImpl::setWindowTitle(const std::string& title)
{
}