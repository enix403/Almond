#include "almond/layers/LayerStack.h"

namespace Almond
{
    void LayerStack::PushLayer(const Ref<Layer>& layer)
    {

        // TODO: Check if layer is already attached

        m_Layers.push_back(layer);
        layer->OnAttach();
    }

    void LayerStack::PopLayer(const Ref<Layer>& layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if(it != m_Layers.end())
        {
            m_Layers.erase(it);
        }

        layer->OnDetach();
    }
} // namespace Almond