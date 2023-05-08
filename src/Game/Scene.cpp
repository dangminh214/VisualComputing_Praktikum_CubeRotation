#include "Scene.h"
#include <AssetManager.h>

Scene::Scene(OpenGLWindow * window) :
        m_window(window)
{
    assert(window != nullptr);
}

Scene::~Scene()
{

}
bool Scene::init()
{
    try
    {
        //Load shader
        m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"));
        m_shader = m_assets.getShaderProgram("shader");
        m_shader->use();
        static const float vertices[] =  {0.5, -0.5, -0.5, 1, 0, 0,
                                          0.5, -0.5, 0.5, 0, 1, 0,
                                          -0.5, -0.5, 0.5, 0, 0, 1,
                                          -0.5, -0.5, -0.5, 1, 1, 0,
                                          0.5, 0.5, -0.5, 1, 0, 1,
                                          0.5, 0.5, 0.5, 0, 1, 1,
                                          -0.5, 0.5, 0.5, 1, 1, 1,
                                          -0.5, 0.5, -0.5, 0.5, 1, 0.5};

        static const int indices[] = {1, 2, 3,
                                      7, 6, 5,
                                      4, 5, 1,
                                      5, 6, 2,
                                      2, 6, 7,
                                      0, 3, 7,
                                      0, 1, 3,
                                      4, 7, 5,
                                      0, 4, 1,
                                      1, 5, 2,
                                      3, 2, 7,
                                      4, 0, 7};


        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        glVertexAttribPointer(0,3,GL_FLOAT, false, 6*sizeof(float),(void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 6*sizeof(float), (void*)(3*sizeof(float)));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &iboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindVertexArray(0); // unbind VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind IBO


       //Praktikum1 Aufgabe 4
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        std::cout << "Scene initialization done\n";
        return true;
    }
    catch (std::exception& ex)
    {
        throw std::logic_error("Scene initialization fa, it uses count sequential elements from each enabled array to construct a sequence of geometric primitives, beginning with element first. mode specifies what kind of primitives are constructed and how the array elements construct those primitives.     iled:\n" + std::string(ex.what()) + "\n");
    }
}

void Scene::render(float dt)
{
    //static float time = 0.0f;
    Transform* cubeTransform = new Transform();

    float rotationAngleX = glm::radians(45.0f);
    float rotationAngleY = glm::radians(45.0f);
    float rotationAngleZ = glm::radians(45.0f);

    cubeTransform->rotate(glm::vec3(rotationAngleX, rotationAngleY, rotationAngleZ));

    m_shader->setUniform("transformMatrix", cubeTransform->getMatrix(), false);

    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0); // unbind VAO
}
void Scene::update(float dt)
{

}

OpenGLWindow * Scene::getWindow()
{
    return m_window;
}

void Scene::onKey(Key key, Action action, Modifier modifier)
{

}

void Scene::onMouseMove(MousePosition mouseposition)
{

}

void Scene::onMouseButton(MouseButton button, Action action, Modifier modifier)
{

}

void Scene::onMouseScroll(double xscroll, double yscroll)
{

}

void Scene::onFrameBufferResize(int width, int height)
{

}
void Scene::shutdown()
{
    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(1, &vboID);
}


