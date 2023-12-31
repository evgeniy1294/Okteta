/*
    This file is part of the Okteta Core library, made within the KDE community.

    SPDX-FileCopyrightText: 2004, 2011 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef OKTETA_EBCDIC1047CHARCODEC_HPP
#define OKTETA_EBCDIC1047CHARCODEC_HPP

#include "Okteta/export/oktetacore_cfg.hpp"

// lib
#include <CharCodec.hpp>

namespace Okteta {

//
class OKTETACORE_EXPORT EBCDIC1047CharCodec : public CharCodec
{
public:
    EBCDIC1047CharCodec(const EBCDIC1047CharCodec&) = delete;
    EBCDIC1047CharCodec& operator=(const EBCDIC1047CharCodec&) = delete;

protected:
    EBCDIC1047CharCodec();

public: // CharCodec API
    Character decode(Byte byte) const override;
    bool encode(Byte* byte, const QChar& _char) const override;
    bool canEncode(const QChar& _char) const override;
    const QString& name() const override;

public:
    static EBCDIC1047CharCodec* create();
    static const QString& codecName();
};

inline EBCDIC1047CharCodec::EBCDIC1047CharCodec() = default;

inline EBCDIC1047CharCodec* EBCDIC1047CharCodec::create() { return new EBCDIC1047CharCodec(); }

}

#endif
