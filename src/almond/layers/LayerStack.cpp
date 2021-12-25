#include "almond/layers/LayerStack.h"

namespace Almond
{
    LayerStack::LayerStack()
    {}

    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
    }

    void LayerStack::PushLayer(Layer* layer)
    {

        // TODO: Check if layer is already attached

        m_Layers.push_back(layer);
        layer->OnAttach();
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if(it != m_Layers.end())
        {
            m_Layers.erase(it);
        }

        layer->OnDetach();
    }

    void LayerStack::PopAllLayers()
    {
        while (m_Layers.size() > 0)
        {
            auto layer = m_Layers[m_Layers.size() - 1];
            m_Layers.pop_back();

            layer->OnDetach();
            delete layer;
        }

        m_Layers.clear();
    }

} // namespace Almond