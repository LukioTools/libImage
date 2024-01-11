//#include "Image.hpp"
#include "formats/png.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <png.h>
#include <pngconf.h>
#include <string>
#include <string_view>

std::string filename = "img.png";







int main(int argc, char const *argv[])
{
    //Image::Image::init();
    //auto i = Image::Image::load_file("img.png");
    Image::Png img(filename);

    std::clog << "img.channels(): " << img.channels() << std::endl;
    std::clog << "img.bitdepth(): " << img.bitdepth() << std::endl;


    return 0;
}
