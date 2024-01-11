//#include "Image.hpp"
#include "Image.hpp"
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
    Image::Png* img = new Image::Png(filename);
    std::unique_ptr<Image::Image> i(img);



    


    return 0;
}
