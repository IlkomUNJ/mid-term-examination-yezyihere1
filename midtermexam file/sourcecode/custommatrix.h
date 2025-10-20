#ifndef CUSTOMMATRIX_H
#define CUSTOMMATRIX_H

#include <iostream>
#include <cstring> 

using namespace std;

class CustomMatrix{
public:
    bool mat[3][3]={0};
    CustomMatrix(){

    }

    
    CustomMatrix(bool m[3][3]){
        memcpy(mat, m, sizeof(mat));
    }

    void fillMatrix(bool m[3][3]){
        memcpy(mat, m, sizeof(mat));
    }
};

#endif
