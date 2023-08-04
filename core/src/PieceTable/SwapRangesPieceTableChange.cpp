/*
    This file is part of the Okteta Core library, made within the KDE community.

    SPDX-FileCopyrightText: 2008 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#include "Okteta/PieceTable/SwapRangesPieceTableChange.hpp"

// lib
#include "Okteta/PieceTable/PieceTable.hpp"
//
#include <Okteta/ArrayChangeMetrics.hpp>

namespace KPieceTable {

SwapRangesPieceTableChange::~SwapRangesPieceTableChange() = default;

int SwapRangesPieceTableChange::type() const { return SwapRangesId; }

QString SwapRangesPieceTableChange::description() const
{
    return QObject::tr("Swap Ranges");
}

AddressRange SwapRangesPieceTableChange::apply(PieceTable* pieceTable) const
{
    pieceTable->swap(mFirstStart, mSecondRange);

    return AddressRange(mFirstStart, mSecondRange.end());
}

AddressRange SwapRangesPieceTableChange::revert(PieceTable* pieceTable) const
{
    pieceTable->swap(mFirstStart, AddressRange(mFirstStart + mSecondRange.width(), mSecondRange.end()));

    return AddressRange(mFirstStart, mSecondRange.end());
}

ArrayChangeMetrics SwapRangesPieceTableChange::metrics() const
{
    return ArrayChangeMetrics::asSwapping(mFirstStart, mSecondRange.start(), mSecondRange.width());
}

}
