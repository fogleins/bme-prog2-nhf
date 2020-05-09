////
//// Created by Simon on 2020-04-20.
////
//


// Minden átkerült a data.hpp fájlba



////#include "data.h"
//
////template<class T>
////void Data<T>::addElement(T& elementToAdd) {
////    try {
////        T** newArray = new T*[elementCount + 1]; // TODO: T** "[]" nélkül?
////        for (int i = 0; i < elementCount; ++i)
////            newArray[i] = array[i];
////        newArray[elementCount] = &elementToAdd;
////        delete[] array;
////        array = newArray;
////        elementCount += 1;
////    }
////    catch (bad_alloc& e) {
////        cout << "A memoriafoglalas nem sikerult: " << e.what() << endl;
////    }
////}
//
//// TODO: overload - lehessen index és Movie típus szerint is törölni?
//// TODO: mi történik a törölt elemmel? delete keyword nem kell?
////template<class T>
////void Data<T>::removeElement(unsigned int id) {
////    try {
////        if (elementCount <= id)
////            throw out_of_range("A megadott azonositoju elem nem letezik.");
////
////        elementCount -= 1;
////        T** newArray = new T*[elementCount]; // TODO: prog2NHF könyvjelző stackoverflow kérdés alapján nem csak egy *?
////        for (unsigned int i = 0; i < elementCount; ++i) {
////            if (i == id) // ha eléri a törlendő elemet, eggyel növeljük a számlálót, és továbblépünk
////                i++;
////            else {
////                if (i > id) {
////                    array[i]->setID(array[i]->getID() - 1);
////                    newArray[i - 1] = array[i];
////                }
////                else
////                    newArray[i] = array[i];
////            }
////        }
////        delete [] array;
////        array = newArray;
////    }
////    catch (out_of_range& indexError) {
////        cout << indexError.what() << endl;
////    }
////    catch (bad_alloc& memError) {
////        cout << "A memoriafoglalas nem sikerult: " << memError.what() << endl;
////    }
////}
//
//template<class T>
////void Data<T>::removeElement(T& elementToRemove) {
////    for (unsigned int i = 0; i < elementCount; ++i) {
////        if (&array[i] == &elementToRemove) { // TODO: itt az array alapból is pointer, nem kell address of-oln, nem?
////            removeElement(i);
////            return;
////        }
////    }
////    cout << "A megadott film nem talalhato." << endl;
////}
//
//// TODO: referencia ok?
////template<class T>
////T*& Data<T>::operator[](unsigned int index) {
////    try {
////        if (index >= elementCount)
////            throw out_of_range("A megadott indexu elem nem letezik.");
////    }
////    catch (out_of_range& indexError) {
////        cout << indexError.what() << endl;
////    }
////    return array[index];
////}
//
////template<class T>
////const T* Data<T>::operator[](unsigned int index) const {
////    const T* ptr = array[index];
////    return ptr;
////}