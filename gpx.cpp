/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#include "gpx.h"

#include "tinyxml\tinyxml.h"
#include <iostream>
#include "track.h"

using namespace std;

Gpx::Gpx(const string& aFichier)
{
    if (!aFichier.empty()) {
        TiXmlDocument doc(aFichier.c_str());
        if (!doc.LoadFile()) throw string("Lecture impossible du fichier ") + aFichier + " (" + doc.ErrorDesc() + ")";

        TiXmlElement *const pGpx = dynamic_cast<TiXmlElement *const>(doc.FirstChild("gpx"));
        if (!pGpx) throw string("Element <gpx> attendu");

        for (TiXmlNode* pTrk = pGpx->FirstChild("trk"); pTrk; pTrk = pTrk->NextSibling() ) {
            fTracks.push_back(Track::parser(*dynamic_cast<TiXmlElement *const>(pTrk)));
        }
    }
}

Gpx::~Gpx(void)
{
    for (unsigned i = 0; i < fTracks.size(); ++i) delete fTracks[i];
}

unsigned Gpx::getDenivelePositif(void) const
{   float den = 0;
    for (vector<Track*>::const_iterator it = fTracks.begin(); it != fTracks.end(); ++it)
        den += (*it)->getDenivelePositif();
    return static_cast<unsigned>(den + 0.5);
}

unsigned Gpx::getDeniveleNegatif(void) const
{   float den = 0;
    for (vector<Track*>::const_iterator it = fTracks.begin(); it != fTracks.end(); ++it)
        den += (*it)->getDeniveleNegatif();
    return static_cast<unsigned>(den + 0.5);
}


