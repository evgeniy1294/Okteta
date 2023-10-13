/*
    This file is part of the Okteta Core library, made within the KDE community.

    SPDX-FileCopyrightText: 2004, 2011 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef OKTETA_HEXADECIMALBYTECODEC_HPP
#define OKTETA_HEXADECIMALBYTECODEC_HPP

#include "Okteta/export/oktetacore_cfg.hpp"

// lib
#include <Okteta/ValueCodec.hpp>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
class QChar;
#endif

namespace Okteta {

class OKTETACORE_EXPORT HexadecimalByteCodec : public ValueCodec
{
public:
    explicit HexadecimalByteCodec(bool lowerCaseDigits = false);
    HexadecimalByteCodec(const HexadecimalByteCodec&) = delete;
    HexadecimalByteCodec& operator=(const HexadecimalByteCodec&) = delete;

public:
    bool setLowerCaseDigits(bool lowerCaseDigits);
    bool isLowerCaseDigits() const;

public: // ValueCodec API
    unsigned int encodingWidth() const override;
    Byte digitsFilledLimit() const override;

    void encode(QString* digits, unsigned int pos, Byte byte) const override;
    void encodeShort(QString* digits, unsigned int pos, Byte byte) const override;
    bool appendDigit(Byte* byte, unsigned char digit) const override;
    void removeLastDigit(Byte* byte) const override;
    bool isValidDigit(unsigned char digit) const override;
    bool turnToValue(unsigned char* digit) const override;

private:
    const QChar* mDigits;
};

}

#endif
