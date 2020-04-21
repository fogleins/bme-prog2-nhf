//
// Created by Simon on 2020-04-20.
//

#ifndef FILMTAR_DATA_H
#define FILMTAR_DATA_H

#include <iostream>

#include "movie.h"

class Data {
    int elementCount;
    Movie* array;
public:
    Data() {
        elementCount = 0;
        array = new Movie[100]; // TODO: Mekkora mérettel inicializálódjon?
    }
    /** Destruktor */
    ~Data() {
        delete[] array;
    }
    /** Getter függvény az elementCount értékének visszaadására
     *
     * @return A tárolt elemek száma
     */
    int getElementCount() {
        return elementCount;
    }
    // TODO
    /** Elem felvétele a tömbbe
     * ha nem sikerült a foglalás / felszabadítás, kivételt dob
     */
    void addElement(Movie& movieToAdd);
    void removeElement(int id);
    // TODO
    /** Korábban létrehozott gyűjtemény betöltése fájlból
     *
     * @return true, ha sikeres volt a beolvasás
     */
    void open(const char* path);
    Movie& operator[](unsigned int index);
};


#endif //FILMTAR_DATA_H
