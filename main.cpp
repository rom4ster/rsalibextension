#include <iostream>
#include "librsa.h"
#include "mpuint.h"



int main() {
    std::cout << "Hello, World!" << std::endl;


    Librsa rsa;




     auto m = rsa.encrypt("0123456789abcdef01[5375k7J9ab1def");
     std::cout << "ENCRYPT --> " << m << std::endl;
     auto r = rsa.decrypt(m);
    std::cout << "DECRYPT --> " <<  r << std::endl;
    exit(2);



}



