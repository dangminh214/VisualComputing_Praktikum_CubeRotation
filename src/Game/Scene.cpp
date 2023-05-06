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
        float vertices[] = {
                //M
                -0.9, -0.1, 1.0, 0.5, 0.6,
                -0.8, -0.1, 1.0, 0.5, 0.6,
                -0.6, -0.1, 1.0, 0.5, 0.6,
                -0.5, -0.1, 1.0, 0.5, 0.6,
                -0.8, 0.1, 1.0, 0.5, 0.6,
                -0.7, 0.0, 1.0, 0.5, 0.6,
                -0.6, 0.1, 1.0, 0.5, 0.6,

                -0.9, 0.2, 1.0, 0.5, 0.6,
                -0.8, 0.2, 1.0, 0.5, 0.6,
                -0.7, 0.1, 1.0, 0.5, 0.6,
                -0.6, 0.2, 1.0, 0.5, 0.6,
                -0.5, 0.2, 1.0, 0.5, 0.6,

                //I
                -0.4, -0.1, 1.0, 0.5, 0.6,
                -0.3, -0.1, 1.0, 0.5, 0.6,
                -0.4, 0.2,1.0, 0.5, 0.6,
                -0.3, 0.2, 1.0, 0.5, 0.6,

                //N
                -0.2, -0.1, 1.0, 0.5, 0.6,
                -0.1, -0.1,1.0, 0.5, 0.6,
                0.1, -0.1,1.0, 0.5, 0.6,
                0.2, -0.1, 1.0, 0.5, 0.6,
                -0.2, 0.2, 1.0, 0.5, 0.6,
                -0.1, 0.2, 1.0, 0.5, 0.6,
                0.1, 0.2, 1.0, 0.5, 0.6,
                0.2, 0.2, 1.0, 0.5, 0.6,
                -0.1, 0.1, 1.0, 0.5, 0.6,
                0.1, 0.0, 1.0, 0.5, 0.6,

                //H
                0.3, -0.1, 1.0, 0.5, 0.6,
                0.4, -0.1, 1.0, 0.5, 0.6,
                0.3, 0.2, 1.0, 0.5, 0.6,
                0.4, 0.2, 1.0, 0.5, 0.6,
                0.4, 0.1, 1.0, 0.5, 0.6,
                0.4, 0.0, 1.0, 0.5, 0.6,
                0.5, 0.0, 1.0, 0.5, 0.6,
                0.5, 0.1, 1.0, 0.5, 0.6,
                0.5, 0.2, 1.0, 0.5, 0.6,
                0.6, 0.2, 1.0, 0.5, 0.6,
                0.6, -0.1, 1.0, 0.5, 0.6,
                0.5, -0.1, 1.0, 0.5, 0.6,


        };
        unsigned int indices[] = {
                //M
                0,1,7,
                7,1,4,
                7,9,8,
                7,5,9,
                9,5,10,
                10,5,6,
                2,3,10,
                10,3,11,

                //I
                12, 13, 14,
                14, 13, 15,

                //N
                16, 17,20,
                20,17,21,
                21,24,18,
                21,18,25,
                18,19,22,
                22,19,23,

                //H
                26, 27,28,
                28, 27, 29,
                30,31,32,
                30,32,33,
                37,36,34,
                34,36,35

        };
        //set up VBO
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);
        //Vertex Attribute definieren, aktivieren
        glVertexAttribPointer(0,2,GL_FLOAT, false, 5*sizeof(float),(void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 5*sizeof(float), (void*)(2*sizeof(float)));
        //pointer 2*sizeof(float): after x,y then come r,g,b -> each x or y contains of (sizeofByte) ->r,g,b come after 2*(sizeofFloat) Byte
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        //set up IBO
        glGenBuffers(1, &iboID);
        //Binden des IBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        //Füllen des IBO mit Index Daten
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindVertexArray(0); // unbind VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind IBO


        //My code end here
        std::cout << "Scene initialization done\n";
       //Aufgabe 4
        //glEnable(GL_CULL_FACE);
        //glFrontFace(GL_CCW);
        //glCullFace(GL_BACK);
        return true;
    }
    catch (std::exception& ex)
    {
        throw std::logic_error("Scene initialization fa, it uses count sequential elements from each enabled array to construct a sequence of geometric primitives, beginning with element first. mode specifies what kind of primitives are constructed and how the array elements construct those primitives.     iled:\n" + std::string(ex.what()) + "\n");
    }
}

void Scene::render(float dt)
{
    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, 66,GL_UNSIGNED_INT, 0);

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


