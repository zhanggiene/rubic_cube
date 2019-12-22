//
//  VertexArray.cpp
//  third
//
//  Created by Zhang Zhuyan on 22/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#include "VertexArray.hpp"

int VertexArray::index;
VertexArray::VertexArray(){
    
    glGenVertexArrays(1,&vaID);
    //index=0;
}
void VertexArray::bind(){
    glBindVertexArray(vaID);
    
}
void VertexArray::unbind(){
    glBindVertexArray(0);
    
}

void VertexArray::combine(const VertexBuffer& vb,const VertexBufferLayout& layout){
    bind();
    vb.bind();
    const auto& elements=layout.getElements();
    unsigned int offset=0;
    
    for (unsigned int i=0;i<elements.size();i++)
    {
        const auto& element=elements[i];
        
        glEnableVertexAttribArray(i);
        std::cout<<"glenablevertexattribarray("<<i<<")"<<","<<element.count<<","<<element.type<<","<<element.normalized<<","<<layout.getStride()<<","<<offset<<std::endl;
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(),(const void*)offset);
        offset+=element.count*4;
        
    }
    

    
}
unsigned int VertexArray::getID(){
    return vaID;
    
}
