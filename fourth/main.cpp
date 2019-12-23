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
#include "cube.h"
#include "rubicCube.h"

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
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    window.setActive(); // active the windows for OpenGL rendering,
    //draw using OpenGL commands go here.
    
     glEnable(GL_DEPTH_TEST);    // GL depth test is disabled by default.
    
    
    glewInit(); //  rememebr to include this code to initialise glew.
    
    
    
    
    Shader program("VertexShader.txt","fragmentShader.txt");// rmb to change the scheme home folder, root
    //******************root of many debuging ***********//
    
    RubicCube zhuyan=RubicCube();
    int number=0;
    while (window.isOpen())
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clear color must be at the start of drawing.
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Right)
                {
                    std::cout << "the -> key was pressed" << std::endl;
                    number++;
                    if (number>27) {number=0;}
                }
            }
            
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
        zhuyan.setView(glm::vec3(10.0f,10.0f,3.0f));
        zhuyan.rotate3();
        zhuyan.draw(&program,number);
        
        window.display();            //sleep(seconds(5));
        
    }
    return 0;
    
}

