#pragma once

#include <string>

#include <cmrc/cmrc.hpp>
#include "../psp/intra/intraFont.h"

class Font {
public:
    enum FontSize {
        SIZE_SMALL = 8,
        SIZE_MEDIUM = 0,
        SIZE_LARGE = 16
    };

    enum FontStyle
    {
        STYLE_PLAIN = 0,
        STYLE_BOLD,
        STYLE_ITALIC
    };

    enum FontFace {
        FACE_SYSTEM = 0
    };

    Font(FontStyle style, FontSize pointSize);
    ~Font();

    int getBaselinePosition() const;
    int getHeight() const;
    intraFont* getTtfFont() const;
    int charWidth(char c);
    int stringWidth(const std::string& s);
    int substringWidth(const std::string& string, int offset, int len);

private:
    intraFont* ttfFont;
    int height;

    static int getRealFontSize(FontSize size);
};