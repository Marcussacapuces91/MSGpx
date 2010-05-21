/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef POINTGPX_H
#define POINTGPX_H

#include "point.h"

#include <string>
#include "tinyxml\tinyxml.h"

using namespace std;

class PointGPX : public Point
{
    public:
/**
 * Constructeur de l'instance. Initialise les attributs.
 */
        PointGPX(const double& aLat,
                 const double& aLon,
                 const float& aEle = 0,
                 const string& aTime="",
                 const string& aName = "",
                 const string& aLink = "",
                 const float& aHDOP = 0,
                 const float& aVDOP = 0,
                 const float& aPDOP = 0) :
            Point(aLat, aLon),
            fEle(aEle),
            fTime(aTime),
            fName(aName),
            fLink(aLink),
            fHDOP(aHDOP),
            fVDOP(aVDOP),
            fPDOP(aPDOP)
        {};

/**
 * Destructeur de l'instance. Sans action.
 */
        virtual ~PointGPX() {};

/**
 * Méthode de classe assurant la génération d'un PointGPX à partir d'un Element XML.
 * \warning La destruction de l'instance PointGPX est à la charge de
 *          l'utilisateur de cette méthode.
 * \param aElement Une référence vers l'élément à analyser.
 * \return Un pointeur sur une instance de PointGPX.
 */
        static PointGPX* parser(TiXmlElement& aElement);

        const float& ele(void) const { return fEle; }

    protected:

    private:
        const float fEle;
        const string fTime;
        const string fName;
        const string fLink;
        const float fHDOP;
        const float fVDOP;
        const float fPDOP;
};

#endif // POINTGPX_H
