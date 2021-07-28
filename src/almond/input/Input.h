#pragma once

#include "almond/utils/holders.h"

namespace Almond
{
    class Input
    {
    public:
        inline static bool IsKeyPressed(int keycode)
        {
            return s_InputImpl->IsKeyPressedImpl(keycode);
        }
        inline static bool IsMouseButtonPressed(int btncode)
        {
            return s_InputImpl->IsMouseButtonPressedImpl(btncode);
        }
        inline static FloatTuple GetMousePosition()
        {
            return s_InputImpl->GetMousePositionImpl();
        }
        inline static float GetMouseX()
        {
            return s_InputImpl->GetMouseXImpl();
        }
        inline static float GetMouseY()
        {
            return s_InputImpl->GetMouseYImpl();
        }

    protected:
        virtual bool IsKeyPressedImpl(int keycode) const = 0;
        virtual bool IsMouseButtonPressedImpl(int btncode) const = 0;
        virtual FloatTuple GetMousePositionImpl() const = 0;
        virtual float GetMouseXImpl() const = 0;
        virtual float GetMouseYImpl() const = 0;

    public:
        static Input* s_InputImpl;
    };
} // namespace Almond