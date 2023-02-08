//
// Created by rom4ster on 2/7/2023.
//

#include <cstring>
#include <vector>
#include "librsa.h"





unsigned short *Librsa::parseFile(std::string fileName) {
    std::ifstream file;
    file.open(fileName);
    std::string data;
    std::getline(file, data);
    std::vector<unsigned short> res;
    for (char *p = strtok( (char *) data.c_str(),","); p != nullptr; p = strtok(nullptr, ","))
    {
        unsigned  short tempChar = std::stoul(data, nullptr, 16);
        res.push_back(tempChar);
    }
    auto ret = new unsigned short [res.size()];
    for (int i = 0; i < res.size(); i++) {
        ret[i] = res[i];
    }
    return ret;
}

std::vector<std::string> Librsa::groupMessage(std::string msg) {
    // take n length message and group by lengths of 16 padding with 0x0
    std::vector<std::string> v;
    unsigned int msgMod = 0;
    std::string msgg = msg;
    if ( (msgMod = (msg.length() % 16)) != 0 ) {
        for ( int i = 0; i < (16-msgMod); i++) {
            msgg.append(pad);
        }
    }
    int pos = 0;
    while (pos < msgg.length()) {
        std::string s = msgg.substr(pos,16);
        v.push_back(s);
        pos+=16;
    }

    return v;
}

unsigned short *Librsa::parseMsg(std::string msg) {

    auto len = msg.length();
    auto * ret = new unsigned short[len];
    for(int i = 0; i< len; i++) {
        ret[i] = msg[i];
    }
    return ret;


}

std::string Librsa::makeString(std::vector<unsigned short *> v) {
    std::string s = "";
    for (auto & i : v) {
        for (int j = 0; j< 16; j++) {
            s.push_back((char) i[j]);
        }
    }
    return s;

}

std::string Librsa::edcrypt(std::string msg, bool encrypt) {

    mpuint * ed = nullptr;
    ed = encrypt ? e : n;
    std::vector<std::string> msgs = groupMessage(msg);
    std::vector<unsigned short *> res;
    for (const auto & msg : msgs) {
        auto parsed = parseMsg(msg);
        auto temp = mpuint(16);
        temp.value = parsed;
        auto edr = mpuint(16);
        EncryptDecrypt(edr,temp,*ed,*n);
        auto arr = new unsigned short [edr.length];
        for (int i = 0; i < edr.length; i++) {
            arr[i] = edr.value[i];
        }
        res.push_back(arr);
    }
    return makeString(res);
}

std::string Librsa::encrypt(std::string msg) {
    return edcrypt(msg, true);
}
std::string Librsa::decrypt(std::string msg) {
    return edcrypt(msg, false);
}



