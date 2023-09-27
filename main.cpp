#include <iostream>
#include <filesystem>
#include "Utils/Timer.h"
#include "Shader.h"
#include <Window.h>
#include <glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


void onmousedown(int x, int y, Uint8 button)
{
    std::cout << "CLICKED AT " << x << ", " << y << '\n';
}

void onkeypress(SDL_Keycode key, Uint16 modifier)
{
    std::cout << key << "presssed yes \n";
}

int main() {
    Timer execTimer{};
    execTimer.reset();

    Window w{};

    w.create();
    w.SetKeyDownCallback(onkeypress);
    w.SetMouseButtonDownCallback(onmousedown);
    //std::cout << std::filesystem::relative("/home/niooi/Projects/CLionProjects/GLGameEngine/include/DefaultShaders/Default.vert").relative_path();
    Shader test{"../include/DefaultShaders/Default.vert", "../include/DefaultShaders/Default.frag"};
    glm::mat4 m = glm::identity<glm::mat4>();
    glm::mat4 v = glm::identity<glm::mat4>();
    while(w.shouldRun())
    {
        w.pollEvents();
        w.clear(100,100,100,100);

        test.activate();

        test.setUniformMat4("modelMat", m);
        test.setUniformMat4("viewMat", v);
        glm::vec3 axis{0, 0, 1};
        v = glm::rotate(v, 0.1f, axis);
        test.setUniformMat4("projMat", m);

        glColor3b(8, 8, 2);
        glBegin(GL_TRIANGLES);
        glVertex3d(0.5, 0.5, 0);
        glVertex3d(0.5, 1, 0);
        glVertex3d(-0.5, 1, 0);
        glEnd();


        w.renderPresent();
    }

    w.close();

    std::cout << "Execution finished in " << execTimer.elapsed() << " seconds." << '\n';
    return 0;
}
