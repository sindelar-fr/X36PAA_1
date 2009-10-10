/* 
 * File:   Polozka.h
 * Author: franta
 *
 * Created on 2. říjen 2009, 19:06
 */

#ifndef _POLOZKA_H
#define	_POLOZKA_H

class Polozka {
public:
    Polozka();
    Polozka(int hmotnost, int cena);
   // bool operator<(const Polozka& b);
    int cena;
    int hmotnost;
    virtual ~Polozka();
private:

};

#endif	/* _POLOZKA_H */

