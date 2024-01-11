//#include "Image.hpp"
#include "Image.hpp"
#include "formats/png.hpp"
#include <asm-generic/ioctls.h>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <png.h>
#include <pngconf.h>
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
    //Image::Image::init();
    //auto i = Image::Image::load_file("img.png");
    Image::Png* img = new Image::Png(filename);
    std::unique_ptr<Image::Image> i(img);
    slog(img->data)
    slog(img->info)
    slog(img->png)

    slog(img->bitdepth())
    slog(img->channels())
    
    auto r = i->get(0, 0);

    std::cout << r.r << " / " << r.g << " / " << r.b << std::endl;

    winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    auto width = win.ws_col;
    auto height = win.ws_row;

    auto hr = static_cast<double>(img->height())/height;
    auto wr = static_cast<double>(img->width())/width;

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
    


    return 0;
}
