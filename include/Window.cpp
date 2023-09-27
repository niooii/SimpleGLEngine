#include <iostream>
#include "Window.h"

void Window::create()
{
    create(800, 800, "Sample Window");
}

void Window::create(int w, int h, const char *n)
{
    width = w;
    height = h;
    name = n;

    SDL_Init(SDL_INIT_EVERYTHING);

    // FUCK MY LIFE

    //create a context of version 3.3 and use core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    //make it so the screen doesn't flicker on KDE
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");

    uint32_t WindowFlags = SDL_WINDOW_OPENGL;
    window = SDL_CreateWindow("OpenGL Test", 0, 0, w, h, WindowFlags);
    context = SDL_GL_CreateContext(window);

    GLenum e;
    if((e = glewInit()) != GLEW_OK)
    {
        std::cout << "error dumbass " << glewGetErrorString(glewInit()) << '\n';
        exit(-1);
    }

    //initialize z-depth buffering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //antialiasing
    glEnable(GL_MULTISAMPLE);

    //glViewport(0, 0, w, h);
}

void Window::close()
{
//    glDeleteProgram(solidProgram);
//    glDeleteProgram(wireframeProgram);
    running = false;
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Window::shouldRun()
{
    return running;
}

void Window::clear()
{
    clear(0.0f, 0.0f, 0.0f, 1.0f);
}

void Window::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    //clear the color and the depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::renderPresent()
{
    //std::cout << glewGetErrorString(glGetError()) << '\n';
    SDL_GL_SwapWindow(window);
}

void Window::setActiveCamera(Camera* c)
{
    mainCamera = c;
}


void Window::pollEvents()
{
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_QUIT:
                close();
                break;

            case SDL_MOUSEMOTION:
                if(OnMouseMotion == nullptr)
                    continue;
                OnMouseMotion(
                        e.motion.x,
                        e.motion.y,
                        e.motion.xrel,
                        e.motion.yrel
                        );
                break;

            case SDL_MOUSEBUTTONDOWN:
                if(OnMouseButtonDown == nullptr)
                    continue;
                OnMouseButtonDown(
                        e.button.x,
                        e.button.y,
                        e.button.button
                        );
                break;

            case SDL_MOUSEBUTTONUP:
                if(OnMouseButtonUp == nullptr)
                    continue;
                OnMouseButtonUp(
                        e.button.x,
                        e.button.y,
                        e.button.button
                        );
                break;

            case SDL_KEYDOWN:
                if(OnKeyDown == nullptr)
                    continue;
                OnKeyDown(
                        e.key.keysym.sym,
                        e.key.keysym.mod
                        );
                break;

            case SDL_KEYUP:
                if(OnKeyUp == nullptr)
                    continue;
                OnKeyUp(
                        e.key.keysym.sym,
                        e.key.keysym.mod
                        );
        }
    }
}

void Window::SetMouseMotionCallback(void (*callback)(int, int, int, int))
{
    OnMouseMotion = callback;
}

void Window::SetMouseButtonDownCallback(void (*callback)(int, int, Uint8))
{
    OnMouseButtonDown = callback;
}

void Window::SetMouseButtonUpCallback(void (*callback)(int, int, Uint8))
{
    OnMouseButtonUp = callback;
}

void Window::SetKeyDownCallback(void (*callback)(SDL_Keycode key, Uint16 modifier)) {
    OnKeyDown = callback;
}

void Window::SetKeyUpCallback(void (*callback)(SDL_Keycode key, Uint16 modifier)) {
    OnKeyUp = callback;
}

