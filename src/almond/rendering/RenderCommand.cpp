#include "RenderCommand.h"
#include "almond/core/Logging.h"

#define IMPL_RENDER_COMMAND(CmdStructName)  \
    void _CMD_IMPL_##CmdStructName(const void* data); \
    const RenderCommandDispatch RenderCommands::CmdStructName::_StaticDispatch = _CMD_IMPL_##CmdStructName; \
    void _CMD_IMPL_##CmdStructName(const void* data)

namespace 
{

    template <typename T>
    inline const T* CastCmdData(const void* data)
    {
        return reinterpret_cast<const T*>(data);
    }
}

namespace Almond
{
    IMPL_RENDER_COMMAND(Draw)
    {
        auto cmdData = CastCmdData<RenderCommands::Draw>(data);
        AD_CORE_LOG_DEBUG(
            "[Cmd = Draw] "
            "StartVertex = {0}, "
            "VertexCount = {1}",
            cmdData->StartVertex,
            cmdData->VertexCount
        );
    }
}