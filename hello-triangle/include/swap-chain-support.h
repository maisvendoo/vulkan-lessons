#ifndef     SWAP_CHAIN_SUPPORT_H
#define     SWAP_CHAIN_SUPPORT_H

#include    <vector>
#include    <vulkan/vulkan.h>

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR        capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR>   presentModes;
};

#endif // SWAP_CHAIN_SUPPORT_H
