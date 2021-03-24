#ifndef     APP_H
#define     APP_H

#define     GLFW_INCLUDE_VULKAN
#include    <GLFW/glfw3.h>

#include    <iostream>
#include    <stdexcept>
#include    <cstdlib>
#include    <vector>

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


    void initWindow();

    void createInstance();

    void initVulkan();

    void mainLoop();

    void cleanup();
};

#endif // APP_H
