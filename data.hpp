//
// Created by Simon on 2020-04-20.
//

#ifndef FILMTAR_DATA_HPP
#define FILMTAR_DATA_HPP

#include <iostream>

using namespace std;

/** @class Data data.hpp
 *  @brief Dinamikus heterogén kollekció kezelő osztály
 *
 * @tparam T A heterogén kollekció típusa
 *
 * @note
 * Ez a programrész Movie típusú dinamikus tömb tárolására készült,
 * a sablonos megoldás csak a későbbi újrafelhasználhatóságot szolgálja.
 */
template<class T>
class Data {
    unsigned int elementCount; /**< A tárolt elemek száma */
    T** array; /**< A dinamikusan foglalt tömbre mutató pointer */
public:
    /** Konstruktor */
    Data<T>() {
        elementCount = 0;
        array = new T*[elementCount];
    }

    // TODO: ez csak fájl beolvasásánál lehet hasznos, kell?
    explicit Data(unsigned int size) {
        elementCount = size;
        array = new T*[size];
    }

    /** Másoló konstruktor
     *
     * @param from Az a Data típusú elem, amiből másolni szeretnénk az újba
     */
    Data<T>(const Data& from) {
        array = new T*[from.elementCount];
        for (unsigned int i = 0; i < from.elementCount; ++i)
            array[i] = from.array[i];
        elementCount = from.elementCount;
    }

    /** Destruktor */
    virtual ~Data<T>() {
        delete[] array;
    }

    /** Getter függvény az elementCount értékének visszaadására
     *
     * @return A tárolt elemek száma
     */
    unsigned int getElementCount() {
        return elementCount;
    }

    /** Elem felvétele a tömbbe, ha nem sikerült a foglalás, kivételt dob
     *
     * @param movieToAdd A felveendő film
     */
    void addElement(T& elementToAdd) {
        try {
            T** newArray = new T*[elementCount + 1];
            for (int i = 0; i < elementCount; ++i)
                newArray[i] = array[i];
            newArray[elementCount] = &elementToAdd;
            delete[] array;
            array = newArray;
            elementCount += 1;
        }
        catch (bad_alloc& e) {
            cout << "A memoriafoglalas nem sikerult: " << e.what() << endl;
        }
    }

    /** Elem törlése a tömbből, ha nem sikerült a felszabadítás, kivételt dob
     *
     * @param id A törlendő film azonosítója
     */
    void removeElement(unsigned int id) {
        try {
            if (elementCount <= id)
                throw out_of_range("Torles: A megadott azonositoju elem nem letezik.\n");

            elementCount -= 1;
            T** newArray = new T*[elementCount];
            for (unsigned int i = 0; i < elementCount; ++i) {
                if (i == id) // ha eléri a törlendő elemet, eggyel növeljük a számlálót, és továbblépünk
                    i++;
                else {
                    if (i > id) {
                        array[i]->setID(array[i]->getID() - 1);
                        newArray[i - 1] = array[i];
                    }
                    else
                        newArray[i] = array[i];
                }
            }
            delete [] array;
            array = newArray;
            cout << "Torles sikeres" << endl;
        }
        catch (out_of_range& indexError) {
            cout << indexError.what() << endl;
        }
        catch (bad_alloc& memError) {
            cout << "A memoriafoglalas nem sikerult: " << memError.what() << endl;
        }
    }

    /** Elem törlése a tömbből, ha nem sikerült a felszabadítás, kivételt dob
     *
     * @param elementToRemove A törlendő elem referenciája
     */
    void removeElement(T& elementToRemove) {
        for (unsigned int i = 0; i < elementCount; ++i) {
            if (array[i] == &elementToRemove) {
                removeElement(i);
                return;
            }
        }
        cout << "A megadott film nem talalhato." << endl;
    }

    /** Indexelő operator
     *
     * @param index A keresett elem indexere
     * @return A tömb indexedik eleme, T típusú referencia
     */
    T*& operator[](unsigned int index) {
        try {
            if (index >= elementCount)
                throw out_of_range("A megadott indexu elem nem letezik.");
        }
        catch (out_of_range& indexError) {
            cout << indexError.what() << endl;
        }
        return array[index];
    }
    //const T* operator[](unsigned int index) const;
    //const T& operator[](unsigned int index) const;
    // TODO: operator=?

    /** Az operator= overloadja Data típusra
     *
     * @param rhs Az a Data típusú objektum, aminek az adatait az adott objektumba szeretnénk rakni
     * @return Az rhs-sel megegyező tulajdonságú Data&
     */
    Data& operator=(Data rhs) {
        for (unsigned int i = 0; i < rhs.elementCount; ++i) { // TODO: for nélkül, sima másolásnál ok?
            array[i] = rhs.array[i];
        }
        elementCount = rhs.elementCount;
        return *this;
    }
};


#endif //FILMTAR_DATA_HPP
