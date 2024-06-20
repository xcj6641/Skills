#include <iostream>
#include <stdio.h>
#include <format>
#include <stdlib.h>

template<typename T, typename ... Types>
T* UserNew(Types&&... args) //throw(std::bad_alloc)
{
    void * p = malloc(sizeof(T));
    if(!p){
        throw std::bad_alloc();
    }
    //std::forward<E1>(e1), std::forward<E2>(e2), std::forward<E3>(e3)
    return new(p)T(std::forward<Types>(args)...);
}

template<typename T>
void UserDelete(T* p){
    if(!p) return;
    p->~T();
    free(p);
}

class Flat{
    int x;
    int y;
    std::string type;
public:
    Flat(int pX, int pY, std::string inType):x(pX), y(pY), type(std::move(inType)){}
    ~Flat(){
        std::string str = std::format("Flat({},{},{}) is released.", x,y,type);
        std::cout<<str<<std::endl;}
    void print(){
        std::string str = std::format("This is Flat with x={}, y={}, type={}", x,y, type);
        std::cout<< str<<std::endl;        
    }
};
class Visual{
    int x;
    int y;
    int z;
public:
    Visual(){}
    Visual(int inX, int inY, int inZ):x(inX),y(inY),z(inZ){}
    void SetPosition(int inX, int inY, int inZ){
        x = inX;
        y = inY;
        z = inZ;
    }
    void print(){
        std::cout<<"This is Visual with x="<<x<<", y="<<y<<", z="<<z<<std::endl;
    }
    ~Visual(){
        std::cout<<"Visual(x="<<x<<", y="<<y<<", z="<<z<<") is deleted"<<std::endl;
    }
};

int main(int argc, const char * argv[]){
    if (__cplusplus == 202101L) std::cout << "C++23";
    else if (__cplusplus == 202002L) std::cout << "C++20";
    else if (__cplusplus == 201703L) std::cout << "C++17";
    else if (__cplusplus == 201402L) std::cout << "C++14";
    else if (__cplusplus == 201103L) std::cout << "C++11";
    else if (__cplusplus == 199711L) std::cout << "C++98";
    else std::cout << "pre-standard C++." << __cplusplus;
    std::cout << "\n";

    Visual* visual = UserNew<Visual>();
    visual->SetPosition(2,3,4);
    visual->print();
    UserDelete(visual);

    Flat *flat = UserNew<Flat>(14,14,"Square");
    flat->print();
    return 0;
}