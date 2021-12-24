#pragma once

#include "almond/input/Input.h"


namespace Almond {
    class LinuxInput: public Input {
    protected:
        bool        IsKeyPressedImpl(int keycode) const override;
        bool        IsMouseButtonPressedImpl(int btncode) const override;
        float_vec2   GetMousePositionImpl() const override;
        float       GetMouseXImpl() const override;
        float       GetMouseYImpl() const override;
    };
}