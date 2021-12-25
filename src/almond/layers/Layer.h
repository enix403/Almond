#pragma once

#include <string>

#include "almond/events/Event.h"
#include "almond/core/Timestep.h"

namespace Almond
{

    class Layer
    {
    public:
        Layer(const std::string& name = "Layer")
        : m_DebugName(name) {}

		virtual ~Layer() = default;

        virtual void OnAttach() { };
        virtual void OnDetach() { };

        /**
         * Receives an event and returns whether to propagate this event
         * to the layers below
         * */
        virtual bool OnEvent(const Events::Event& e) { return true; };

        virtual void OnUpdate(Timestep ts) { };

        virtual void OnImGuiRender() { };
        virtual void OnPostImGuiRender() { };

    public:
        inline const std::string& GetDebugName() const { return m_DebugName; } 

    private:
        std::string m_DebugName;
    };

} // namespace Almond