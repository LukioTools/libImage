#pragma once
#include "../Image.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <png.h>


namespace Image
{

    class Png : public Image
    {
    private:
        inline RGBA get_16(std::size_t x, std::size_t y,std::size_t& c){
            unsigned int* p = &reinterpret_cast<unsigned int**>(data)[y][x];
            return {
                *p,
                (c > 1 ? static_cast<RGBA_val_t>(p[1]) : static_cast<RGBA_val_t>(0U)),
                (c > 2 ? static_cast<RGBA_val_t>(p[2]) : static_cast<RGBA_val_t>(0U)),
                (c > 3 ? static_cast<RGBA_val_t>(p[3]) : static_cast<RGBA_val_t>(1U)),
            };
        }


        inline RGBA get_8(std::size_t x, std::size_t y, std::size_t c){
            auto p = &data[y][x*c];
            return {
                *p,
                (c > 1 ? static_cast<RGBA_val_t>(p[1]) : static_cast<RGBA_val_t>(0U)),
                (c > 2 ? static_cast<RGBA_val_t>(p[2]) : static_cast<RGBA_val_t>(0U)),
                (c > 3 ? static_cast<RGBA_val_t>(p[3]) : static_cast<RGBA_val_t>(1U)),
            };
        }
    public:
        png_structp png   =  nullptr;
        png_infop   info  =  nullptr;
        png_bytepp  data  =  nullptr;

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
            auto d  =   bitdepth();
            auto c =    channels();

                            //premature optimization
            if(d == 16)
                return get_16(x,y,c);
            if(d == 8)
                return get_8(x,y, c);


            auto p = get_ptr(x, y);


            
            unsigned char total = 0;
            unsigned char bits_read_from_byte = 0;
            RGBA ret;

            for (size_t j = 0; j < std::clamp(c, 0LU, 4LU); j++)
            {
                for (size_t i = 0; i < d; i++)
                {
                    ret[j] |= *p & (1 << d);
                    bits_read_from_byte++;

                    if(bits_read_from_byte >= sizeof(unsigned char)){
                        p++;
                        bits_read_from_byte = 0;
                    }
                }
            }
            return ret;
            
            

            
            //int bitmask = 0;
            //for (size_t i = 0; i < d; i++)
            //    bitmask |= (1<<i);
            

            //auto c =    channels();
            //auto p =    &data[y][x];
            

            return {};
        }
        inline unsigned char * get_ptr(std::size_t x, std::size_t y) override{
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
            png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
            info = png_create_info_struct(png);  
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
} // namespace Image
