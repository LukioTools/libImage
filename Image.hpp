#pragma once
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <regex>
#include <stdexcept>
#include <utility>
#include <vector>
#include "Callable.hpp"


    // means that init is called once when object is used at runtime which is stupid
//IMAGE_NO_INIT

#ifndef IMAGE_STATIC_SIZE
#define IMAGE_STATIC_SIZE 2
#endif
#define IMAGE_DYNAMIC_VTABLE 1



namespace Image
{
    typedef unsigned int RGBA_val_t;
    struct RGBA //supports only to 4bytes aka 16 bitdepth, if you want more use the get_ptr function 
    {
        RGBA_val_t r = 0;
        RGBA_val_t g = 0;
        RGBA_val_t b = 0;
        RGBA_val_t a = 255;

        RGBA_val_t& operator[](unsigned char index){
            switch (index)
            {
            case 0:
                return r;
            case 1:
                return g;
            case 2:
                return b;
            case 3:
                return a;
            }
            throw std::out_of_range("RGBA::[]::out of range");
        }
    };
    class Image;
    class Image
    {
    public:
        inline virtual std::size_t width(){
            return -1;
        };
        inline virtual std::size_t height(){
            return 0;
        };
        inline virtual std::size_t channels(){
            return 0;
        };
        inline virtual std::size_t bitdepth(){
            return 0;
        };
        inline virtual RGBA get(std::size_t x, std::size_t y){
            return {};
        };
        inline virtual unsigned char* get_ptr(std::size_t x, std::size_t y){
            return nullptr;
        };
        inline virtual bool write_file(const std::string& filename){
            return false;
        }
        inline virtual void clear(){}

        Image() {}
        Image(const Image& other) = delete;
        virtual ~Image() {}
        struct ImageLoader
        {
            std::regex rgx;//matching_file_regex
            Image*(*load)(const std::string& filename);
        };
        
        static std::vector<ImageLoader> image_loaders;

        static std::unique_ptr<Image> load_file(const std::string& filename){
            std::unique_ptr<Image> i(nullptr);
            for (auto& e : image_loaders) {
                if(std::regex_match(filename, e.rgx)){
                    if(e.load){
                        i.reset(e.load(filename));
                        break;
                    }
                }
            }
            return std::move(i);
        }
    };


    inline std::vector<Image::ImageLoader> Image::image_loaders;

} // namespace Image
