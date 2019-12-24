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
#define CLOCKWISE 1
#define ANTICLOCKWISE -1







vector<vector<int>> faces{
    {3,2,5},{2,5},{2,4,5},
    { 2,3},{2},{2,4},
    { 6,3,2},{2,6},{2,4,6},
    
    { 3, 5 },{5},{4,5},
    { 3 },{},{ 4 },
    { 3,6 },{6},{4,6},
    
    {3, 1, 5 },{1,5},{1,4,5},
    { 3, 1},{1},{ 1, 4},
    { 1,3,6 },{6,1},{1,4,6},
};


class RubicCube
{
public:
    int cubeMove[3][3][3];
    
    bool isRotating;// only start rotating when it is not rotating. 
    Cube cubes[27];
    RubicCube()
    {   int index=0;
        isRotating=false;
        for (int i=0;i<27;i++)
        {
            cubes[i].setColor(faces[i]);

            cubes[i].setupMesh();// set color first, then setup mesh
            //cubes[i].setTranslation(0,i,0);
            cubes[i].setTranslation((int)(i%9)/3,(i%9)%3,(int)i/9);
            cubes[i].checkvertices();
        }
        //[plane][row][column]
        for (int i=0;i<3;i++)
        {
            for (int j=0;j<3;j++)
            {
                for (int k=0;k<3;k++)
                {
                    cubeMove[i][j][k]=index;
                    index++;
                }}}
        this->print();
        
          }
    
    
    void print(){
        for (int i=2;i>=0;i--)
        {
            for (int j=2;j>=0;j--)
            {
                for (int k=0;k<3;k++)
                {
                    cout<<cubeMove[i][j][k]<<" ";
                }
                cout<<endl;
            }
            cout<<"_________"<<endl;
            
        }
    }
        
        
    void resetFaces()
    {
        
        for (int i=0;i<3;i++)
        {
            for (int j=0;j<3;j++)
            {
                for (int k=0;k<3;k++)
                {
                    cubes[cubeMove[i][j][k]].changeVertex(faces[i*9+j*3+k]);
                    //cubes[i*9+j*3+k].changeVertex(faces[cubeMove[i][j][k]]); wrong approach
                   cout<<"changing cube"<<i*9+j*3+k<<"to "<<cubeMove[i][j][k]<<endl;
                    //cubes[i*9+j*3+k].changeVertex();
                    
                }}}
        
        
    
    }
    void setView(glm::vec3 position)
    {
       
        for (int i=0;i<27;i++)
        {
               cubes[i].setView(position);
        }
        
        
    }
    
    void rotate(int planeNumber,int dir)
    {
       
        planarRotate(planeNumber,dir);
        for (int i=0;i<3;i++)
        {
            for (int k=0;k<3;k++)
                
                cubes[cubeMove[planeNumber][i][k]].rotatePlanar(dir);
        }
        
        print();
        
    }
    void planarRotate(int n,int dir)
    {
        vector<int> temp;
        temp.push_back(cubeMove[n][0][0]);
        temp.push_back(cubeMove[n][0][1]);
        temp.push_back(cubeMove[n][0][2]);
        temp.push_back(cubeMove[n][1][2]);
        temp.push_back(cubeMove[n][2][2]);
        temp.push_back(cubeMove[n][2][1]);
        temp.push_back(cubeMove[n][2][0]);
        temp.push_back(cubeMove[n][1][0]);
        
        if (dir== ANTICLOCKWISE)
        {
            cubeMove[n][0][0]=temp[6];
            cubeMove[n][0][1]=temp[7];
            cubeMove[n][0][2]=temp[0];
            cubeMove[n][1][2]=temp[1];
            cubeMove[n][2][2]=temp[2];
            cubeMove[n][2][1]=temp[3];
            cubeMove[n][2][0]=temp[4];
            cubeMove[n][1][0]=temp[5];
        }
        else if(dir== CLOCKWISE)
        {
            cubeMove[n][0][0]=temp[2];
            cubeMove[n][0][1]=temp[3];
            cubeMove[n][0][2]=temp[4];
            cubeMove[n][1][2]=temp[5];
            cubeMove[n][2][2]=temp[6];
            cubeMove[n][2][1]=temp[7];
            cubeMove[n][2][0]=temp[0];
            cubeMove[n][1][0]=temp[1];
            
            
            
        }
        else
            assert("something is wrong");
        
        
        
    }
    
