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

using namespace std;

class Track
{
    private:
/// Nom de la trace.
        const string fName;

/// Description de la trace.
        const string fDesc;

/// Structure du Point.
        struct Point { double lat, lon; float alt; string time; };

/// Segments composants une trace.
        vector< vector<Point> > fSegments;

    protected:

    public:
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
 * M�thode de classe instanciant une Track � partir d'un TiXmlElement.
 * \param aElement Une r�f�rence sur un TiXmlElement.
 * \return Un pointeur sur une instance de Track. La destruction de l'instance
 *         est � la charge de l'utilisateur de cette m�thode.
 */
        static Track* parser(TiXmlElement& aElement);

/**
 * Retourne la somme des mont�es.
 * \return Un entier indiquant la somme des progressions positives.
 */
        float getDenivelePositif(void) const;

/**
 * Retourne la somme des descentes.
 * \return Un entier indiquant la somme des progressions n�gatives.
 */
        float getDeniveleNegatif(void) const;

};

#endif // TRACK_H
