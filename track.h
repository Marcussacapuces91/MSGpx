/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef TRACK_H
#define TRACK_H

#include <string>
#include "tinyxml\tinyxml.h"
#include <vector>
#include "segment.h"

using namespace std;

class Track
{
    private:
/// Nom de la trace.
        const string fName;

/// Description de la trace.
        const string fDesc;

/// Segments composants une trace.
        vector<Segment*> fSegments;

    protected:

    public:
/// Définition du Sens et de ses 2 valeurs possibles.
/// \see getDenivele().
        enum Sens { MONTANT, DESCENDANT};

/**
 * Constructeur de l'instance.
 * \param aName Nom de l'instance.
 * \param aDesc Description de l'instance.
 */
        Track(const string& aName = "",
              const string& aDesc = "");

/**
 * Destructeur de l'instance.
 */
        ~Track();

/**
 * Méthode de classe instanciant une Track à partir d'un TiXmlElement.
 * \param aElement Une référence sur un TiXmlElement.
 * \return Un pointeur sur une instance de Track. La destruction de l'instance
 *         est à la charge de l'utilisateur de cette méthode.
 */
        static Track* parser(TiXmlElement& aElement);

/**
 * Retourne la somme des montées.
 * \return Un entier indiquant la somme des progressions positives.
 */
        float getDenivele(const Sens aSens = MONTANT) const;

/**
 * Retourne le premier point de la trace.
 * \return Un pointeur sur le premier PointGPX trouvé dans la trace.
 * \warning Ne tient pas compte de l'ordre chronologique (champ time).
 */
        const PointGPX* premier(void) const;

/**
 * Retourne le dernier point de la trace.
 * \return Un pointeur sur le dernier PointGPX trouvé dans la trace.
 * \warning Ne tient pas compte de l'ordre chronologique (champ time).
 */
        const PointGPX* dernier(void) const;

/**
 * Retourne la longueur de la trace mesurée à l'altitude 0.
 * \return Un réel indiquant la longueur en mètres.
 */
        float longueur(void) const;

};

#endif // TRACK_H
