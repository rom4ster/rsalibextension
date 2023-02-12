# rsalibextension
using files at http://www.efgh.com/software/rsa.txt to make a simple rsa lib in C++. This is not a production ready security suite but rather a way for small time quick &amp; dirty encryption for lesser risk environments. 


This is a great solution for those who just want to keep it simple and have it work. The way it works is that it will take a user defined or default "padding character" 
(this character may not show up in your original string, or it will be removed) and use it to make your string length a multiple of 16. Then it will take the string 
and split it into 16 character chunks, which will then be encrypted. The encrypted result is returned as a string representing an array of unsigned shorts.
Passing this string into the decrypt function will reconstitute it into an array of unsigned shorts and split it into chunks of size 16. These chunks will be decrypted
and appended to the result string. After removing the padding character, the result string will be returned. 

Encryption and decryption keys are of length 16 currently and must be in the following format

```<short>,<short>,<short>...```
where <short> is a string representing a short, written as hex. 

The public, private, and modulus files must adhere to this format.

Currently auto generation of these files is not supported however, the rsa.cpp file does contain a "GenerateKeys" method that can be used for creation of these keys

Usage:

```Librsa(std::string pubFile = DEFAULT_PUB_FILE, std::string privFile = DEFAULT_PRIV_FILE, std::string modFile = DEFAULT_MOD_FILE, char pad = DEFAULT_PAD)```

pubFile: Link to public file, or "./public" by default
privFile: Link to private file or "./private" by default
modFile: Link to modulus file or "./modulus" by default
pad: what character to pad with or '_' by default


```   
    std::string encrypt(std::string msg);
    std::string decrypt(std::string msg);
```
These functions will take a message and encrypt/decrypt it. Note that the string input in decrypt is actually a hex representation of an unsigned short array
while in encrypt it is whatever data needs encryption, as a string. 


Compilation of this library can be done via cmake. Make will also work however it
has not been set up. A PR for this would be helpful. Contributions to make 
this library better would be great. Remember the philosophy of simple and
beginner-friendly.

Due to the different types of files in this code, it uses 3 licences 

This software is composed of code used from http://www.efgh.com/software/rsa.txt
This code is in the public domain and therefore free to use for any purpose

Any modifications to these files (such as mpuint.cpp) are distributed under GPL
All new files except the ones in the following exception list are GPL

Exception List:

    allrightreserved

Any files in the exception list are All Rights Reserved and their usage is
described in the file itself


For all GPL files, the following applies

    librsa, a way to encrypt simply for beginners.
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




