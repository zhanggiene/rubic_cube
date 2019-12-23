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

using namespace sf;
int main( int argc, char** argv )
{
    
    float i=0.0f;
    float x=0.0f;
    sf::Clock clock;
    int widthScreen=2080;
    int heightScreen=1760;
    //renderwindows become window,
    sf::ContextSettings settings;
    settings.depthBits = 32;
    settings.stencilBits = 0;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 4;
    settings.minorVersion = 1; // it means 4.1
    Window window(sf::VideoMode(widthScreen,heightScreen),"OPENGL",sf::Style::Default, settings);
    glClearColor(1.0f,0.0f,0.0f,1.0f);
    window.setActive(); // active the windows for OpenGL rendering,
    //draw using OpenGL commands go here.
    
     glEnable(GL_DEPTH_TEST);    // GL depth test is disabled by default.
    
    
    glewInit(); //  rememebr to include this code to initialise glew.
    
    
    
    
    Shader program("VertexShader.txt","fragmentShader.txt");// rmb to change the scheme home folder, root
    //******************root of many debuging ***********//
    
    float vertices_data[] = {
        -0.5f, -0.5f, -0.5f,//0
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,// one face
        
        -0.5f, -0.5f,  0.5f,//6
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,//two face
        
        -0.5f,  0.5f,  0.5f,//12
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,//three face
        
        0.5f,  0.5f,  0.5f,//18
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,//four face
        
        -0.5f, -0.5f, -0.5f,//24
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,// five face
        
        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,// six face
    };
    
    
    
    VertexArray VAO=VertexArray();
    VertexBuffer VBO=VertexBuffer(vertices_data,sizeof(vertices_data));
    VertexBufferLayout vertex_position=VertexBufferLayout();
    vertex_position.push<float>(3);
    //vertex_position.push<float>(3);
    VAO.combine(VBO, vertex_position);
    
    VAO.unbind();
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
        
        
        VAO.bind();
        program.use();
        program.setMatrix("view",view);
        program.setMatrix("projection",projection);        
        // draw
       
        glm::mat4 model=glm::mat4(1.0f);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
              program.setMatrix("model",model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

        VAO.unbind();
     VBO.unbind();
            
            // ****************misttake *************
            // must use the program, then can set the matris and stuff
            
            
            
            
            
            
    
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        
        window.display();            //sleep(seconds(5));
        
    }
    return 0;
    
}

