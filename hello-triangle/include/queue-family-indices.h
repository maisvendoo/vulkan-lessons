#ifndef     QUEUE_FAMILY_INDICES_H
#define     QUEUE_FAMILY_INDICES_H

#include    <optional>
#include    <cstdint>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;

    bool isComplete()
    {
        return graphicsFamily.has_value();
    }
};

#endif // QUEUE_FAMILY_INDICES_H
