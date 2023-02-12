//
// Created by rom4ster on 2/7/2023.
//

#include <string>
#include "mpuint.h"
#include <iostream>
#include <fstream>
#include "rsa.h"
#include <vector>

#define DEFAULT_PUB_FILE "./public"
#define DEFAULT_PRIV_FILE "./private"
#define DEFAULT_MOD_FILE "./modulus"
#define DEFAULT_PAD '-'

#define MPUINT_SIZE 16

class Librsa {
private:
    mpuint *  d;
    mpuint *  e;
    mpuint *  n;
    std::string pad;

    unsigned short * parseFile(std::string fileName);
    static unsigned short * parseMsg(std::string msg);
    std::vector<std::string> groupMessage(std::string msg);
    [[nodiscard]] std::string makeString(std::vector<unsigned short *> v) const;
    static std::string asString(std::vector<unsigned short *> v);

    static std::vector<unsigned short *> fromString(std::string s);

public:

    explicit Librsa(std::string pubFile = DEFAULT_PUB_FILE, std::string privFile = DEFAULT_PRIV_FILE, std::string modFile = DEFAULT_MOD_FILE, char pad = DEFAULT_PAD) {

        this->e = new mpuint(MPUINT_SIZE);
        this->d = new mpuint(MPUINT_SIZE);
        this->n = new mpuint(MPUINT_SIZE);

        e->value = parseFile(pubFile);
        d->value = parseFile(privFile);
        n->value = parseFile(modFile);
        char tmp [2];
        tmp[0] = pad;
        tmp[1] = 0x0;
        this->pad = std::string(tmp);

    }
    ~Librsa() {
        delete d;
        delete e;
        delete n;
    }

    std::string encrypt(std::string msg);
    std::string decrypt(std::string msg);



};