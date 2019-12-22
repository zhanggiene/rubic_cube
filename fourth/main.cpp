//
//  main.cpp
//  first_meshing
//
//  Created by Zhang Zhuyan on 2/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//
#include <GL/glew.h>  // inlude this first, as it overlapps with SFML.
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
//#include <SFML/Graphics.hpp>  dont include SFML/GRAPHICS unless u are doing some SFML transformation

#include <glm.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include "shader.hpp"
#include "VertexBufferLayout.h"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include"Texture.hpp"

using namespace sf;
int main( int argc, char** argv )
{
    struct Material {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;
    };
    //Material material={glm::vec3(0.0215,0.1745,0.0215),glm::vec3(0.07568,0.61424,0.07568),glm::vec3(0.633,0.727811 ,0.633),0.6};    emerald
    Material material{glm::vec3(0.05375,0.05,0.06625),glm::vec3(0.18275,0.17,0.22525),glm::vec3(0.332741,0.328634,0.346435),0.3};
    
    
    float i=0.0f;
    float x=0.0f;
    sf::Clock clock;
    int widthScreen=2080;
    int heightScreen=1760;
    glm::vec3 lightPosition(0.0f,0.8f,0.2f);
    //renderwindows become window,
    sf::ContextSettings settings;
    settings.depthBits = 32;
    settings.stencilBits = 0;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 4;
    settings.minorVersion = 1; // it means 4.1
    Window window(sf::VideoMode(widthScreen,heightScreen),"OPENGL",sf::Style::Default, settings);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    window.setActive(); // active the windows for OpenGL rendering,
    //draw using OpenGL commands go here.
    
     glEnable(GL_DEPTH_TEST);    // GL depth test is disabled by default.
    
    
    glewInit(); //  rememebr to include this code to initialise glew.
    
    
    
    
    Shader program("VertexShader.txt","fragmentShader.txt");
    Shader lightProgram("VertexShader.txt","fragmentShaderLight.txt");
    
    float cube_vertices[] = {

            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    
    
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    
    
    VertexArray VAO=VertexArray();
    VertexBuffer VBO=VertexBuffer(cube_vertices,sizeof(cube_vertices));
    VertexBufferLayout vertex_position=VertexBufferLayout();
    vertex_position.push<float>(3);
    vertex_position.push<float>(3);
    VAO.combine(VBO, vertex_position);
    
    VAO.unbind();
    VBO.unbind();
    VertexArray lightVao=VertexArray();
    VBO.bind();
    lightVao.combine(VBO,vertex_position);
    lightVao.unbind();
    VBO.unbind();
    
    
    while (window.isOpen())
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clear color must be at the start of drawing.
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //******uniform data processing, so it will change every frame
        
        
        float radius = 10.0f;
        float cameraHeight=10.f;
        sf::Time elapsed1 = clock.getElapsedTime();
        float  sec  = elapsed1.asSeconds();
        float camX = sin(sec) * radius;
        float camZ = cos(sec) * radius;
        float y_axis=sin(sec)*cameraHeight;
        glm::vec3 cameraPosition(camX,y_axis,camZ);
        glm::mat4 view;
        view = glm::lookAt(cameraPosition, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        
        
        glm::mat4 projection=glm::mat4(1.0f);
        projection=glm::perspective(glm::radians(45.0f),(float)widthScreen/(float)heightScreen,0.1f,100.0f);
        
        
        
        
        glm::mat4 modelLight=glm::mat4(1.0f);
        x+=0.001;
        lightPosition=glm::vec3(sin(x),lightPosition.y,lightPosition.z);
        modelLight = glm::translate(modelLight,lightPosition);
        modelLight=glm::scale(modelLight, glm::vec3(0.2f));
        
    
        
        
        
        
        
        VAO.bind();
        program.use();
        program.setMatrix("view",view);
        program.setMatrix("projection",projection);
        program.setVec3f("cameraPosition",cameraPosition);
        program.setVec3f("lightColor",glm::vec3(1.0f));
        program.setVec3f("lightPos",lightPosition);
        program.setVec3f("material.ambient",material.ambient);
        program.setVec3f("material.diffuse",  material.diffuse);
        program.setVec3f("material.specular", material.specular);
        program.setFloat("material.shininess", material.shininess);
        
        
        
        
        // draw
        for (int i=0;i<10;i++){
        glm::mat4 model=glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
              program.setMatrix("model",model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
            

        VAO.unbind();
     VBO.unbind();
            
            
            lightVao.bind();
            lightProgram.use();
            lightProgram.setMatrix("view",view);
            lightProgram.setMatrix("projection",projection);
            lightProgram.setMatrix("model",modelLight);
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
            lightVao.unbind();
            
            // ****************misttake *************
            // must use the program, then can set the matris and stuff
            
            
            
            
            
            
    
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        
        window.display();            //sleep(seconds(5));
        
    }
    return 0;
    
}

