#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <unordered_map>
#include <FL/Fl_Image.H>
#include <FL/Fl_RGB_Image.H>
#include "totype.hpp"
#include "fflerror.hpp"

class ImageCache
{
    private:
        std::unordered_map<uint32_t, std::unique_ptr<Fl_Image>> m_cache;

    public:
        ImageCache() = default;

    public:
        Fl_Image *retrieve(uint32_t);

    public:
        Fl_Image *retrieve(uint8_t fileIndex, uint16_t imageIndex)
        {
            return retrieve((to_u32(fileIndex) << 16) + imageIndex);
        }

    public:
        void clear()
        {
            m_cache.clear();
        }
};
