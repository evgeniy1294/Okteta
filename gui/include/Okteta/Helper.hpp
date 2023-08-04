/*
    This file is part of the Okteta Gui library, made within the KDE community.

    SPDX-FileCopyrightText: 2003, 2008-2009 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef OKTETA_HELPER
#define OKTETA_HELPER

#include <Okteta/ColorScheme.hpp>

// Okteta core
#include <Okteta/Character.hpp>

// Qt
#include <QColor>

// temporary solution until syntax highlighting is implemented
static inline QColor colorForChar(const Okteta::Character byteChar)
{
    return byteChar.isUndefined() ? Qt::yellow :
           byteChar.isPunct() ?     Qt::red :
           byteChar.isPrint() ?     Qt::black :
           (byteChar == QLatin1Char(0x0A) || byteChar == QLatin1Char(0x0D)) ?
                                    Qt::darkCyan :
                                    Qt::blue;
}

static inline Okteta::ColorScheme::ForegroundRole foregroundRoleForChar(const Okteta::Character byteChar)
{
    return byteChar.isUndefined() ? Okteta::ColorScheme::NegativeText :
           byteChar.isPunct() ?     Okteta::ColorScheme::InactiveText :
           byteChar.isPrint() ?     Okteta::ColorScheme::NormalText :
           (byteChar == QLatin1Char(0x0A) || byteChar == QLatin1Char(0x0D)) ?
                                    Okteta::ColorScheme::VisitedText :
                                    Okteta::ColorScheme::ActiveText;
}

#endif
