//#include "Image.hpp"
#include "Image.hpp"
#include "formats/png.hpp"
#include <asm-generic/ioctls.h>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <png.h>
#include <pngconf.h>
#include <regex>
#include <string>
#include <string_view>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "def.hpp"



std::string filename = "img.png";



#define slog(var) std::clog << #var": " <<  var << std::endl;



int main(int argc, char const *argv[])
{
    std::cout << (std::regex_match(filename, std::regex("*.")) ? "true" : "false") << '\n';
    /*
    
    Image::Png::init();
    auto i = Image::Image::load_file("img.png");
    auto r = i->get(0, 0);

    std::cout << r.r << " / " << r.g << " / " << r.b << std::endl;

    winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    auto width = win.ws_col;
    auto height = win.ws_row;

    auto hr = static_cast<double>(i->height())/height;
    auto wr = static_cast<double>(i->width())/width;

    slog(hr)
    slog(wr)
    for (size_t h = 0; h < height; h++)
    {
        for (size_t w = 0; w < width; w++)
        {
            auto e = i->get(w*wr,h*hr);
            std::cout << color_bg_rgb(e) << ' ' << attr_reset;
        }
        std::cout << '\n' << '\r';
    }
    */


    return 0;
}
