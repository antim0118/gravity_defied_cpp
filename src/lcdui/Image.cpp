#include "Image.h"

#include <stdexcept>
#include <string>

Image::Image(int width, int height)
{
    this->img = g2dTexCreatePlaceholder(width, height);
}

Image::Image(const std::string& embeddedPath)
{
    this->img = g2dTexLoad(embeddedPath.c_str(), NULL, 0, G2D_SWIZZLE);
    if (!this->img)
        printf("[ERR] Image.load() error loading \"%s\"\n", embeddedPath.c_str());
}

Image::~Image()
{
    g2dTexFree(&this->img);;
}

int Image::getWidth() const
{
    return this->img->w;
}

int Image::getHeight() const
{
    return this->img->h;
}

g2dImage* Image::getImage() const
{
    return this->img;
}
