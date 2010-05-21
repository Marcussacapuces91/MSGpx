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
    //dtor
}

Track* Track::parser(TiXmlElement& aElement)
{
    TiXmlElement *const pName = dynamic_cast<TiXmlElement *const>(aElement.FirstChild("name"));
    TiXmlElement *const pDesc = dynamic_cast<TiXmlElement *const>(aElement.FirstChild("desc"));
    Track *const pTrack = new Track(pName ? pName->GetText() : "", pDesc ? pDesc->GetText() : "");
    assert(pTrack);
    for (TiXmlNode* pTrkSeg = aElement.FirstChild("trkseg"); pTrkSeg; pTrkSeg = pTrkSeg->NextSibling() ) {
        vector<Point> points;
        for (TiXmlNode* pTrkPt = pTrkSeg->FirstChild("trkpt"); pTrkPt; pTrkPt = pTrkPt->NextSibling()) {
            TiXmlElement *const pElement = pTrkPt->ToElement();
            if (!pElement) {
                delete pTrack;
                throw string("Element <trkpt> attendu");
            }
            Point point;
            double dbl = 0;
            switch (pElement->QueryDoubleAttribute("lat", &dbl)) {
                case TIXML_SUCCESS :
                    point.lat = dbl;
                    break;
                case TIXML_WRONG_TYPE :
                    delete pTrack;
                    throw string("Type incorrect de l'attribut 'lat'");
                    break;
                case TIXML_NO_ATTRIBUTE :
                    delete pTrack;
                    throw string("Attribut 'lat' manquant");
                    break;
            }
            switch (pElement->QueryDoubleAttribute("lon", &dbl)) {
                case TIXML_SUCCESS :
                    point.lon = dbl;
                    break;
                case TIXML_WRONG_TYPE :
                    delete pTrack;
                    throw string("Type incorrect de l'attribut 'lon'");
                    break;
                case TIXML_NO_ATTRIBUTE :
                    delete pTrack;
                    throw string("Attribut 'lon' manquant");
                    break;
            }

            TiXmlElement *const pE1 = dynamic_cast<TiXmlElement *const>(pElement->FirstChild("ele"));
            if (!pE1) {
                delete pTrack;
                throw string("Element <ele> attendu");
            }
            istringstream iss(pE1->GetText());
            iss >> point.alt;

            TiXmlElement *const pE2 = dynamic_cast<TiXmlElement *const>(pElement->FirstChild("time"));
            if (!pE2) {
                delete pTrack;
                throw string("Element <time> attendu");
            }
            point.time = pE2->GetText();

            points.push_back(point);
        }
        pTrack->fSegments.push_back(points);
    }
    return pTrack;
}

float Track::getDenivelePositif(void) const
{
    float den = 0;
    for (vector< vector<Point> >::const_iterator i = fSegments.begin(); i != fSegments.end(); ++i) {
        const vector<Point> segment = *i;
        if (segment.size() > 1) {
            for (unsigned j = 1; j < segment.size(); ++j) {
                if (segment[j-1].alt < segment[j].alt)
                    den += segment[j].alt - segment[j-1].alt;
            }
        }
    }
    return den;
}

float Track::getDeniveleNegatif(void) const
{
    float den = 0;
    for (vector< vector<Point> >::const_iterator i = fSegments.begin(); i != fSegments.end(); ++i) {
        const vector<Point> segment = *i;
        if (segment.size() > 1) {
            for (unsigned j = 1; j < segment.size(); ++j) {
                if (segment[j-1].alt > segment[j].alt)
                    den += segment[j-1].alt - segment[j].alt;
            }
        }
    }
    return den;
}
