#include "colorf.hpp"
#include "totype.hpp"
#include "bevent.hpp"
#include "sdldevice.hpp"
#include "alphaonbutton.hpp"

extern PNGTexDB *g_progUseDB;
extern SDLDevice *g_sdlDevice;

AlphaOnButton::AlphaOnButton(
        Widget::VarDir argDir,
        Widget::VarOff argX,
        Widget::VarOff argY,

        int onOffX,
        int onOffY,
        int onRadius,

        uint8_t alphaMod,
        uint32_t onColor,
        uint32_t downTexID,

        std::function<void(Widget *      )> fnOnOverIn,
        std::function<void(Widget *      )> fnOnOverOut,
        std::function<void(Widget *, bool)> fnOnClick,
        std::function<void(Widget *      )> fnOnTrigger,

        bool    triggerOnDone,
        Widget *pwidget,
        bool    autoDelete)

    : ButtonBase
      {
          std::move(argDir),
          std::move(argX),
          std::move(argY),
          0,
          0,

          std::move(fnOnOverIn),
          std::move(fnOnOverOut),
          std::move(fnOnClick),
          std::move(fnOnTrigger),

          SYS_U32NIL,
          SYS_U32NIL,
          SYS_U32NIL,

          0,
          0,
          0,
          0,

          triggerOnDone,
          false,

          pwidget,
          autoDelete,
      }
    , m_alphaMod(alphaMod)
    , m_onColor(onColor)
    , m_texID(downTexID)
    , m_onOffX(onOffX)
    , m_onOffY(onOffY)
    , m_onRadius(onRadius)
{
    if(auto texPtr = g_progUseDB->retrieve(m_texID); !texPtr){
        throw fflerror("can't load down texture: %llu", to_llu(m_texID));
    }

    setSize([this](const Widget *){ return SDLDeviceHelper::getTextureWidth (g_progUseDB->retrieve(m_texID)); },
            [this](const Widget *){ return SDLDeviceHelper::getTextureHeight(g_progUseDB->retrieve(m_texID)); });
}

void AlphaOnButton::drawEx(int dstX, int dstY, int, int, int, int) const
{
    switch(getState()){
        case BEVENT_ON:
            {
                auto texPtr = g_sdlDevice->getCover(m_onRadius, 360);
                if(!texPtr){
                    throw fflerror("can't get round cover: radius = %llu", to_llu(m_onRadius));
                }

                SDLDeviceHelper::EnableRenderBlendMode enableBlendMode(SDL_BLENDMODE_BLEND);
                SDLDeviceHelper::EnableTextureModColor enableModColor(texPtr, colorf::RGBA(m_onColor, m_onColor, m_onColor, m_alphaMod));
                g_sdlDevice->drawTexture(texPtr, dstX + m_onOffX, dstY + m_onOffY);
                break;
            }
        case BEVENT_DOWN:
            {
                auto texPtr = g_progUseDB->retrieve(m_texID);
                if(!texPtr){
                    throw fflerror("can't get down texture: texID = %llu", to_llu(m_texID));
                }

                g_sdlDevice->drawTexture(texPtr, dstX, dstY);
                break;
            }
        default:
            {
                break;
            }
    }
}
