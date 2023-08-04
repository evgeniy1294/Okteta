/*
    This file is part of the Okteta Core library, made within the KDE community.

    SPDX-FileCopyrightText: 2004, 2011 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#include "Okteta/ValueCodec.hpp"

// lib
#include "Okteta/Codecs/BinaryByteCodec.hpp"
#include "Okteta/Codecs/OctalByteCodec.hpp"
#include "Okteta/Codecs/DecimalByteCodec.hpp"
#include "Okteta/Codecs/HexadecimalByteCodec.hpp"
// Qt
#include <QString>

namespace Okteta {

ValueCodec::~ValueCodec() = default;

ValueCodec* ValueCodec::createCodec(ValueCoding valueCoding)
{
    ValueCodec* result;
    switch (valueCoding)
    {
    case DecimalCoding: result = new DecimalByteCodec(); break;
    case OctalCoding:   result = new OctalByteCodec();   break;
    case BinaryCoding:  result = new BinaryByteCodec();  break;
    case HexadecimalCoding:
    default:            result = new HexadecimalByteCodec();
    }
    return result;
}

unsigned int ValueCodec::decode(unsigned char* byte, const QString& digits, unsigned int pos) const
{
    const unsigned int oldPos = pos;
    const unsigned int left = digits.size() - pos;

    unsigned int d = encodingWidth();
    if (left < d) {
        d = left;
    }

    unsigned char result = 0;
    while (d > 0) {
        if (!appendDigit(&result, digits.at(pos).toLatin1())) { // TODO: use QChar.digitValue()
            break;
        }

        ++pos;
        --d;
    }

    *byte = result;
    return pos - oldPos;
}

}
