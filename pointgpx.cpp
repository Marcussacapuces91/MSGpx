/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#include "pointgpx.h"
#include <sstream>

using namespace std;

PointGPX* PointGPX::parser(TiXmlElement& aElement)
{
    double lon, lat = 0;
    float ele = 0;
    string name, link, time;
    float hdop, vdop, pdop = 0;

    switch (aElement.QueryDoubleAttribute("lat", &lat)) {
        case TIXML_SUCCESS :
            break;
        case TIXML_WRONG_TYPE :
            throw string("Type incorrect de l'attribut 'lat'");
            break;
        case TIXML_NO_ATTRIBUTE :
            throw string("Attribut 'lat' manquant");
            break;
    }

    switch (aElement.QueryDoubleAttribute("lon", &lon)) {
        case TIXML_SUCCESS :
            break;
        case TIXML_WRONG_TYPE :
            throw string("Type incorrect de l'attribut 'lon'");
            break;
        case TIXML_NO_ATTRIBUTE :
            throw string("Attribut 'lon' manquant");
            break;
    }

    TiXmlNode *const pN1 = aElement.FirstChild("ele");
    if (pN1 && pN1->ToElement()) {
        istringstream iss1(pN1->ToElement()->GetText());
        iss1 >> ele;
    }

    TiXmlNode *const pN2 = aElement.FirstChild("time");
    if (pN2 && pN2->ToElement()) {
        time = pN2->ToElement()->GetText();
    }

    TiXmlNode *const pN3 = aElement.FirstChild("name");
    if (pN3 && pN3->ToElement()) {
        name = pN3->ToElement()->GetText();
    }

    TiXmlNode *const pN4 = aElement.FirstChild("link");
    if (pN4 && pN4->ToElement()) {
        const char *const p = pN4->ToElement()->Attribute("href");
        if (p) link = string(p);
    }

    TiXmlNode *const pN5 = aElement.FirstChild("hdop");
    if (pN5 && pN5->ToElement()) {
        istringstream iss5(pN5->ToElement()->GetText());
        iss5 >> hdop;
    }

    TiXmlNode *const pN6 = aElement.FirstChild("vdop");
    if (pN6 && pN6->ToElement()) {
        istringstream iss6(pN6->ToElement()->GetText());
        iss6 >> vdop;
    }

    TiXmlNode *const pN7 = aElement.FirstChild("pdop");
    if (pN7 && pN7->ToElement()) {
        istringstream iss7(pN7->ToElement()->GetText());
        iss7 >> pdop;
    }

    return new PointGPX(lat, lon, ele, time, name, link, hdop, vdop, pdop);
}

