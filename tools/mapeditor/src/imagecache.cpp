#include "colorf.hpp"
#include "alphaf.hpp"
#include "imagemapdb.hpp"
#include "imagecache.hpp"
#include "mainwindow.hpp"
#include <FL/Fl_Shared_Image.H>

extern ImageMapDB *g_imageMapDB;
extern MainWindow *g_mainWindow;

Fl_Image *ImageCache::retrieve(uint32_t imageIndex)
{
    if(auto p = m_cache.find(imageIndex); p != m_cache.end()){
        return p->second.get();
    }

    if(const auto [imgBuf, imgW, imgH] = g_imageMapDB->decode(imageIndex, g_mainWindow->removeShadowMosaicEnabled()); imgBuf){
        // understand the Fl_Image and Fl_RGB_Image:
        // Fl_RGB_Image needs a RGBA buffer as constructor parameter, but it won't create its internal copy
        // caller has to make sure the buffer is available and not changed

        // but Fl_Image doesn't require such a buffer
        // immediately after Fl_RGB_Image::copy() returns the Fl_Image pointer
        // we are good to use the RGBA buffer for other purpose
        return (m_cache[imageIndex] = std::unique_ptr<Fl_Image>(Fl_RGB_Image((const uchar *)(imgBuf), imgW, imgH, 4).copy())).get();
    }

    // can't load from imageDB
    // put a place holder, to prevent next load

    m_cache[imageIndex] = {};
    return nullptr;
}
