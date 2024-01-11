#pragma once
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <regex>
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
    struct RGBA
    {
        unsigned char r = 0;
        unsigned char g = 0;
        unsigned char b = 0;
        unsigned char a = 1;
    };
    class Image
    {
    public:
        inline virtual std::size_t width(){
            return 0;
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

        Image() {}
        Image(const Image& other) = delete;
        ~Image() {}
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
