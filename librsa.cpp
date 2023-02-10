//
// Created by rom4ster on 2/7/2023.
//

#include <cstring>
#include <vector>
#include "librsa.h"
#include <sstream>
#include <iomanip>


unsigned short *Librsa::parseFile(std::string fileName) {
    std::ifstream file;
    file.open(fileName);
    std::string data;
    if (file.fail()) {
        std::cout << "fail\n";
    }
    std::getline(file, data);


    std::vector<unsigned short> res;
    for (char *p = strtok( (char *) data.c_str(),","); p != nullptr; p = strtok(nullptr, ","))
    {
        unsigned  short tempChar = std::stoul(p, nullptr, 16);
        res.push_back(tempChar);
    }
    auto ret = new unsigned short [res.size()];
    for (int i = 0; i < res.size(); i++) {
        ret[i] = res[i];
    }
    return ret;
}

std::vector<std::string> Librsa::groupMessage(std::string msg) {
    std::vector<std::string> v;
    std::string msgg = msg;
    unsigned int msgMod = 0;
    if ( (msgMod = (msg.length() % 16)) != 0 ) {
        for ( int i = 0; i < (16-msgMod); i++) {
            msgg.append(&pad);
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




std::string Librsa::makeString(std::vector<unsigned short *> v) const {
    std::string s = "";
    for (auto & i : v) {
        for (int j = 0; j< 16; j++) {

            s.push_back((char) i[j]);

        }
    }
    s.erase(std::remove(s.begin(), s.end(), pad), s.end());
    return s;
}


std::string Librsa::asString(std::vector<unsigned short *> v) {
    std::stringstream s;
    for (auto & i : v) {
        for (int j = 0; j < 16; j++) {
            auto val = i[j];
            s << std::setfill('0') << std::setw(sizeof(unsigned short)*2)<< std::hex << (unsigned int) val;
        }
    }
    return  s.str();
}

std::vector<unsigned short *> Librsa::fromString(std::string s) {

    int full_length = s.length()/(sizeof(unsigned short) * 2);
    auto full = new unsigned short [full_length];
    auto str = s.c_str();
    auto len = s.length() + str;
    auto f = 0;
    while (str < len) {
        std::stringstream tmp;
        for (int i = 0; i < 4; i++) {
            tmp << *str;
            str++;
        }
        full[f] = std::stoul(tmp.str(), nullptr, 16);
        f++;
    }

    std::vector<unsigned short *> ret;
    int chunk_size =  16;
    unsigned short * chunk = full;

    while( (chunk - full) < full_length ) {
        ret.push_back(chunk);
        chunk +=chunk_size;
    }
    return ret;


}


std::string Librsa::encrypt(std::string msg) {
    std::vector<std::string> msgs = groupMessage(msg);
    std::vector<unsigned short *> res;
    for (const auto & msg : msgs) {
        auto parsed = parseMsg(msg);
        auto temp = new mpuint(16);
        temp->value = parsed;
        auto edr = new mpuint(16);
        EncryptDecrypt(*edr,*temp,*e,*n);
        auto arr = new unsigned short [edr->length];
        for (int i = 0; i < edr->length; i++) {
            // std::cout << edr.value[i] << " ";
            arr[i] = edr->value[i];
        }
        res.push_back(arr);
    }
    return asString(res);
}
std::string Librsa::decrypt(std::string msg) {
    std::vector<unsigned short *> res;
    std::vector<unsigned short *> msgs = fromString(msg);
    for (const auto & msg : msgs) {
        auto temp = new mpuint(16);
        temp->value = msg;
        auto edr = new mpuint(16);
        EncryptDecrypt(*edr,*temp,*d,*n);
        auto arr = new unsigned short [edr->length];
        for (int i = 0; i < edr->length; i++) {
            // std::cout << edr.value[i] << " ";
            arr[i] = edr->value[i];
        }
        res.push_back(arr);


    }
    return makeString(res);
}



