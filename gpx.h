/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef GPX_H_INCLUDED
#define GPX_H_INCLUDED

#include <string>
#include <vector>
#include "track.h"

using namespace std;

/**
 * Classe permettant la manipulation des fichiers GPX et de leur contenu.
 */
class Gpx
{
    private:
/// Liste des Traces.
        vector<Track*> fTracks;

/// Liste des WayPoints.
        vector<PointGPX*> fWayPoints;

    protected:

    public:
/**
 * Contructeur de l'instance.
 * Initialise l'instance et lit le fichier dont le chemin est indiqué.
 * \param aFichier Chemin du fichier à lire ; si le chemin est vide, aucun fichier n'est lu.
 * \throw exception si une erreur se produit pendant la lecture du fichier.
 */
        Gpx(const string& aFichier = "");

/**
 * Destructeur de l'instance.
 */
        ~Gpx(void);

/**
 * Retourne la somme des montées.
 * \return Un entier indiquant la somme des progressions positives.
 */
        unsigned getDenivelePositif(void) const;

/**
 * Retourne la somme des descentes.
 * \return Un entier indiquant la somme des progressions négatives.
 */
        unsigned getDeniveleNegatif(void) const;

/**
 * Indique si le fichier ne contient aucune trace (<trk>) exploitable.
 * \return true s'il n'y a pas de trace, false sinon.
 */
        bool noTrack(void) const { return fTracks.empty(); }

/**
 * Retourne le premier point du fichier.
 * \return Un pointeur sur le premier PointGPX trouvé dans le fichier.
 * \warning Ne tient pas compte de l'ordre chronologique (champ time).
 */
        const PointGPX* premier(void) const;

/**
 * Retourne le dernier point du fichier.
 * \return Un pointeur sur le dernier PointGPX trouvé dans le fichier.
 * \warning Ne tient pas compte de l'ordre chronologique (champ time).
 */
        const PointGPX* dernier(void) const;

/**
 * Retourne la longueur des traces mesurée à l'altitude 0.
 * \return Un réel indiquant la longueur en mètres.
 */
        float longueur(void) const;

};

#endif // GPX_H_INCLUDED
