#pragma once
#include <cstdint>
#include <functional>
#include "pngtexdb.hpp"
#include "sdldevice.hpp"
#include "buttonbase.hpp"

class AlphaOnButton: public ButtonBase
{
    private:
        uint8_t m_alphaMod;
        uint32_t m_onColor;

    private:
        uint32_t m_texID;

    private:
        int m_onOffX;
        int m_onOffY;
        int m_onRadius;

    public:
        AlphaOnButton(
                Widget::VarDir,
                Widget::VarOff,
                Widget::VarOff,

                int,
                int,
                int,

                uint8_t,
                uint32_t,
                uint32_t,

                std::function<void(Widget *      )> fnOnOverIn  = nullptr,
                std::function<void(Widget *      )> fnOnOverOut = nullptr,
                std::function<void(Widget *, bool)> fnOnClick   = nullptr,
                std::function<void(Widget *      )> fnOnTrigger = nullptr,

                bool    triggerOnDone = true,
                Widget *pwidget       = nullptr,
                bool    autoDelete    = false);

    public:
        void drawEx(int, int, int, int, int, int) const override;
};
