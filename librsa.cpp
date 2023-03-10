/*

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




std::string Librsa::makeString(std::vector<unsigned short *> v) const {
    std::string s = "";
    for (auto & i : v) {
        for (int j = 0; j< 16; j++) {

            s.push_back((char) i[j]);

        }
    }
    s.erase(std::remove(s.begin(), s.end(), pad[0]), s.end());
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
        delete edr;
        delete temp;
    }
    auto ret = asString(res);
    for (int i = 0; i < res.size(); i ++) delete[] (res[i]);

    return ret;
}
std::string Librsa::decrypt(std::string msg) {
    std::vector<unsigned short *> res;
    std::vector<unsigned short *> msgs = fromString(msg);
    for (const auto & mssg : msgs) {
        auto temp = new mpuint(16);
        temp->value = mssg;
        auto edr = new mpuint(16);
        EncryptDecrypt(*edr,*temp,*d,*n);
        auto arr = new unsigned short [edr->length];
        for (int i = 0; i < edr->length; i++) {
            // std::cout << edr.value[i] << " ";
            arr[i] = edr->value[i];
        }
        res.push_back(arr);
        delete edr;

    }



    auto ret = makeString(res);
    for (auto & re : res) delete[] re;
    return ret;
}

void Librsa::generateKeys(std::string d, std::string e, std::string n) {

    auto validFiles = false;
    if (!d.empty() && !e.empty() && !n.empty())  validFiles = true;

    std::ofstream df;
    std::ofstream ef;
    std::ofstream nf;
// jfhdjgnhbfjgfhdj
// sksdhjenmfjksjrm
// sjsl;e;wbnv;sdsf




    if (validFiles) {
        df.open(d);
        ef.open(e);
        nf.open(n);
    }

    std::stringstream ds;
    std::stringstream es;
    std::stringstream ns;



    auto dm = new mpuint(16);
    auto em = new mpuint(16);
    auto nm = new mpuint(16);

    GenerateKeys(*dm,*em,*nm);

    for (int i = 0; i < 16; i ++) {
        ds << ", " << std::hex<<dm->value[i];
        es << ", " << std::hex<<em->value[i];
        ns << ", " << std::hex<<nm->value[i];
    }
    ds = std::stringstream(ds.str().c_str()+1);
    es = std::stringstream(es.str().c_str()+1);
    ns = std::stringstream(ns.str().c_str()+1);

    if (validFiles) {
        df << ds.str();
        ef << es.str();
        nf << ns.str();
    }
    df.close();
    ef.close();
    nf.close();

    std::cout << ds.str() << std::endl;
    std::cout << es.str() << std::endl;
    std::cout << ns.str() << std::endl;


}



