/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef SEGMENT_H
#define SEGMENT_H

#include "pointgpx.h"
#include <vector>

using namespace std;

/**
 * Instancie un segment compos� de Point
 */
class Segment
{
    public:
        enum Sens {MONTANT = +1, DESCENDANT = -1} ;

/**
 * Constructeur de l'instance.
 */
        Segment();

/**
 * Destructeur de l'instance.
 */
        ~Segment();

/**
 * Ajoute un Point dans le Segment existant.
 * \param aPoint Une r�f�rence sur un Point.
 */
        void add(PointGPX *const apPoint)
        { if (apPoint) fPoints.push_back(apPoint); }

        float getDenivele(const Sens aSens = MONTANT) const;

/**
 * Retourne le premier point du segment.
 * \return Un pointeur sur le premier PointGPX trouv� dans le segment.
 * \warning Ne tient pas compte de l'ordre chronologique (champ time).
 */
        const PointGPX* premier(void) const;

/**
 * Retourne le dernier point du segment.
 * \return Un pointeur sur le dernier PointGPX trouv� dans le segment.
 * \warning Ne tient pas compte de l'ordre chronologique (champ time).
 */
        const PointGPX* dernier(void) const;

/**
 * Retourne la longueur du segment mesur� � l'altitude 0.
 * \return Un r�el indiquant la longueur en m�tres.
 */
        float longueur(void) const;

    protected:

    private:
/// Liste ordonn�e des PointGPX.
        vector<PointGPX*> fPoints;

};

#endif // SEGMENT_H
