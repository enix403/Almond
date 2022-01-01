#pragma once

#include "almond/core/base.h"

namespace Almond
{
    typedef void (*RenderCommandDispatch)(const void* cmdData);

    struct _RenderCmdPacketHeader;

    // A "packet" object is simply a pointer to its header
    // It could be typedef'ed to just a void* but it is more
    // expressive to use a forward-declared header struct
    //
    // Its memory layout is the header followed by its arbitrary-sized command data
    typedef _RenderCmdPacketHeader* _RenderCmdPacket; 

    struct _RenderCmdPacketHeader
    {
        _RenderCmdPacket NextPacket;
        RenderCommandDispatch Dispatch;
    };


    #define _RDQ_PACKET_HEADER(packet) \
        reinterpret_cast<_RenderCmdPacketHeader*>(packet)

    #define _RDQ_CMD_HEADER(cmd) \
        _RDQ_PACKET_HEADER(reinterpret_cast<char*>(cmd) - sizeof(_RenderCmdPacketHeader))

    #define _RDQ_PACKET_CMD_DATA(CmdType, packet) \
        reinterpret_cast<CmdType*>(reinterpret_cast<char*>(packet) + sizeof(_RenderCmdPacketHeader))

    class RenderCommandQueue
    {
        typedef uint16_t Key_t;

    public:
        RenderCommandQueue(int maxCommands);
        ~RenderCommandQueue();

    private:
        template <typename U>
        static _RenderCmdPacket AllocatePacketMemory()
        {
            // TODO: Use a Linear Memory Allocator for fast allocations
            return reinterpret_cast<_RenderCmdPacket>(::operator new(
                sizeof(_RenderCmdPacketHeader) + sizeof(U)));
        }

        template <typename U>
        U* EnqueueCommand(Key_t key)
        {
            _RenderCmdPacket pack = AllocatePacketMemory<U>();
            auto header = _RDQ_PACKET_HEADER(pack);
            header->NextPacket = nullptr;
            header->Dispatch = U::_StaticDispatch;

            {
                // TODO: thread locking
                auto index = m_Count++;
                m_Keys[index] = key;
                m_Packets[index] = pack;
            }

            return _RDQ_PACKET_CMD_DATA(U, pack);
        }

        template <typename U, typename V>
        U* AppendCommand(V* parentCommand)
        {
            _RenderCmdPacket pack = AllocatePacketMemory<U>();
            auto header = _RDQ_PACKET_HEADER(pack);
            header->NextPacket = nullptr;
            header->Dispatch = U::_StaticDispatch;

            auto parentHeader = _RDQ_CMD_HEADER(parentCommand);
            parentHeader->NextPacket = pack;

            return _RDQ_PACKET_CMD_DATA(U, pack);
        }

        /**
         * TODOs: 
         *      submitting
         *      aux memory
         *      cmd memory linear allocation
         *      (later) thread-safe command addition
         * */

    private:
        Key_t* m_Keys;
        _RenderCmdPacket* m_Packets;

        int m_Count = 0;
    };

    #undef _RDQ_PACKET_HEADER
    #undef _RDQ_CMD_HEADER
    #undef _RDQ_PACKET_CMD_DATA
}


namespace Almond
{

    namespace RenderCommands
    {
        #define RENDER_CMD_STORAGE_HEADER() \
            private: \
            static const RenderCommandDispatch _StaticDispatch; \
            friend class RenderCommandQueue; \
            public:

        struct Draw
        {
            RENDER_CMD_STORAGE_HEADER()

            uint32_t StartVertex;
            uint32_t VertexCount;
        };

        #undef RENDER_CMD_STORAGE_HEADER
    }
}
