/* 
 * File:   Pripad.cpp
 * Author: franta
 * 
 * Created on 2. říjen 2009, 20:36
 */

#include "Pripad.h"


Pripad::Pripad(int velikost) {
    this->pole= new Polozka*[velikost];
}

Pripad::Pripad(const Pripad& orig) {
}

Pripad::~Pripad() {
}

