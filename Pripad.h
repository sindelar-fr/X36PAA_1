/* 
 * File:   Pripad.h
 * Author: franta
 *
 * Created on 2. říjen 2009, 20:36
 */

#ifndef _PRIPAD_H
#define	_PRIPAD_H
#include "Polozka.h"


class Pripad {

public:
    Polozka * pole;
    Pripad(int velikost);
    Pripad(const Pripad& orig);
    virtual ~Pripad();
private:

};

#endif	/* _PRIPAD_H */

