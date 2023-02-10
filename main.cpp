#include <iostream>
#include "librsa.h"
#include "mpuint.h"



// l;dkj;sldkfj;ads
// ertoiupeorghd;f,
// ;laine;lvikhn;soijf;lieslifbnslm


int main() {
    std::cout << "Hello, World!" << std::endl;

    /*mpuint d(16);
    mpuint e(16);
    mpuint n(16);*/

    //GenerateKeys(d, e, n);


    unsigned short dv []= {0xf36f, 0x6169, 0x6e65, 0x3b6c, 0x7669, 0x6b68, 0x6e3b, 0x736f, 0x696a, 0x663b, 0x6c69, 0x6573, 0x6c69, 0x6662, 0x6e73, 0x6c6d};
    unsigned short ev []= {0x4f3f, 0x767f, 0x336c, 0x4d41, 0x4eb, 0xac18, 0x8ca1, 0xb40a, 0xa500, 0xe5a, 0x59b5, 0xccde, 0xf0de, 0x7ee1, 0x45c9, 0x7f05};
    unsigned short nv []= {0xb807, 0xcaa0, 0xc41a, 0xb102, 0x4d7b, 0xcd9a, 0xa185, 0x9990, 0x6f17, 0x7415, 0x5be2, 0x5c0d, 0x7b1e, 0xbcc9, 0x2499, 0xcd67};

    Librsa rsa;
    //rsa.d->dump();
    //rsa.e->dump();
    //rsa.n->dump();


     auto z = rsa.parseMsg("0123456789abcdef");


     auto m = rsa.encrypt("0123456789abcdef015375k7J9a[b]1def");
     std::cout << "ENCRYPT --> " << m << std::endl;
     auto r = rsa.decrypt(m);
    std::cout << "DECRYPT --> " <<  r << std::endl;
    exit(2);



}



