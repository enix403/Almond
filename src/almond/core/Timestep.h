#pragma once

namespace Almond {
    struct Timestep
    {
    public:
        Timestep(float deltatime = 0.f)
        :   m_DeltaTime(deltatime)
        {}
        
        operator float() const { return m_DeltaTime; }

        inline float Seconds() const { return m_DeltaTime; }
        inline float Milliseconds() const { return m_DeltaTime * 1000.f; }

    private:
        float m_DeltaTime;
    };
}