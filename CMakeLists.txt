cmake_minimum_required(VERSION 3.24)
project(gravity_defied_cpp C CXX)

unset(ENV{PKG_CONFIG_PATH})

find_package(PkgConfig REQUIRED)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/utils/Time.cpp
    src/utils/EmbedFileStream.cpp
    src/main.cpp
    src/MathF16.cpp
    src/GameCanvas.cpp
    src/GamePhysics.cpp
    src/TimerOrMotoPartOrMenuElem.cpp
    src/class_10.cpp
    src/GameLevel.cpp
    src/LevelLoader.cpp
    src/Micro.cpp
    src/TextRender.cpp
    src/GameMenu.cpp
    src/SettingsStringRender.cpp
    src/MenuManager.cpp
    src/RecordManager.cpp
    src/Timer.cpp
    src/lcdui/CanvasImpl.cpp
    src/lcdui/Canvas.cpp
    src/lcdui/Graphics.cpp
    src/lcdui/Image.cpp
    src/lcdui/Font.cpp
    src/lcdui/Command.cpp
    src/lcdui/FontStorage.cpp
    src/rms/RecordEnumerationImpl.cpp
    src/rms/RecordStore.cpp
    src/psp/glib2d.c
    src/psp/ctrl/controls.c
    src/psp/intra/intraFont.c
)

include(cmake/CMakeRC.cmake)

cmrc_add_resource_library(Assets
    NAMESPACE assets
    ALIAS Assets::Assets
    WHENCE assets
    assets/bluearm.png
    assets/helmet.png
    assets/sprites.png
    assets/blueleg.png
    assets/bluebody.png
    assets/logo.png
    assets/fender.png
    assets/levels.mrg
    assets/engine.png
    assets/splash.png
    assets/raster.png
    assets/FontSansSerif.ttf
)

add_executable(GravityDefied ${SOURCES})

target_compile_features(GravityDefied PRIVATE cxx_std_17)
# target_compile_options(GravityDefied PRIVATE -Wall -Wextra)
target_compile_options(GravityDefied PRIVATE -O3 -G0 -Wall -Wno-trigraphs -Ofast -ffast-math -funroll-loops -fomit-frame-pointer -DNDEBUG -ffunction-sections -fdata-sections)

target_include_directories(GravityDefied PRIVATE include)

target_link_directories(GravityDefied PRIVATE)

set_target_properties(GravityDefied PROPERTIES LINK_FLAGS_RELEASE -s)

target_link_libraries(GravityDefied 
                        Assets::Assets
                        png
                        jpeg
                        psppower
                        z
                        pspge
                        pspgu
                        m
                        c
                        intrafont
                        pspctrl
                        pspdisplay
                        pspsystemctrl_kernel
                        psprtc
                        pspgum
                        pspvfpu
                        pspusb
                        pspusbstor
                        pspkubridge
                        pspvram
                        bz2
                        freetype)

# Copy assets to the build directory
file(COPY assets/levels.mrg DESTINATION ${CMAKE_BINARY_DIR})

create_pbp_file(TARGET GravityDefied TITLE "${CMAKE_PROJECT_NAME}"
  # ICON_PATH
  # BACKGROUND_PATH
  # PREVIEW_PATH
)