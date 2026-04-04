#include "Font.h"

#include <stdexcept>

Font::Font(FontStyle style, FontSize pointSize)
{
    int realSize = getRealFontSize(pointSize);
    this->ttfFont = intraFontLoadTTF("assets/FontSansSerif.ttf", INTRAFONT_STRING_UTF8, realSize);
    if (!this->ttfFont || this->ttfFont == NULL)
        printf("[ERR] error loading font \"FontSansSerif.ttf\" pointSize:%d  realSize:%d \n", pointSize, realSize);
    // TTF_SetFontStyle(font, style);
    this->height = realSize;
}

Font::~Font()
{
    intraFontUnload(ttfFont);
}

int Font::getBaselinePosition() const
{
    return height;
}

int Font::getHeight() const
{
    return height;
}

intraFont* Font::getTtfFont() const
{
    return ttfFont;
}

int Font::charWidth(char c)
{
    return stringWidth(std::string(1, c));
}

int Font::stringWidth(const std::string& s)
{
    return intraFontMeasureText(ttfFont, s.c_str());
}

int Font::substringWidth(const std::string& string, int offset, int len)
{
    return stringWidth(string.substr(offset, len));
}

int Font::getRealFontSize(FontSize size)
{
    switch (size) {
    case SIZE_LARGE:
        return 30;
    case SIZE_MEDIUM:
        return 16;
    case SIZE_SMALL:
        return 12;
    default:
        throw std::runtime_error("unknown font size: " + std::to_string(size));
    }
}
