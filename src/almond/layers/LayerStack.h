#pragma once

#include <vector>

#include "almond/core/base.h"
#include "almond/layers/Layer.h"

namespace Almond
{
    class LayerStack
    {
    public:
        void PushLayer(const Ref<Layer>& layer);
        void PopLayer(const Ref<Layer>& layer);

        inline std::vector<Ref<Layer>>::const_iterator begin() const
        {
            return m_Layers.begin();
        }
        inline std::vector<Ref<Layer>>::const_iterator end() const
        {
            return m_Layers.end();
        }

        inline std::vector<Ref<Layer>>::iterator begin()
        {
            return m_Layers.begin();
        }
        inline std::vector<Ref<Layer>>::iterator end()
        {
            return m_Layers.end();
        }

    private:
        std::vector<Ref<Layer>> m_Layers;
    };
} // namespace Almond