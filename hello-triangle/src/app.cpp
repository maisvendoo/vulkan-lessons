#include    "app.h"

const   uint32_t    WIDTH = 1024;
const   uint32_t    HEIGHT = 768;

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
void HelloTriangleApplication::createInstance()
{
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


    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames  = glfwExtensions;

    createInfo.enabledLayerCount = 0;

    // Получаем список поддерживаемых расширений Vulkan
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> extensions(extensionCount);

    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

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
void HelloTriangleApplication::initVulkan()
{
    createInstance();
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
    glfwDestroyWindow(window);

    glfwTerminate();
}
