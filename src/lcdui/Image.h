#pragma once

#include <string>
#include <cstring>

#include "../psp/glib2d.h"

class Image
{
private:
    g2dImage *img;

public:
    Image(const std::string &embeddedPath);
    Image(int width, int height);
    ~Image();

    int getWidth() const;
    int getHeight() const;
    g2dImage *getImage() const;
};
