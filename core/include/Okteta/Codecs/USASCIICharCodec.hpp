/*
    This file is part of the Okteta Core library, made within the KDE community.

    SPDX-FileCopyrightText: 2014 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef OKTETA_USASCIICHARCODEC_HPP
#define OKTETA_USASCIICHARCODEC_HPP

#include "Okteta/export/oktetacore_cfg.hpp"

// lib
#include <Okteta/CharCodec.hpp>

namespace Okteta {

//
class OKTETACORE_EXPORT USASCIICharCodec : public CharCodec
{
public:
    USASCIICharCodec(const USASCIICharCodec&) = delete;
    USASCIICharCodec& operator=(const USASCIICharCodec&) = delete;

protected:
    USASCIICharCodec();

public: // CharCodec API
    Character decode(Byte byte) const override;
    bool encode(Byte* byte, const QChar& _char) const override;
    bool canEncode(const QChar& _char) const override;
    const QString& name() const override;

public:
    static USASCIICharCodec* create();
    static const QString& codecName();
};

inline USASCIICharCodec::USASCIICharCodec() = default;

inline USASCIICharCodec* USASCIICharCodec::create() { return new USASCIICharCodec(); }

}

#endif
