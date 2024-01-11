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

#define IMAGE_INDEX 0
#include <boost/preprocessor/inc.hpp>


namespace Image
{
    struct RGBA
    {
        unsigned char r = 0;
        unsigned char g = 0;
        unsigned char b = 0;
        unsigned char a = 1;
    };
    
    struct ImageVtable
    {
        std::unique_ptr<Callable<std::size_t>> width = nullptr;//std::size_t(*fn_width)();
        std::unique_ptr<Callable<std::size_t>> height = nullptr;//std::size_t(*fn_height)();
        std::unique_ptr<Callable<std::size_t>> channels = nullptr;//std::size_t(*fn_channels)();
        std::unique_ptr<Callable<std::size_t>> bitdepth = nullptr;//std::size_t(*fn_bitdepth)();
        std::unique_ptr<Callable<RGBA, std::size_t, std::size_t>> get = nullptr;//RGBA(*fn_get)(std::size_t x, std::size_t y);
        std::unique_ptr<Callable<unsigned char*, std::size_t, std::size_t>> get_ptr = nullptr;//unsigned char*(*fn_get_ptr)(std::size_t x, std::size_t y);
        std::unique_ptr<Callable<bool, const std::string&>> write = nullptr;//unsigned char*(*fn_get_ptr)(std::size_t x, std::size_t y);
    };
    
    class Image
    {
    private:
        
        #ifndef IMAGE_NO_INIT
    public:
        static void  init()
        #else
    private:
        static void  useage()
        #endif
        {   
            #if defined(IMAGE_NO_INIT)
            if (!has_initialized)
            {
                has_initialized = true;
            #endif // IMAGE_NO_INIT
            
                image_vtable.emplace_back(
                    ImageVtable{
                    std::unique_ptr<Callable<std::size_t>>(new Basic_Fn<std::size_t>{[]()->std::size_t{return 0;}}),
                    std::unique_ptr<Callable<std::size_t>>(new Basic_Fn<std::size_t>{[]()->std::size_t{return 0;}}),
                    std::unique_ptr<Callable<std::size_t>>(new Basic_Fn<std::size_t>{[]()->std::size_t{return 0;}}),
                    std::unique_ptr<Callable<std::size_t>>(new Basic_Fn<std::size_t>{[]()->std::size_t{return 0;}}),
                    std::unique_ptr<Callable<RGBA, std::size_t, std::size_t>>(new Basic_Fn<RGBA, std::size_t, std::size_t>{[](std::size_t x, std::size_t y)->RGBA{return {0,0,0,1};}}), 
                    std::unique_ptr<Callable<unsigned char*, std::size_t, std::size_t>>(new Basic_Fn<unsigned char*, std::size_t, std::size_t>{[](std::size_t x, std::size_t y)->unsigned char*{return nullptr;}}), 
                    std::unique_ptr<Callable<bool, const std::string&>>(new Basic_Fn<bool, const std::string&>{[](const std::string& fn)->bool{return false;}}), 
                    }
                );

            #if defined(IMAGE_NO_INIT)
            }
            #endif // IMAGE_NO_INIT
        }
    public:

        
        size_t vtable_index=IMAGE_INDEX;
        //c++ vtables are overrated af

        inline std::size_t width(){
            #ifndef IMAGE_NO_INIT
            #else
            useage();
            #endif
            if(!image_vtable[vtable_index].width || image_vtable.size() <= vtable_index)
                return image_vtable[IMAGE_INDEX].width->call();

            return image_vtable[vtable_index].width->call();

        };
        inline std::size_t height(){
            #ifndef IMAGE_NO_INIT
            #else
            useage();
            #endif
            if(!image_vtable[vtable_index].height || image_vtable.size() <= vtable_index)
                return image_vtable[IMAGE_INDEX].height->call();

            return image_vtable[vtable_index].height->call();

        };
        inline std::size_t channels(){
            #ifndef IMAGE_NO_INIT
            #else
            useage();
            #endif
            if(!image_vtable[vtable_index].channels || image_vtable.size() <= vtable_index)
                return image_vtable[IMAGE_INDEX].channels->call();

            return image_vtable[vtable_index].channels->call();

        };
        inline std::size_t bitdepth(){
            #ifndef IMAGE_NO_INIT
            #else
            useage();
            #endif
            if(!image_vtable[vtable_index].bitdepth || image_vtable.size() <= vtable_index)
                return image_vtable[IMAGE_INDEX].bitdepth->call();

            return image_vtable[vtable_index].bitdepth->call();

        };
        inline RGBA get(std::size_t x, std::size_t y){
            #ifndef IMAGE_NO_INIT
            #else
            useage();
            #endif
            if(!image_vtable[vtable_index].get || image_vtable.size() <= vtable_index)
                return image_vtable[IMAGE_INDEX].get->call(x,y);

            return image_vtable[vtable_index].get->call(x,y);

        };
        inline unsigned char* get_ptr(std::size_t x, std::size_t y){
            #ifndef IMAGE_NO_INIT
            #else
            useage();
            #endif
            if(!image_vtable[vtable_index].get_ptr || image_vtable.size() <= vtable_index)
                return image_vtable[IMAGE_INDEX].get_ptr->call(x,y);
            return image_vtable[vtable_index].get_ptr->call(x,y);

        };

        Image() {}
        Image(const Image& other) = delete;
        ~Image() {}

        #ifndef IMAGE_DYNAMIC_VTABLE
        static std::array<ImageVtable, IMAGE_STATIC_SIZE> 
        #else
        static std::vector<ImageVtable>
        #endif


        image_vtable;

        #ifndef IMAGE_NO_INIT
        #else
        static bool has_initialized;
        #endif

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
        inline bool write_file(const std::string& filename){
            #ifndef IMAGE_NO_INIT
            #else
            useage();
            #endif
            if(!image_vtable[vtable_index].get_ptr || image_vtable.size() <= vtable_index)
                return image_vtable[IMAGE_INDEX].write->call(filename);
            return image_vtable[vtable_index].write->call(filename);
        }

        //static ImageVtable& new_vtable(const ImageVtable&& table){
        //    #ifndef IMAGE_NO_INIT
        //
        //    #else
        //    useage();
        //    #endif
        //    return image_vtable.emplace_back(table);
        //}
    };
    #ifndef IMAGE_NO_INIT
    #else
    inline bool Image::has_initialized = false;
    #endif


    #ifndef IMAGE_DYNAMIC_VTABLE
    inline std::array<ImageVtable, IMAGE_STATIC_SIZE> 
    #else
    inline std::vector<ImageVtable>
    #endif
    Image::image_vtable;

    inline std::vector<Image::ImageLoader> Image::image_loaders;

} // namespace Image
