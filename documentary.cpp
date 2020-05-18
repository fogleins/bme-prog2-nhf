//
// Created by Simon on 2020-04-17.
//

#include "documentary.h"

using std::cout;
using std::string;
using std::ostream;

/** Értékadás operator overloadja Documentary típusra
 *
 * @param rhs A jobboldali operandus
 * @return A jobboldali operandussal megegyező tulajdonságú Documentary&
 */
Documentary& Documentary::operator=(const Documentary& rhs) {
    if (this != &rhs) {
        setID(0);
        setTitle(rhs.getTitle());
        setRunningTime(rhs.getRunningTime());
        setReleaseYear(rhs.getReleaseYear());
        description = rhs.description;
        setCategory(rhs.getCategory());
    }
    return *this;
}

/** Egyenlőségvizsgálat-operator overloadja Documentary típusra
 *
 * @param rhs A jobboldali operandus
 * @return Igaz, ha a két film megegyezik
 */
bool Documentary::operator==(const Documentary& rhs) const {
    if (this == &rhs)
        return true;
    else
        return this->getTitle() == rhs.getTitle() && this->getRunningTime() == rhs.getRunningTime() &&
            this->getReleaseYear() == rhs.getReleaseYear() && this->getCategory() == rhs.getCategory() &&
            this->description == rhs.description;
}

/** A megadott ostreamre írja a film adatait
 *
 * @param os Az ostream, amire az adatokat írja
 * @param file Igaz, ha fájlba kell írni az adatokat
 */
void Documentary::print(ostream& os, bool file) const {
    Movie::print(os, file);
    if (file)
        os << ";" << description;
    else
        os << "\tLeiras: " << description;
}
