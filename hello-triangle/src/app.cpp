#include    "app.h"

const   uint32_t    WIDTH = 1024;
const   uint32_t    HEIGHT = 768;

const   std::vector<const char *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef  NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
HelloTriangleApplication::HelloTriangleApplication()
    : window(nullptr)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
HelloTriangleApplication::~HelloTriangleApplication()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void HelloTriangleApplication::run()
{
    initWindow();

    initVulkan();

    mainLoop();

    cleanup();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void HelloTriangleApplication::initWindow()
{
    // Инициализируем GLFW
    glfwInit();

    // Указываем GLFW что НЕ НАДО создавать контекст OpenGL
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // Отключаем изменяемый размер окна (рано еще, маленькие еще!)
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Создаем окно
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool HelloTriangleApplication::checkValidationLayerSupport()
{
    uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char *layerName : validationLayers)
    {
        bool layerFound = false;

        for (const auto &layerProperties : availableLayers)
        {
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
        {
            return false;
        }
    }

    return true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::vector<const char *> HelloTriangleApplication::getRequiredExtentions()
{
    uint32_t glfwExtentionsCount = 0;
    const char **glfwExtentions;
    glfwExtentions = glfwGetRequiredInstanceExtensions(&glfwExtentionsCount);

    std::vector<const char *> extentions(glfwExtentions, glfwExtentions + glfwExtentionsCount);

    if (enableValidationLayers)
    {
        extentions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extentions;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void HelloTriangleApplication::createInstance()
{
    if (enableValidationLayers && !checkValidationLayerSupport())
    {
        throw std::runtime_error("Validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Формируем список расширений оконной системы GLFW, запрашиваемый у Vulkan
    auto glfwExtensions = getRequiredExtentions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(glfwExtensions.size());
    createInfo.ppEnabledExtensionNames  = glfwExtensions.data();

    // Добавляем слои валидации, если включена соответствующая опция (только в отладке!)
    if (enableValidationLayers)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else
    {
        createInfo.enabledLayerCount = 0;
    }

    // Получаем список поддерживаемых расширений Vulkan
    uint32_t extensionCount = 0;

    // Предварительный запрос списка расширений Vulkan
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    // Получаем список доступных расширений
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    // Выводим в консоль список расширений
    std::cout << "Available extensions:" << std::endl;

    for (const auto &extension : extensions)
    {
        std::cout << '\t' << extension.extensionName << std::endl;
    }

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create instance!");
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void HelloTriangleApplication::setupDebugMessager()
{
    if (!enableValidationLayers)
        return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

    createInfo.pfnUserCallback = debugCallback;
    createInfo.pUserData = nullptr;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void HelloTriangleApplication::initVulkan()
{
    createInstance();
    setupDebugMessager();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void HelloTriangleApplication::mainLoop()
{
    // Цикл обработки сообщений окна
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void HelloTriangleApplication::cleanup()
{
    vkDestroyInstance(instance, nullptr);

    glfwDestroyWindow(window);

    glfwTerminate();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
VkBool32 HelloTriangleApplication::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                 VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                 const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                 void *pUserData)
{
    std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}


