//
//  rubicCube.h
//  rubic cube2
//
//  Created by Zhang Zhuyan on 23/12/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef rubicCube_h
#define rubicCube_h

#include"cube.h"

vector<vector<int>> faces{
    {3},{3},{3},
    { 4 },{5},{ 6 },
    { 1,2},{1,3},{},
    
    { 3, 5 },{5},{4,5},
    { 3 },{},{ 4 },
    { 3,6 },{6},{4,6},
    
    {2, 4, 5 },{2,5},{2,3,5},
    { 2, 4 },{2},{ 2, 3 },
    { 2,4,6 },{2,6},{2,3,6},
};


class RubicCube
{
public:
    Cube cubes[27];
    RubicCube()
    {
        for (int i=0;i<27;i++)
        {
            cubes[i].setColor(faces[i]);

            cubes[i].setupMesh();// set color first, then setup mesh
            //cubes[i].setTranslation(0,i,0);
            cubes[i].setTranslation((int)(i%9)/3,(i%9)%3,(int)i/9);
            
        }
    }
    
    
    
    void setView(glm::vec3 position)
    {
       
        for (int i=0;i<27;i++)
        {
               cubes[i].setView(position);
        }
        
        
    }
    
    
    void draw(Shader* program )
    {
        for (int i=0;i<27;i++)
        {
            cubes[i].Draw(program);
        }
        
    }
    
    void draw(Shader* program,int number )
    {
        for (int i=0;i<number;i++)
        {
            cubes[i].Draw(program);
        }
        
    }
    
    
    
    
    
    
    
    
};
#endif /* rubicCube_h */
