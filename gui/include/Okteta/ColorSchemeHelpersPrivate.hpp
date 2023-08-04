#ifndef COLORSCHEME_P_H
#define COLORSCHEME_P_H

#include <QCoreApplication>
#include <QPalette>

#include <array>

namespace Okteta {

/*
static KSharedConfigPtr defaultConfig()
{
    // cache the value we'll return, since usually it's going to be the same value
    static thread_local KSharedConfigPtr config;
    // Read from the application's color scheme file (as set by KColorSchemeManager).
    // If unset, this is equivalent to openConfig() and the system scheme is used.
    const auto colorSchemePath = qApp->property("KDE_COLOR_SCHEME_PATH").toString();
    if (!config || config->name() != colorSchemePath) {
        config = KSharedConfig::openConfig(colorSchemePath);
    }
    return config;
}
*/

class StateEffects
{
public:
    explicit StateEffects(QPalette::ColorGroup state);
    ~StateEffects()
    {
    }

    QBrush brush(const QBrush &background) const;
    QBrush brush(const QBrush &foreground, const QBrush &background) const;

private:
    enum EffectTypes {
        Intensity,
        Color,
        Contrast,
        NEffectTypes,
    };

    enum IntensityEffects {
        IntensityNoEffect,
        IntensityShade,
        IntensityDarken,
        IntensityLighten,
        NIntensityEffects,
    };

    enum ColorEffects {
        ColorNoEffect,
        ColorDesaturate,
        ColorFade,
        ColorTint,
        NColorEffects,
    };

    enum ContrastEffects {
        ContrastNoEffect,
        ContrastFade,
        ContrastTint,
        NContrastEffects,
    };

    int _effects[NEffectTypes];
    double _amount[NEffectTypes];
    QColor _color;
};

} // namespace Okteta

#endif // COLORSCHEME_P_H
