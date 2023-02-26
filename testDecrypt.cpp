#include <iostream>
#include "librsa.h"

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
int main(int c, char ** v) {


    if (c > 2) {
        std::cout << "Invalid arguments, specify string or none to read from user input" << std::endl;
        exit(1);
    }

    Librsa rsa;

    std::string testInput;
    if (c ==2) {
        testInput = std::string(v[1]);
    } else {
        std::getline(std::cin, testInput);
    }
    auto pos = testInput.find('\n');
    if (pos != std::string::npos) {
        testInput.replace(pos,1,"");
    }
    auto out = rsa.decrypt(testInput);
    std::cout<<out<<std::endl;

}