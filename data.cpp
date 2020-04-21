//
// Created by Simon on 2020-04-20.
//

#include "data.h"

void Data::addElement(Movie& movieToAdd) {
    try {
        Movie* newArray = new Movie[elementCount + 1];
        for (int i = 0; i < elementCount; ++i)
            newArray[i] = array[i];
        newArray[elementCount] = movieToAdd; // TODO: operator overload?
        delete[] array;
        array = newArray;
    }
    catch (bad_alloc& e) {
        cout << "A memoriafoglalas nem sikerult: " << e.what() << endl;
    }
}

// TODO: overload - lehessen index és Movie típus szerint is törölni?
void removeElement(int id) {
    // TODO
}