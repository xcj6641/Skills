#include <stdlib.h>
#include <iostream>
#include <format>

void* allocateSpace(size_t totalBytes){
    return malloc(totalBytes);
}

void freeSpace(void* head ){
    free(head);
}

constexpr int BLOCK_HEAD_SIZE_BYTE = sizeof(size_t);

template<typename T>
T* UserNewArray(size_t elem_num){
    void* p = allocateSpace(sizeof(T)*elem_num + BLOCK_HEAD_SIZE_BYTE);

    if(!p) throw std::bad_alloc();

    *((size_t*)p) = elem_num;
    //void* cannot directly do pointer arithmetic 
    void * block = (void*)((size_t)p + BLOCK_HEAD_SIZE_BYTE);
    for(int i = 0; i < elem_num; ++i){
        new(block) T();
        block = (void*)((size_t)block+sizeof(T));
    }
    return (T*)((size_t)p + BLOCK_HEAD_SIZE_BYTE);
}

template<typename T>
void UserDeleteArray(T* p){
    if(!p) return;
    
    void* head = (void*) ((size_t)p - BLOCK_HEAD_SIZE_BYTE);
    int cnt = *((size_t*)head);
    std::cout<<"To delete:"<<cnt<<std::endl;
    if(cnt > 0){
        for(int i = 0; i < cnt; ++i){
            p[i].~T();
            // ((T*)p)->~T();
            // p+=1;
        }
    }
    freeSpace(head);
}


class Visual{
    int idx;
    int x;
    int y;
    int z;
public:
    Visual(){}
    Visual(int inIdx, int inX, int inY, int inZ):idx(inIdx),x(inX),y(inY),z(inZ){}
    void SetPosition(int inIdx, int inX, int inY, int inZ){
        idx = inIdx;
        x = inX;
        y = inY;
        z = inZ;
    }
    void print(){
        std::string s = std::format("This is Visual{} with x={}, y={}, z={}", idx, x,y,z);
        std::cout<<s<<std::endl;
    }
    ~Visual(){
        std::string s = std::format("Visual{}(x={}, y={}, z={}) is deleted", idx,x,y,z);
        std::cout<<s<<std::endl;
    }
};

int main(){
    int n = 5;
    Visual* arr = UserNewArray<Visual>(n);
    for(int i = 0; i < n; ++i){
        (arr+i)->SetPosition(i, i,i+1,i+2);
    }
    for(int i = 0; i < n; ++i){
        (arr+i)->print();
    }
    UserDeleteArray(arr);
}