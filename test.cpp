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
#include <iostream>
#include "librsa.h"




int main() {
    std::cout << "Hello, World!" << std::endl;


    Librsa rsa;




     //auto m = rsa.encrypt("0123456789abcdef01[5375k7J9ab1def");
     auto m = rsa.encrypt("shutdown1676167628");
     std::cout << "ENCRYPT --> " << m << std::endl;
     auto r = rsa.decrypt(m);
    std::cout << "DECRYPT --> " <<  r << std::endl;
    exit(0);



}



