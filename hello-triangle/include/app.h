#ifndef     APP_H
#define     APP_H

#define     GLFW_INCLUDE_VULKAN
#include    <GLFW/glfw3.h>

#include    <iostream>
#include    <stdexcept>
#include    <cstdlib>
#include    <vector>
#include    <cstring>
#include    <set>

#include    "queue-family-indices.h"
#include    "swap-chain-support.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class HelloTriangleApplication
{
public:

    HelloTriangleApplication();

    ~HelloTriangleApplication();

    void run();

private:

    // Указатель на экземпляр окна
    GLFWwindow  *window;

    VkInstance  instance;

    VkDebugUtilsMessengerEXT debugMessager;

    VkPhysicalDevice    physicalDevice;

    VkDevice            device;

    VkPhysicalDeviceFeatures deviceFeatures;

    VkQueue graphicsQueue;

    VkSurfaceKHR    surface;

    VkQueue presentQueue;

    void initWindow();

    bool checkValidationLayerSupport();

    std::vector<const char *> getRequiredExtentions();

    void createInstance();

    void populateDebugMessegerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

    void setupDebugMessager();

    void createSurface();

    // Выбор физического устройства вывода (видеокарты)
    void pickPhysicalDevice();

    // Проверка физического устройства на соответствие нашим требованиям
    bool isDeviceSuitable(VkPhysicalDevice device);

    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    // Определение доступных семейств очередей Vulkan
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    // Создание логического устройства
    void createLogicalDevice();

    void initVulkan();

    void mainLoop();

    void cleanup();

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
            );
};

#endif // APP_H
