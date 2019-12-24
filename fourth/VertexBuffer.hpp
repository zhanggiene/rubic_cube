//
//  VertexBuffer.hpp
//  second
//
//  Created by Zhang Zhuyan on 21/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp

#include <stdio.h>
class VertexBuffer
{
public:
    VertexBuffer(const void* data,const unsigned size);
    void bind() const ;
    void unbind() const ;
    void passID(unsigned int* ID);
private:
    unsigned int mBufferID;
    
    
    
    
    
    
};





#endif /* VertexBuffer_hpp */
