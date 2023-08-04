/*
    This file is part of the Okteta Core library, made within the KDE community.

    SPDX-FileCopyrightText: 2009 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef OKTETA_LINEPOSITIONRANGE_HPP
#define OKTETA_LINEPOSITIONRANGE_HPP

// lib
#include "Okteta/LinePosition.hpp"

// Okteta core
#include <Okteta/NumberRange.hpp>

namespace Okteta {

using LinePositionRange = NumberRange<LinePosition, LinePositionSize>;

}

#endif
