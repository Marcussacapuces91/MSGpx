/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#include "segment.h"

Segment::Segment()
{
    //ctor
}

Segment::~Segment()
{
    for (vector<PointGPX*>::const_iterator it = fPoints.begin(); it != fPoints.end(); ++it) delete *it;
}

float Segment::getDenivele(const Sens aSens) const
{
    float den = 0;
    if (fPoints.size() > 1) {
        for (unsigned i = 1; i < fPoints.size(); ++i) {
            if (fPoints[i-1]->ele() * aSens < fPoints[i]->ele() * aSens)
                den += fPoints[i]->ele() - fPoints[i-1]->ele();
        }
    }
    return den * aSens;
}

const PointGPX* Segment::premier(void) const
{
    if (fPoints.empty()) throw string("Aucun point");
    return fPoints[0];
}

const PointGPX* Segment::dernier(void) const
{
    if (fPoints.empty()) throw string("Aucun point");
    return fPoints[fPoints.size() - 1];
}

float Segment::longueur(void) const
{
    float lon = 0;
    if (fPoints.size() > 1) {
        for (unsigned i = 1; i < fPoints.size(); ++i)
            lon += fPoints[i-1]->distance(*fPoints[i]);
    }
    return lon;
}


