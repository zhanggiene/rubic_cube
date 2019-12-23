//
//  cube.cpp
//  rubic cube
//
//  Created by Zhang Zhuyan on 21/12/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//



#ifndef cube_h
#define cube_h

#include <glm.hpp>
#include "VertexBufferLayout.h"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <gtx/transform.hpp>
#include <gtc/quaternion.hpp>
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

const glm::mat4 originPosition = glm::translate(glm::mat4(1.0f),glm::vec3(1,1,-1));
const glm::mat4 NoriginPosition = glm::translate(glm::mat4(1.0f),glm::vec3(-1,-1,1));
class Cube
{
public:
    /*  Mesh Data  */
 vector<Vertex> vertices;// it contains color and vertices one color, one vertices.
unsigned int VAO;
glm::mat4 view;
glm::mat4 projection;
glm::mat4 translation;
glm::mat4 rotation;
    glm::quat orientation;
float angle=0.0001;
float degree=0.0f;

    
    /*  Functions  */
    // constructor
    Cube():translation(glm::mat4(1.0f)),projection(glm::perspective(glm::radians(45.0f),(float)2080/(float)1750,0.1f,100.0f)),view(glm::mat4(1.0f)),rotation(glm::mat4(1.0f)),orientation(glm::quat(1.0f,0,0,0))
    
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
            //cout<<"hi"<<endl;
        }
        
        
    }
    void setTranslation(int up,int right,int behind){ // this method cannot be done in a loop, only be done once.
        // it is set through experiment, y is up.
        glm::vec3 up_vector(glm::vec3(0.0f,1.0f*up,0.0f));
        glm::vec3 right_vector(glm::vec3(1.0f*right,0.0f,0.0f));
        glm::vec3 behind_vector(glm::vec3(0.0f,0.0f,-1.0f*behind));
        translation = glm::translate(glm::mat4(1.0f), up_vector+right_vector+behind_vector);
        //model=glm::translate(model, glm::vec3(4.0f, 0.1f, 0.0f));
       
        
    }
    
    void setVerticalRotation(int dir){
        
        //target is 1-8, 9-17
        /*https://math.stackexchange.com/questions/18382/quaternion-and-rotation-about-an-origin-and-an-arbitrary-axis-origin-help*/
         
        assert(dir==1 or dir==-1);
        glm::quat aroundX = glm::angleAxis(glm::radians(degree), glm::vec3(0, 0, -1*dir));
        //model=glm::rotate(model, angle, glm::vec3(0,0,1));
        //mat4 RotationMatrix = glm::quaternion::toMat4(quaternion);
        //glm::mat4 RotationMatrix = glm::toMat4(myQuat);
        rotation= originPosition*(glm::mat4_cast(aroundX))*(NoriginPosition);
        // order matters, quaternion can only rotate around its origin, so NoriginPosition bring you back to orign , then do rotation, then bring to previous position.
        degree+=0.1;
        
    }
    void setHorizontalRotation(int dir){
    //target is 678,15 16 17 24 25 26
        assert(dir==1 or dir==-1);
        glm::quat aroundV = glm::angleAxis(glm::radians(degree), glm::vec3(0, dir*1, 0));
        rotation= originPosition*(glm::mat4_cast(aroundV))*(NoriginPosition);
        //rotation= (glm::mat4_cast(aroundV));
        degree+=0.1;
    }
    void setSideRotation(int dir){
        assert(dir==1 or dir==-1);
        //target is 2 5 8 11 14 17 
        glm::quat aroundV = glm::angleAxis(glm::radians(degree), glm::vec3(-1*dir, 0, 0));
        rotation= originPosition*(glm::mat4_cast(aroundV))*(NoriginPosition);
        //rotation= (glm::mat4_cast(aroundV));
        degree+=0.1;
    }
    
    
    void setView(glm::vec3 temp){
        view = glm::lookAt(temp, glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0));
        
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
        cout<<"ith color is "<<i<<endl;
            
            for (int k=0;k<6;k++)
            {
                vertices[6*(i-1)+k].color=numberTocolor(i);
                
                
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
        VBO_obj.unbind();
    }
    
    void Draw(Shader* program)
    {
        program->setMatrix("model",rotation*translation);
        
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


#endif /* cube_h */

