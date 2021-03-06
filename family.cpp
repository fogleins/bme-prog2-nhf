//
// Created by Simon on 2020-04-17.
//

#include "family.h"

using std::cout;
using std::string;
using std::ostream;

/** Értékadás operator overloadja Family típusra
 *
 * @param rhs A jobboldali operandus
 * @return A jobboldali operandussal megegyező tulajdonságú Family&
 */
Family& Family::operator=(const Family& rhs) {
    if (this != &rhs) {
        setID(0);
        setTitle(rhs.getTitle());
        setRunningTime(rhs.getRunningTime());
        setReleaseYear(rhs.getReleaseYear());
        setCategory(rhs.getCategory());
        ageRating = rhs.ageRating;
    }
    return *this;
}

/** Egyenlőségvizsgálat-operator overloadja Family típusra
 *
 * @param rhs A jobboldali operandus
 * @return Igaz, ha a két film megegyezik
 */
bool Family::operator==(const Family &rhs) const {
    if (this == &rhs)
        return true;
    else
        return this->getTitle() == rhs.getTitle() && this->getRunningTime() == rhs.getRunningTime() &&
            this->getReleaseYear() == rhs.getReleaseYear() && this->getCategory() == rhs.getCategory() &&
            ageRating == rhs.ageRating;
}

/** A megadott ostreamre írja a film adatait
 *
 * @param os Az ostream, amire az adatokat írja
 * @param file Igaz, ha fájlba kell írni az adatokat
 */
void Family::print(ostream& os, bool file) const {
    Movie::print(os, file);
    if (file)
        os << ';' << ageRating;
    else
        os << "\tKorhatar-besorolas: " << ageRating;
}
