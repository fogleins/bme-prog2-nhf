//
// Created by Simon on 2020-04-20.
//

#ifndef FILMTAR_DATA_H
#define FILMTAR_DATA_H

#include "movie.h"

class Data {
    int elementCount;
    Movie* array;
public:
    Data();
    ~Data();
    /**
     *
     * @return A tárolt elemek száma
     */
    int getElementCount();
    // TODO
    /** Elem felvétele a tömbbe
     * @return true, ha sikerült felvenni
     */
    bool addElement();
    bool removeElement();
    // TODO
    /** Korábban létrehozott gyűjtemény betöltése fájlból
     *
     * @return true, ha sikeres volt a beolvasás
     */
    bool fromFile();
    Movie operator[](Movie& mv);
};


#endif //FILMTAR_DATA_H
