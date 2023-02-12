/*
     Copyright (C) 2023  rom4ster

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
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