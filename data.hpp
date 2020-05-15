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
    ~Data<T>() {
        for (unsigned i = 0; i < elementCount; ++i)
            delete array[i];
        delete[] array;
    }

    /** Getter függvény az elementCount értékének visszaadására
     *
     * @return A tárolt elemek száma
     */
    unsigned int getElementCount() {
        return elementCount;
    }

    /** Elem felvétele a tömbbe
     *
     * @param elementToAdd A felveendő elem
     */
    void addElement(T& elementToAdd) {
        T** newArray = new T*[elementCount + 1];
        for (unsigned int i = 0; i < elementCount; ++i)
            newArray[i] = array[i];
        newArray[elementCount] = &elementToAdd;
        delete[] array;
        array = newArray;
        elementCount += 1;
    }

    /** Elem törlése a tömbből
     *  @note Ha a memóriafoglalás nem sikerül, std::bad_alloc kivétel kerül dobásra,
     *  amit a hívónak kell kezelnie
     *
     * @param id A törlendő elem azonosítója
     */
    void removeElement(unsigned int id) {
        if (elementCount <= id)
            throw out_of_range("Torles: A megadott azonositoju elem nem letezik.\n");

        elementCount -= 1;
        T** newArray = new T*[elementCount];
        for (unsigned int i = 0; i < elementCount; ++i) {
            if (i >= id) {
                array[i]->setID(array[i]->getID() - 1);
                newArray[i] = array[i + 1];
            }
            else
                newArray[i] = array[i];
        }
        delete array[id];
        delete[] array;
        array = newArray;
    }

    /** Elem törlése a tömbből
     *  @note Ha a memóriafoglalás nem sikerül, std::bad_alloc kivétel kerül dobásra,
     *  amit a hívónak kell kezelnie
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
        throw runtime_error("A megadott elem nem szerepel a tombben.");
    }

    /** Indexelő operator
     *
     * @param index A keresett elem indexere
     * @return A tömb indexedik eleme, T típusú referencia
     * @throws std::out_of_range ha a megadott elem túlmutat
     * a tömb határain
     */
    T*& operator[](unsigned int index) {
        if (index >= elementCount)
            throw out_of_range("A megadott indexu elem nem letezik.");
        return array[index];
    }

    /** Az operator= overloadja Data típusra
     *
     * @param rhs Az a Data típusú objektum, aminek az adatait az adott objektumba szeretnénk rakni
     * @return Az rhs-sel megegyező tulajdonságú Data&
     */
    Data& operator=(Data rhs) {
        for (unsigned int i = 0; i < rhs.elementCount; ++i) {
            array[i] = rhs.array[i];
        }
        elementCount = rhs.elementCount;
        return *this;
    }
};


#endif //FILMTAR_DATA_HPP
