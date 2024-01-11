#pragma once
#include "../Image.hpp"
#include <png.h>
#define PNG_VTABLE_INDEX BOOST_PP_INC(IMAGE_INDEX)




namespace Image
{
    class Png : public Image
    {
    private:
    public:
        Png(){vtable_index = PNG_VTABLE_INDEX;}
        Png(const std::string& filename){vtable_index = PNG_VTABLE_INDEX;
        

        }
        ~Png() {

        }
    };

    static Image* load_png(const std::string& filename){
        auto i = new Png;
        

        return i;
    }
} // namespace Image


#undef IMAGE_INDEX
#define IMAGE_INDEX PNG_VTABLE_INDEX
