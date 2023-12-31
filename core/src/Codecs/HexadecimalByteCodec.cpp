/*
    This file is part of the Okteta Core library, made within the KDE community.

    SPDX-FileCopyrightText: 2004, 2011 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#include "Okteta/Codecs/HexadecimalByteCodec.hpp"

// Qt
#include <QString>

namespace Okteta {

static constexpr QChar upperCaseDigits[16] =
{   // '0',                  '1',             '2',              '3'
    char16_t(0x0030), char16_t(0x0031), char16_t(0x0032), char16_t(0x0033),
    //    '4',               '5',             '6',              '7'
    char16_t(0x0034), char16_t(0x0035), char16_t(0x0036), char16_t(0x0037),
    //  '8',                 '9',             'A',              'B',
    char16_t(0x0038), char16_t(0x0039), char16_t(0x0041), char16_t(0x0042),
    //    'C',               'D',              'E',              'F'
    char16_t(0x0043), char16_t(0x0044), char16_t(0x0045), char16_t(0x0046)
};
static constexpr QChar lowerCaseDigits[16] =
{   // '0',                  '1',             '2',              '3'
    char16_t(0x0030), char16_t(0x0031), char16_t(0x0032), char16_t(0x0033),
    //    '4',               '5',             '6',              '7'
    char16_t(0x0034), char16_t(0x0035), char16_t(0x0036), char16_t(0x0037),
    //  '8',                 '9',              'a',              'b',
    char16_t(0x0038), char16_t(0x0039), char16_t(0x0061), char16_t(0x0062),
    //  'c',                 'd',              'e',              'f'
    char16_t(0x0063), char16_t(0x0064), char16_t(0x0065), char16_t(0x0066)
};
static constexpr Byte hexadecimalDigitsFilledLimit = 16;

HexadecimalByteCodec::HexadecimalByteCodec(bool useLowerCaseDigits)
    : mDigits(useLowerCaseDigits ? lowerCaseDigits : upperCaseDigits)
{
}

bool HexadecimalByteCodec::setLowerCaseDigits(bool useLowerCaseDigits)
{
    const QChar* const digits = useLowerCaseDigits ? lowerCaseDigits : upperCaseDigits;

    if (digits == mDigits) {
        return false;
    }

    mDigits = digits;
    return true;
}

bool HexadecimalByteCodec::isLowerCaseDigits() const { return mDigits == lowerCaseDigits; }

unsigned int HexadecimalByteCodec::encodingWidth() const { return 2; }
Byte HexadecimalByteCodec::digitsFilledLimit() const { return hexadecimalDigitsFilledLimit; }

void HexadecimalByteCodec::encode(QString* digits, unsigned int pos, Byte byte) const
{
    const int minSizeNeeded = pos + 2;
    if (digits->size() < minSizeNeeded) {
        digits->resize(minSizeNeeded);
    }

    (*digits)[pos++] = mDigits[byte >> 4];
    (*digits)[pos] = mDigits[byte & 0x0F];
}

void HexadecimalByteCodec::encodeShort(QString* digits, unsigned int pos, Byte byte) const
{
    const int encodingLength = (byte > 0xF) ? 2 : 1;
    const int minSizeNeeded = pos + encodingLength;
    if (digits->size() < minSizeNeeded) {
        digits->resize(minSizeNeeded);
    }

    unsigned char digitValue = byte >> 4;

    if (digitValue > 0) {
        (*digits)[pos++] = mDigits[digitValue];
    }
    (*digits)[pos] = mDigits[byte & 0x0F];
}

static inline constexpr bool isValidBigDigit(unsigned char digit)
{
    return ('A' <= digit && digit <= 'F');
}

static inline constexpr bool isValidSmallDigit(unsigned char digit)
{
    return ('a' <= digit && digit <= 'f');
}

static inline constexpr bool isValidDecimalDigit(unsigned char digit)
{
    return ('0' <= digit && digit <= '9');
}

bool HexadecimalByteCodec::isValidDigit(unsigned char digit) const
{
    return isValidDecimalDigit(digit) || isValidBigDigit(digit) || isValidSmallDigit(digit);
}

bool HexadecimalByteCodec::turnToValue(unsigned char* digit) const
{
    if (isValidDecimalDigit(*digit)) {
        *digit -= '0';
    } else if (isValidBigDigit(*digit)) {
        *digit -= 'A' - 10;
    } else if (isValidSmallDigit(*digit)) {
        *digit -= 'a' - 10;
    } else {
        return false;
    }

    return true;
}

bool HexadecimalByteCodec::appendDigit(Byte* byte, unsigned char digit) const
{
    if (turnToValue(&digit)) {
        Byte _byte = *byte;
        if (_byte < hexadecimalDigitsFilledLimit) {
            _byte <<= 4;
            _byte += digit;
            *byte = _byte;
            return true;
        }
    }
    return false;
}

void HexadecimalByteCodec::removeLastDigit(Byte* byte) const
{
    *byte >>= 4;
}

}
