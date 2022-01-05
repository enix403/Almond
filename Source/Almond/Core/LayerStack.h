#pragma once

#include <vector>

#include <Almond/Core/Base.h>
#include <Almond/Core/Layer.h>

namespace Almond
{
    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

    public:
        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);

        void PopAllLayers();

        inline const std::vector<Layer*> LayersIter() const { return m_Layers; }

        inline std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
        inline std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }

        inline std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        inline std::vector<Layer*>::iterator end() { return m_Layers.end(); }


    private:
        std::vector<Layer*> m_Layers;
    };
} // namespace Almond