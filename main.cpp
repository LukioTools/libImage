//#include "Image.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <png.h>
#include <pngconf.h>
#include <string>
#include <string_view>

std::string filename = "img.png";



struct read_png_data_t
{
    png_structp png = nullptr;
    png_infop info = nullptr;
    png_bytepp rows;
    //png_bytepp rows = nullptr;

    ~read_png_data_t(){
        auto w = png_get_image_width(png, info);
        auto h = png_get_image_height(png, info);
        png_destroy_read_struct(&png, &info, nullptr);
        png_free(png, rows);
        png = nullptr;
        info = nullptr;
        rows =nullptr;
    }
};

read_png_data_t read_png(const std::string& filename)
{
    FILE *fp = fopen(filename.c_str(), "rb");
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    auto info = png_create_info_struct(png);  
    png_init_io(png, fp);
    png_read_png(png, info, PNG_TRANSFORM_IDENTITY, NULL);
    auto row_ptr = png_get_rows(png, info);
    fclose(fp);
    return {
        png,
        info,
        row_ptr,
    };
}

int main(int argc, char const *argv[])
{
    //Image::Image::init();
    //auto i = Image::Image::load_file("img.png");

    auto r = read_png(filename);
    auto w = png_get_image_width(r.png, r.info);
    auto h = png_get_image_height(r.png, r.info);
    std::cout << w << ':' << h << std::endl;

    std::cout << (int)r.rows[0][0] << (int)r.rows[0][1] << (int)r.rows[0][2] << std::endl;

    return 0;
}
