#pragma once

#include "almond/events/Event.h"

namespace Almond
{

    class Layer
    {
    public:
        virtual ~Layer(){};

        // virtual void OnCreate()  = 0;
        // virtual void OnDestroy() = 0;
        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;

        /**
         * Receives an event and returns whether to propagate this event
         * to the layers below
         * */
        virtual bool OnEvent(const Events::Event& e) = 0;

        /**
         * Called every frame
         * */
        virtual void OnUpdate() = 0;
    };

} // namespace Almond