#include <coloredSphere.hpp>
#include <iostream>

int main()
{
    gil::RenderingWindow window {1600, 900, "Sorts Comparison"};
    if(!window.isReady())
    {
        std::cerr << "Window is not ready, something went wrong" << std::endl;
        return -1;
    }

    gil::InputTrigger exit;
    gil::InputTrigger sort;
    gil::InputTrigger shuffle;
    gil::InputControl xRotation;
    gil::InputControl yRotation;

    gil::EventHandler eventHandler;
    eventHandler.addKeyControl(gil::KEY_ESCAPE, exit, 1.0f);
    eventHandler.addKeyControl(gil::KEY_E, sort, 1.0f);
    eventHandler.addKeyControl(gil::KEY_R, shuffle, 1.0f);

    eventHandler.addKeyControl(gil::KEY_W, xRotation, -1.0f);
    eventHandler.addKeyControl(gil::KEY_S, xRotation,  1.0f);
    eventHandler.addKeyControl(gil::KEY_D, yRotation, -1.0f);
    eventHandler.addKeyControl(gil::KEY_A, yRotation,  1.0f);

    window.setEventHandler(eventHandler);

    glm::vec3 viewPos {0.0f, 0.0f, 3.0f};
    gil::Shader shader("coloredSphere");
    ColoredSphere ball(1.0f);

    shader.use();
    gil::setupDefaultLights(shader, viewPos);

    float xRotationAngle {0.0f};
    float yRotationAngle {0.0f};
    glm::vec3 rigidBodyPos { 0.0f, 0.0f, 0.0f };

    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    gil::Timer timer(true);
    while(window.isActive())
    {
        window.pollEvents();
        if(exit.isTriggered())
        {
            window.close();
        }
        if(sort.isTriggered())
        {
            ball.sortWithMergeSort(window, shader);
        }
        if(shuffle.isTriggered())
        {
            ball.shuffle(window, shader);
        }

        glClearColor(0.125f, 0.125f, 0.125f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        float deltaTime = timer.getDeltaTime();
        xRotationAngle += xRotation.getMagnitude() * deltaTime;
        yRotationAngle += yRotation.getMagnitude() * deltaTime;
        glm::mat4   model = glm::translate(glm::mat4(1.0f), rigidBodyPos);
                    model = glm::rotate(model, xRotationAngle, glm::vec3{1.0f, 0.0f, 0.0f});
                    model = glm::rotate(model, yRotationAngle, glm::vec3{0.0f, 1.0f, 0.0f});

        glm::mat4 view = glm::lookAt(viewPos, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f});
        glm::mat4 projection = glm::perspective(45.0f, window.getAspectRatio(), 0.1f, 100.0f);
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        ball.draw(shader);

        window.swapBuffers();
        timer.tick();
    }

    return 0;
}
