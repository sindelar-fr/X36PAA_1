/* 
 * File:   Polozka.cpp
 * Author: franta
 * 
 * Created on 2. říjen 2009, 19:06
 */

#include "Polozka.h"

Polozka::Polozka(int hmotnost, int cena) {
    this->hmotnost = hmotnost;
    this->cena = cena;
}

Polozka::Polozka(){
    
}

Polozka::~Polozka() {
}
/*
bool Polozka::operator<(const Polozka& b) {
    double pomerA = this->cena/this->hmotnost;
    double pomerB = b.cena/b.hmotnost;
    return pomerA<pomerB;
}*/

