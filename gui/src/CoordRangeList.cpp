/*
    This file is part of the Okteta Gui library, made within the KDE community.

    SPDX-FileCopyrightText: 2003 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#include "Okteta/CoordRangeList.hpp"

namespace Okteta {

CoordRangeList::CoordRangeList() = default;

CoordRangeList::~CoordRangeList() = default;

void CoordRangeList::addCoordRange(const CoordRange& coordRange)
{
    if (!coordRange.isValid()) {
        return;
    }

    // we try to insert it by ascending indizes
    // if sections are overlapping we combine them
    Iterator it = begin();
    Iterator endIt = end();
    for (; it != endIt; ++it) {
        // TODO: add bufferwidth to rangelist so consecutive ranges can be joined, cmp sectionlist
        // is next CoordRange behind the new CoordRange?
        if (coordRange.endsBefore(*it)) {
            // put the new before it
            insert(it, coordRange);
            return;
        }

        // does the next CoordRange overlap?
        if ((*it).overlaps(coordRange)) {
            CoordRange mergedCoordRange(coordRange);
            // Start of the combined sections is the smaller one
            mergedCoordRange.extendStartTo((*it).start());
            // next we search all the overlapping sections and keep the highest end index
            Coord endCoord((*it).end());
            iterator it2 = it;
            for (++it2; it2 != endIt; ++it2) {
                if (coordRange.endsBefore((*it2).start())) {
                    break;
                }
                endCoord = (*it2).end();
            }

            // the higher end is the end of the combined CoordRange
            mergedCoordRange.extendEndTo(endCoord);
            // remove all overlapping sections
            it = erase(it, it2);
            // and instead insert the combined one
            insert(it, mergedCoordRange);
            return;
        }
    }

    // all others are before the new?
    if (it == endIt) {
        // add it at the end
        append(coordRange);
    }
}

}
