/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#include "track.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

Track::Track(const string& aName,
             const string& aDesc) :
    fName(aName),
    fDesc(aDesc)
{
    //ctor
}

Track::~Track()
{
    for (vector<Segment*>::const_iterator it = fSegments.begin(); it != fSegments.end(); ++it) delete *it;
}

Track* Track::parser(TiXmlElement& aElement)
{
    TiXmlElement *const pName = dynamic_cast<TiXmlElement *const>(aElement.FirstChild("name"));
    TiXmlElement *const pDesc = dynamic_cast<TiXmlElement *const>(aElement.FirstChild("desc"));
    Track *const pTrack = new Track(pName ? pName->GetText() : "", pDesc ? pDesc->GetText() : "");
    assert(pTrack);
    for (TiXmlNode* pTrkSeg = aElement.FirstChild("trkseg"); pTrkSeg; pTrkSeg = pTrkSeg->NextSibling() ) {
        Segment *const pSegment = new Segment;
        for (TiXmlNode* pTrkPt = pTrkSeg->FirstChild("trkpt"); pTrkPt; pTrkPt = pTrkPt->NextSibling()) {
            TiXmlElement *const pElement = pTrkPt->ToElement();
            if (!pElement) {
                delete pSegment;
                delete pTrack;
                throw string("Element <trkpt> attendu");
            }
            pSegment->add(PointGPX::parser(*pElement));
        }
        pTrack->fSegments.push_back(pSegment);
    }
    return pTrack;
}

float Track::getDenivele(const Sens aSens) const
{
    float den = 0;
    for (vector<Segment*>::const_iterator it = fSegments.begin(); it != fSegments.end(); ++it)
        den += (**it).getDenivele(aSens == MONTANT ? Segment::MONTANT : Segment::DESCENDANT);
    return den;
}

const PointGPX* Track::premier(void) const
{
    if (fSegments.empty()) throw string("Aucun segment");
    return fSegments[0]->premier();
}

const PointGPX* Track::dernier(void) const
{
    if (fSegments.empty()) throw string("Aucun segment");
    return fSegments[fSegments.size() - 1]->dernier();
}

float Track::longueur(void) const
{
    float lon = 0;
    for (vector<Segment*>::const_iterator it = fSegments.begin(); it != fSegments.end(); ++it)
        lon += (**it).longueur();
    return lon;
}