    void HRotate(int n,int dir)
    {
        vector<int> temp;
        temp.push_back(cubeMove[0][n][0]);
        temp.push_back(cubeMove[0][n][1]);
        temp.push_back(cubeMove[0][n][2]);
        temp.push_back(cubeMove[1][n][2]);
        temp.push_back(cubeMove[2][n][2]);
        temp.push_back(cubeMove[2][n][1]);
        temp.push_back(cubeMove[2][n][0]);
        temp.push_back(cubeMove[1][n][0]);
        
        if (dir== ANTICLOCKWISE)
        {
            cubeMove[0][n][0]=temp[6];
            cubeMove[0][n][1]=temp[7];
            cubeMove[0][n][2]=temp[0];
            cubeMove[1][n][2]=temp[1];
            cubeMove[2][n][2]=temp[2];
            cubeMove[2][n][1]=temp[3];
            cubeMove[2][n][0]=temp[4];
            cubeMove[1][n][0]=temp[5];
        }
        else if (dir==CLOCKWISE)
        {
            cubeMove[0][n][0]=temp[2];
            cubeMove[0][n][1]=temp[3];
            cubeMove[0][n][2]=temp[4];
            cubeMove[1][n][2]=temp[5];
            cubeMove[2][n][2]=temp[6];
            cubeMove[2][n][1]=temp[7];
            cubeMove[2][n][0]=temp[0];
            cubeMove[1][n][0]=temp[1];
            
            
            
        }
        else
            assert("something is wrong");
        
        
        
    }
    
    void SRotate(int n,int dir)
    {
        vector<int> temp;
        temp.push_back(cubeMove[0][0][n]);
        temp.push_back(cubeMove[0][1][n]);
        temp.push_back(cubeMove[0][2][n]);
        temp.push_back(cubeMove[1][2][n]);
        temp.push_back(cubeMove[2][2][n]);
        temp.push_back(cubeMove[2][1][n]);
        temp.push_back(cubeMove[2][0][n]);
        temp.push_back(cubeMove[1][0][n]);
        
        if (dir== CLOCKWISE)
        {
            cubeMove[0][0][n]=temp[6];
            cubeMove[0][1][n]=temp[7];
            cubeMove[0][2][n]=temp[0];
            cubeMove[1][2][n]=temp[1];
            cubeMove[2][2][n]=temp[2];
            cubeMove[2][1][n]=temp[3];
            cubeMove[2][0][n]=temp[4];
            cubeMove[1][0][n]=temp[5];
        }
        else if (dir== ANTICLOCKWISE)
        {
            cubeMove[0][0][n]=temp[2];
            cubeMove[0][1][n]=temp[3];
            cubeMove[0][2][n]=temp[4];
            cubeMove[1][2][n]=temp[5];
            cubeMove[2][2][n]=temp[6];
            cubeMove[2][1][n]=temp[7];
            cubeMove[2][0][n]=temp[0];
            cubeMove[1][0][n]=temp[1];

        }
        
        else
            assert("something is wrong");
        
        
        
    }
    
    
    
    
    
    void rotate2(int planeNumber,int dir)
    {
        HRotate(planeNumber,dir);
        for (int i=0;i<3;i++)
        {
            for (int k=0;k<3;k++)
            
            cubes[cubeMove[i][planeNumber][k]].rotateHorizontal(dir);
        }
        
        print();
    }
    
    void rotate3(int planeNumber,int dir)
    {
         SRotate(planeNumber,dir);
        for (int i=0;i<3;i++)
        {
            for (int k=0;k<3;k++)
                
                cubes[cubeMove[i][k][planeNumber]].rotateSide(dir);
        }
       
        print();
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
