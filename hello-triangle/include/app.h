#ifndef     APP_H
#define     APP_H

#define     GLFW_INCLUDE_VULKAN
#include    <GLFW/glfw3.h>

#include    <iostream>
#include    <stdexcept>
#include    <cstdlib>
#include    <vector>
#include    <cstring>

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

    void initWindow();

    bool checkValidationLayerSupport();

    std::vector<const char *> getRequiredExtentions();

    void createInstance();

    void populateDebugMessegerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

    void setupDebugMessager();

    // Выбор физического устройства вывода (видеокарты)
    void pickPhysicalDevice();

    // Проверка физического устройства на соответствие нашим требованиям
    bool isDeviceSuitable(VkPhysicalDevice device);

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
