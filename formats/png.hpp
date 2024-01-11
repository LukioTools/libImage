#pragma once
#include "../Image.hpp"
#include <iostream>
#include <png.h>


namespace Image
{

    class Png : public Image
    {
    public:
        png_structp png = nullptr;
        png_infop info = nullptr;
        png_bytepp data = nullptr;

        std::size_t width() override{
            return png_get_image_width(png, info);
        }
        std::size_t height() override{
            return png_get_image_height(png, info);
        }
        std::size_t channels() override{
            return png_get_channels(png, info);
        }
        std::size_t bitdepth() override{
            return png_get_bit_depth(png, info);
        }
        RGBA get(std::size_t x, std::size_t y) override{
            auto c = channels();
            auto p = &data[y][x];
            return {
                *p,
                (c > 1 ? p[1] : static_cast<unsigned char>(0)),
                (c > 2 ? p[2] : static_cast<unsigned char>(0)),
                (c > 3 ? p[3] : static_cast<unsigned char>(1)),
            };
        }
        unsigned char * get_ptr(std::size_t x, std::size_t y) override{
            return &data[y][x];
        }

        void clear() override{ 
            auto w = png_get_image_width(png, info);
            auto h = png_get_image_height(png, info);
            png_destroy_read_struct(&png, &info, nullptr);
            png_free(png, data);
            png = nullptr;
            info = nullptr;
            data = nullptr;
        }

        void load(const std::string& filename){
            clear();
            FILE *fp = fopen(filename.c_str(), "rb");
            png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
            auto info = png_create_info_struct(png);  
            png_init_io(png, fp);
            png_read_png(png, info, PNG_TRANSFORM_IDENTITY, NULL);
            data = png_get_rows(png, info);
            fclose(fp);
        }

        Png(){}
        Png(const std::string& filename){
            load(filename);
        }
        ~Png() {
            clear();
        }
    };

    static Image* load_png(const std::string& filename){
        auto i = new Png;
        

        return i;
    }
} // namespace Image
