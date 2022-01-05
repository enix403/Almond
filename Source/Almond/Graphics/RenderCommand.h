#pragma once

#include <Almond/Core/Base.h>

namespace Almond
{
    typedef void (*RenderCommandDispatch)(const void* cmdData);
}

#define RENDER_CMD_STORAGE_HEADER() \
    static const RenderCommandDispatch _StaticDispatch

namespace Almond::RenderCommands
{
    /* =================================================================================== */
    /* ============================ Commands Data Definitions ============================ */
    /* =================================================================================== */

    // TODO: Resource Handles

    struct Draw
    {
        RENDER_CMD_STORAGE_HEADER();

        uint32_t StartVertex;
        uint32_t VertexCount;
    };

    /* ---------------------------- Cleanup ---------------------------- */

    #undef RENDER_CMD_STORAGE_HEADER
}

// Command Queues
namespace Almond
{
    class LinearMemoryAllocator
    {
    public:
        LinearMemoryAllocator(size_t maxSize)
        {
            m_MemoryBase = new char[maxSize];
            m_MemoryTop = m_MemoryBase;
            m_MemoryMax = m_MemoryBase + maxSize;
        }
        ~LinearMemoryAllocator()
        {
            delete[] m_MemoryBase;
        }

    public:
        template <typename T = void>
        T* Allocate(size_t size)
        {
            char* current = m_MemoryTop;
            m_MemoryTop += size;
            if (m_MemoryTop > m_MemoryMax)
            {
                m_MemoryTop = current;
                return nullptr;
            }
            return reinterpret_cast<T*>(current);
        }

        void Free(void* ptr) {}
        void Reset() { m_MemoryTop = m_MemoryBase; }

    private:
        char* m_MemoryBase;
        char* m_MemoryTop;
        char* m_MemoryMax;
    };


    typedef void* _RenderCmdPacketHeaderPtr; // Just for readability

    // A "packet" object is simply a pointer to its header
    //
    // Its memory layout is the header followed by its arbitrary-sized command data followed
    // by auxiliary memory
    typedef _RenderCmdPacketHeaderPtr _RenderCmdPacket;

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
        RenderCommandQueue(int maxCommands)
        :   m_Allocator(8 * 1024)
        {
            m_Keys = new Key_t[maxCommands];

            // NOLINTNEXTLINE(bugprone-sizeof-expression)
            m_Packets = new _RenderCmdPacket[maxCommands];
        }
        ~RenderCommandQueue()
        {
            delete[] m_Keys;
            delete[] m_Packets;
        }

    public:
        template <typename U>
        U* EnqueueCommand(Key_t key, size_t auxiliaryMemory = 0)
        {
            _RenderCmdPacket pack = AllocatePacketMemory<U>(auxiliaryMemory);
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

        template <typename U, typename P>
        U* AppendCommand(P* parentCommand, size_t auxiliaryMemory = 0)
        {
            _RenderCmdPacket pack = AllocatePacketMemory<U>(auxiliaryMemory);
            auto header = _RDQ_PACKET_HEADER(pack);
            header->NextPacket = nullptr;
            header->Dispatch = U::_StaticDispatch;

            auto parentHeader = _RDQ_CMD_HEADER(parentCommand);
            parentHeader->NextPacket = pack;

            return _RDQ_PACKET_CMD_DATA(U, pack);
        }

        inline void Clear()
        {
            m_Count = 0;
            m_Allocator.Reset();
        }

        template <typename U>
        static inline char* GetAuxiliaryMemory(U* command)
        {
            return reinterpret_cast<char*>(command) + sizeof(U);
        }

        void Submit()
        {
            for (int i = 0; i < m_Count; i++)
            {
                _RenderCmdPacket packet = m_Packets[i];
                do
                {
                    SubmitPacket(packet);
                    packet = _RDQ_PACKET_HEADER(packet)->NextPacket;
                } while(packet != nullptr);
            }
        }

    private:
        template <typename U>
        _RenderCmdPacket AllocatePacketMemory(size_t auxiliaryMemory = 0)
        {
            // TODO: Use a Linear Memory Allocator for fast allocations
            return reinterpret_cast<_RenderCmdPacket>(m_Allocator.Allocate(
                sizeof(_RenderCmdPacketHeader) + sizeof(U) + auxiliaryMemory));
        }

        static inline void SubmitPacket(_RenderCmdPacket pack)
        {
            auto header = _RDQ_PACKET_HEADER(pack);
            header->Dispatch(_RDQ_PACKET_CMD_DATA(void, pack));
        }

        /**
         * TODOs: 
         *      thread-safe command addition
         * */

    private:
        LinearMemoryAllocator m_Allocator;

        Key_t* m_Keys;
        _RenderCmdPacket* m_Packets;

        int m_Count = 0;
    };

    #undef _RDQ_PACKET_HEADER
    #undef _RDQ_CMD_HEADER
    #undef _RDQ_PACKET_CMD_DATA
}

