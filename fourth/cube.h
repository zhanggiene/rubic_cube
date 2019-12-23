//
//  cube.cpp
//  rubic cube
//
//  Created by Zhang Zhuyan on 21/12/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//



#include <glm.hpp>
#include "VertexBufferLayout.h"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 color;
};

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


class Cube
{
public:
    /*  Mesh Data  */
 vector<Vertex> vertices;// it contains color and vertices one color, one vertices.
unsigned int VAO;
glm::mat4 view;
glm::mat4 projection;
glm::mat4 model;

    
    /*  Functions  */
    // constructor
    Cube():model(glm::mat4(1.0f)),projection(glm::perspective(glm::radians(45.0f),(float)2080/(float)1750,0.1f,100.0f)),view(glm::mat4(1.0f))
    
    {
        for (int i=0;i<36*3;i+=3){
            Vertex vertex;
            glm::vec3 vector_position;
            vector_position.x=vertices_data[i];
            vector_position.y=vertices_data[i+1];
            vector_position.z=vertices_data[i+2];
            glm::vec3 vector_color;
            vector_color.x=1.0f;
            vector_color.y=1.0f;
            vector_color.z=1.0f;            // default color is white color;
            vertex.color=vector_color;
            vertex.Position=vector_position;
            vertices.push_back(vertex);
            cout<<"hi"<<endl;
        }
        
        
    }
    void setTranslation(int up,int right,int behind){ // this method cannot be done in a loop, only be done once.
        // it is set through experiment, y is up.
        model=glm::mat4(1.0f);
        glm::vec3 up_vector(glm::vec3(0.0f,1.0f*up,0.0f));
        glm::vec3 right_vector(glm::vec3(1.0f*right,0.0f,0.0f));
        glm::vec3 behind_vector(glm::vec3(0.0f,0.0f,-1.0f*behind));
        model = glm::translate(model, up_vector+right_vector+behind_vector);
        //model=glm::translate(model, glm::vec3(4.0f, 0.1f, 0.0f));
       
        
    }
    
    void setView(glm::vec3 temp){
        view = glm::lookAt(temp, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        
    }
    void setView(glm::mat4 temp)
    {   view=temp;
        
        
        
    }
    /*void setProjection()
    {
        projection=glm::perspective(glm::radians(45.0f),(float)2080/(float)1750,0.1f,100.0f);
       
        //cout<<"projection setup";
    }*/
    
    void setColor(vector<int>& colors) //array of number to be colored with color.
    {
        for(auto i:colors){
            //cout<<"ith color is "<<i<<endl;
            
            for (int k=0;k<6;k++)
            {
                vertices[6*(i-1)+k].color=numberTocolor(i);
                
                /*if(i==4)
                {
                    int j=6*(i-1)+k;
                cout<<"k is  "<<j<<endl;
                cout<<vertices[j].color.x<<" "<<vertices[j].color.y<<" "<<vertices[j].color.z<<endl;
                    
                }*/
               //cout<<" i "<<i<<endl;
                //cout<<"k is  "<<k<<endl;
                //out<<"vertice is "<<6*(i-1)+k<<endl;
                
                
            }
        }
        
    }
    
    void checkvertices()
    {
        for (int i=0;i<vertices.size();i++)
        {
            cout<<i<<"  ' position is  "<<vertices[i].Position.x<<" "<<vertices[i].Position.y<<" "<<vertices[i].Position.z<<"   "<<vertices[i].color.x<<" "<<vertices[i].color.y<<" "<<vertices[i].color.z<<endl;
            
            
        }
    }
    
    
    void setupMesh()
    {
        //std::cout<<"set up mesh now";
        
        VertexArray VAO_obj=VertexArray();
        VertexBuffer VBO_obj=VertexBuffer(&vertices[0],vertices.size()*sizeof(Vertex));
        VertexBufferLayout vertex_position=VertexBufferLayout();
        vertex_position.push<float>(3);
        vertex_position.push<float>(3);
        
        VAO_obj.combine(VBO_obj, vertex_position);
        VAO=VAO_obj.getID();// VAO is stored in public domain and it is important for drawing , so we need to pass it to public domain. it is the bug that i took very long to find.
        VAO_obj.unbind();
    }
    
    void Draw(Shader* program)
    {
        program->setMatrix("model",model);
        program->setMatrix("view",view);
        program->setMatrix("projection",projection);
        
        
       // cout<<"model"<<endl;
        
        
        program->use();
        
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        
        // always good practice to set everything back to defaults once configured.
       // glActiveTexture(GL_TEXTURE0);
    }
    
private:
    /*  Render data  */
    unsigned int VBO;
    
    /*  Functions    */
    // initializes all the buffer objects/arrays
    
    
    glm::vec3  numberTocolor(int num)
    
    {
        if (num==1) return glm::vec3(1.0f,0.0f,0.0f);//red
        else if(num==2) return glm::vec3(1.0f,1.0f,0.0f);//yellow
        else if(num==3) return glm::vec3(1.0f,0.5f,0.5f); //pink
        else if(num==4) { return glm::vec3(0.5f,0.0f,0.5f); }
        else if(num==5) return glm::vec3(0.0f,1.0f,0.0f);//green
        else if(num==6) return glm::vec3(0.0f,0.0f,1.0f);//blue
        return glm::vec3(1.0f,0.6f,1.0f);
    }
    
    
    
    
    
    
    
    
    
};

