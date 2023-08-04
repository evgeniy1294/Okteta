#include "Okteta/ColorScheme.hpp"
#include "Okteta/ColorSchemeHelpersPrivate.hpp"
#include "Okteta/GlobalConfigStorage.hpp"

#include "Okteta/Colors/kcolorutils.h"

#include <QBrush>
#include <QColor>
#include <QLatin1String>

#include <utility>

Okteta::StateEffects::StateEffects(QPalette::ColorGroup state)
    : _color(0, 0, 0, 0) //, _chain(0) not needed yet
{
    QJsonObject globalConfig;
        GlobalConfigStorage::Instance().config(globalConfig);

    auto colorEffects = globalConfig.value(QStringLiteral("ColorEffects")).toObject();
    QString group;
    if (state == QPalette::Disabled) {
        group = QLatin1String("Disabled");
    } else if (state == QPalette::Inactive) {
        group = QLatin1String("Inactive");
    }

    for (auto &effect : _effects) {
        effect = 0;
    }

    if (!group.isEmpty()) {
        auto cfg = globalConfig.value(group).toObject();

        const bool enabledByDefault = (state == QPalette::Disabled);
        if (cfg.value(QStringLiteral("Enable")).toBool(enabledByDefault)) {
            _effects[Intensity] = cfg.value(QLatin1String("IntensityEffect")).toInt((int)(state == QPalette::Disabled ? IntensityDarken : IntensityNoEffect));
            _effects[Color] = cfg.value(QLatin1String("ColorEffect")).toInt((int)(state == QPalette::Disabled ? ColorNoEffect : ColorDesaturate));
            _effects[Contrast] = cfg.value(QLatin1String("ContrastEffect")).toInt((int)(state == QPalette::Disabled ? ContrastFade : ContrastTint));
            _amount[Intensity] = cfg.value(QLatin1String("IntensityAmount")).toDouble(state == QPalette::Disabled ? 0.10 : 0.0);
            _amount[Color] = cfg.value(QLatin1String("ColorAmount")).toDouble(state == QPalette::Disabled ? 0.0 : -0.9);
            _amount[Contrast] = cfg.value(QLatin1String("ContrastAmount")).toDouble(state == QPalette::Disabled ? 0.65 : 0.25);

            if (_effects[Color] > ColorNoEffect) {
                auto color_str = cfg.value(QLatin1String("Color")).toString();
                _color = color_str.isEmpty() ? (state == QPalette::Disabled ? QColor(56, 56, 56) : QColor(112, 111, 110)) : QColor(color_str);
            }
        }
    }
}

QBrush Okteta::StateEffects::brush(const QBrush &background) const
{
    QColor color = background.color(); // TODO - actually work on brushes
    switch (_effects[Intensity]) {
    case IntensityShade:
        color = KColorUtils::shade(color, _amount[Intensity]);
        break;
    case IntensityDarken:
        color = KColorUtils::darken(color, _amount[Intensity]);
        break;
    case IntensityLighten:
        color = KColorUtils::lighten(color, _amount[Intensity]);
        break;
    }
    switch (_effects[Color]) {
    case ColorDesaturate:
        color = KColorUtils::darken(color, 0.0, 1.0 - _amount[Color]);
        break;
    case ColorFade:
        color = KColorUtils::mix(color, _color, _amount[Color]);
        break;
    case ColorTint:
        color = KColorUtils::tint(color, _color, _amount[Color]);
        break;
    }
    return QBrush(color);
}

QBrush Okteta::StateEffects::brush(const QBrush &foreground, const QBrush &background) const
{
    QColor color = foreground.color(); // TODO - actually work on brushes
    QColor bg = background.color();
    // Apply the foreground effects
    switch (_effects[Contrast]) {
    case ContrastFade:
        color = KColorUtils::mix(color, bg, _amount[Contrast]);
        break;
    case ContrastTint:
        color = KColorUtils::tint(color, bg, _amount[Contrast]);
        break;
    }
    // Now apply global effects
    return brush(color);
}

struct SerializedColors {
    QColor NormalBackground;
    QColor AlternateBackground;
    QColor NormalText;
    QColor InactiveText;
    QColor ActiveText;
    QColor LinkText;
    QColor VisitedText;
    QColor NegativeText;
    QColor NeutralText;
    QColor PositiveText;
};

struct DecorationColors {
    QColor Focus;
    QColor Hover;
};

// clang-format off
// These numbers come from the default color scheme which is currently
// Breeze Light ([breeze repo]/colors/BreezeLight.colors)
static const SerializedColors defaultViewColors = {
    { 255, 255, 255 }, // Background
    { 247, 247, 247 }, // Alternate
    {  35,  38, 41  }, // Normal
    { 112, 125, 138 }, // Inactive
    {  61, 174, 233 }, // Active
    {  41, 128, 185 }, // Link
    { 155,  89, 182 }, // Visited
    { 218,  68,  83 }, // Negative
    { 246, 116,   0 }, // Neutral
    {  39, 174,  96 }  // Positive
};

static const SerializedColors defaultWindowColors = {
    { 239, 240, 241 }, // Background
    { 227, 229, 231 }, // Alternate
    {  35,  38, 41  }, // Normal
    { 112, 125, 138 }, // Inactive
    {  61, 174, 233 }, // Active
    {  41, 128, 185 }, // Link
    { 155,  89, 182 }, // Visited
    { 218,  68,  83 }, // Negative
    { 246, 116,   0 }, // Neutral
    {  39, 174,  96 }  // Positive
};

static const SerializedColors defaultButtonColors = {
    { 252, 252, 252 }, // Background
    { 163, 212, 250 }, // Alternate
    {  35,  38, 41  }, // Normal
    { 112, 125, 138 }, // Inactive
    {  61, 174, 233 }, // Active
    {  41, 128, 185 }, // Link
    { 155,  89, 182 }, // Visited
    { 218,  68,  83 }, // Negative
    { 246, 116,   0 }, // Neutral
    {  39, 174,  96 }  // Positive
};

static const SerializedColors defaultSelectionColors = {
    {  61, 174, 233 }, // Background
    { 163, 212, 250 }, // Alternate
    { 255, 255, 255 }, // Normal
    { 112, 125, 138 }, // Inactive
    { 255, 255, 255 }, // Active
    { 253, 188,  75 }, // Link
    { 155,  89, 182 }, // Visited
    { 176,  55,  69 }, // Negative
    { 198,  92,   0 }, // Neutral
    {  23, 104,  57 }  // Positive
};

static const SerializedColors defaultTooltipColors = {
    { 247, 247, 247 }, // Background
    { 239, 240, 241 }, // Alternate
    {  35,  38,  41 }, // Normal
    { 112, 125, 138 }, // Inactive
    {  61, 174, 233 }, // Active
    {  41, 128, 185 }, // Link
    { 155,  89, 182 }, // Visited
    { 218,  68,  83 }, // Negative
    { 246, 116,   0 }, // Neutral
    {  39, 174,  96 }  // Positive
};

static const SerializedColors defaultComplementaryColors = {
    {  42,  46,  50 }, // Background
    {  27,  30,  32 }, // Alternate
    { 252, 252, 252 }, // Normal
    { 161, 169, 177 }, // Inactive
    {  61, 174, 233 }, // Active
    {  29, 153, 243 }, // Link
    { 155,  89, 182 }, // Visited
    { 218,  68,  83 }, // Negative
    { 246, 116,   0 }, // Neutral
    {  39, 174,  96 }  // Positive
};

static const SerializedColors defaultHeaderColors = {
    { 222, 224, 226 }, // Background
    { 239, 240, 241 }, // Alternate
    {  35,  38,  41 }, // Normal
    { 112, 125, 138 }, // Inactive
    {  61, 174, 233 }, // Active
    {  41, 128, 185 }, // Link
    { 155,  89, 182 }, // Visited
    { 218,  68,  83 }, // Negative
    { 246, 116,   0 }, // Neutral
    {  39, 174,  96 }  // Positive
};

static const DecorationColors defaultDecorationColors = {
    {  61, 174, 233 }, // Focus
    { 147, 206, 233 }, // Hover
};

namespace Okteta {

class ColorSchemePrivate : public QSharedData
{
public:
    explicit ColorSchemePrivate(QPalette::ColorGroup state, ColorScheme::ColorSet set);
    ~ColorSchemePrivate() { }

    QBrush background(ColorScheme::BackgroundRole) const;
    QBrush foreground(ColorScheme::ForegroundRole) const;
    QBrush decoration(ColorScheme::DecorationRole) const;
    qreal contrast() const;

    struct Brushes {
        std::array<QBrush, ColorScheme::NForegroundRoles> fg;
        std::array<QBrush, ColorScheme::NBackgroundRoles> bg;
        std::array<QBrush, ColorScheme::NDecorationRoles> deco;

        bool operator==(const Brushes &b) const
        {
            return this == &b || (fg == b.fg && bg == b.bg && deco == b.deco);
        }
    } _brushes;

    qreal _contrast;
};

static SerializedColors loadSerializedColors(const QJsonObject& group, const SerializedColors &defaults)
{
    SerializedColors loadedColors;

    auto colorStr = group.value(QLatin1String("ForegroundNormal")).toString();
    loadedColors.NormalText = colorStr.isEmpty() ? defaults.NormalText : QColor(colorStr);

    colorStr = group.value(QLatin1String("ForegroundInactive")).toString();
    loadedColors.InactiveText = colorStr.isEmpty() ? defaults.InactiveText : QColor(colorStr);

    colorStr = group.value(QLatin1String("ForegroundActive")).toString();
    loadedColors.ActiveText = colorStr.isEmpty() ? defaults.ActiveText : QColor(colorStr);

    colorStr = group.value(QLatin1String("ForegroundLink")).toString();
    loadedColors.LinkText = colorStr.isEmpty() ? defaults.LinkText : QColor(colorStr);

    colorStr = group.value(QLatin1String("ForegroundVisited")).toString();
    loadedColors.VisitedText = colorStr.isEmpty() ? defaults.VisitedText : QColor(colorStr);

    colorStr = group.value(QLatin1String("ForegroundNegative")).toString();
    loadedColors.NegativeText = colorStr.isEmpty() ? defaults.NegativeText : QColor(colorStr);

    colorStr = group.value(QLatin1String("ForegroundNeutral")).toString();
    loadedColors.NeutralText = colorStr.isEmpty() ? defaults.NeutralText : QColor(colorStr);

    colorStr = group.value(QLatin1String("ForegroundPositive")).toString();
    loadedColors.PositiveText = colorStr.isEmpty() ? defaults.PositiveText : QColor(colorStr);

    colorStr = group.value(QLatin1String("BackgroundNormal")).toString();
    loadedColors.NormalBackground = colorStr.isEmpty() ? defaults.NormalBackground : QColor(colorStr);

    colorStr = group.value(QLatin1String("BackgroundAlternate")).toString();
    loadedColors.AlternateBackground = colorStr.isEmpty() ? defaults.AlternateBackground : QColor(colorStr);

    return loadedColors;
}

static SerializedColors loadSerializedColors(const QLatin1String& group, const SerializedColors &defaults)
{
    QJsonObject globalConfig;
        GlobalConfigStorage::Instance().config(globalConfig);

    auto colorsObj = globalConfig.value(QLatin1String("Colors")).toObject();
    auto colorGroup = colorsObj.value(group).toObject();

    return loadSerializedColors(colorGroup, defaults);
}

static DecorationColors loadDecorationColors(const QJsonObject& group, const DecorationColors& defaults)
{
    DecorationColors colors;

    auto colorStr = group.value(QLatin1String("DecorationFocus")).toString();
    colors.Focus = colorStr.isEmpty() ? defaults.Focus : QColor(colorStr);

    colorStr = group.value(QStringLiteral("DecorationHover")).toString();
    colors.Hover = colorStr.isEmpty() ? defaults.Hover : QColor(colorStr);

    return colors;
}

static DecorationColors loadDecorationColors(const QLatin1String& group, const DecorationColors& defaults)
{
    QJsonObject globalConfig;
        GlobalConfigStorage::Instance().config(globalConfig);

    auto colorsObj = globalConfig.value(QLatin1String("Colors")).toObject();
    auto colorGroup = colorsObj.value(group).toObject();

    return loadDecorationColors(colorGroup, defaults);
}

} // namespace Okteta

Okteta::ColorSchemePrivate::ColorSchemePrivate(QPalette::ColorGroup state, ColorScheme::ColorSet set)
{
    QJsonObject globalConfig;
        GlobalConfigStorage::Instance().config(globalConfig);
            auto colorEffects = globalConfig.value(QStringLiteral("ColorEffects")).toObject();
            auto colorsObj = globalConfig.value(QLatin1String("Colors")).toObject();

    QLatin1String groupName;
    SerializedColors defaultColors;
    DecorationColors defaultDecoColors = defaultDecorationColors;
    QBrush tint;
    switch (set) {
    case ColorScheme::Window:
        groupName = QLatin1String("Window");
        defaultColors = defaultWindowColors;
        break;
    case ColorScheme::Button:
        groupName = QLatin1String("Button");
        defaultColors = defaultButtonColors;
        break;
    case ColorScheme::Selection: {
        const auto inactiveEffectGroup = colorEffects.value(QLatin1String("Inactive")).toObject();
        const bool inactiveSelectionEffect =
                inactiveEffectGroup.value(QLatin1String("ChangeSelectionColor")).toBool(
                    inactiveEffectGroup.value(QLatin1String("Enable")).toBool(true)
                );

        // if enabled, inactive/disabled uses Window colors instead, ala gtk
        // ...except tinted with the Selection:NormalBackground color so it looks more like selection
        if (state == QPalette::Active || (state == QPalette::Inactive && !inactiveSelectionEffect)) {
            groupName = QLatin1String("Selection");
           defaultColors = defaultSelectionColors;
        } else if (state == QPalette::Inactive) {
            groupName = QLatin1String("Window");
            defaultColors = defaultWindowColors;
            tint = ColorSchemePrivate(QPalette::Active, ColorScheme::Selection)._brushes.bg[ColorScheme::NormalBackground];
        } else { // disabled (...and still want this branch when inactive+disabled exists)
            groupName = QLatin1String("Window");
            defaultColors = defaultWindowColors;
        }
    } break;
    case ColorScheme::Tooltip:
        groupName = QLatin1String("Tooltip");
        defaultColors = defaultTooltipColors;
        break;
    case ColorScheme::Complementary:
        groupName = QLatin1String("Complementary");
        defaultColors = defaultComplementaryColors;
        break;
    case ColorScheme::Header:
        groupName = QLatin1String("Header");
        defaultColors = loadSerializedColors(QLatin1String("Window"), defaultHeaderColors);
        defaultDecoColors = loadDecorationColors(QLatin1String("Window"), defaultDecorationColors);
        break;
    case ColorScheme::NColorSets:
        qWarning() << "ColorSet::NColorSets is not a valid color set value to pass to KColorScheme::KColorScheme";
        [[fallthrough]];
    case ColorScheme::View:
        groupName = QLatin1String("View");
        defaultColors = defaultViewColors;
        break;
    }

    auto colorsGroup =  colorsObj.value(groupName).toObject();
    bool hasInactivePalette = false;
    if (state == QPalette::Inactive) {
        auto inactiveGroup = colorsGroup.value(QLatin1String("Inactive"));
        if (inactiveGroup.isObject()) {
            colorsGroup = inactiveGroup.toObject();
            hasInactivePalette = true;
        }
    }

    _contrast = ColorScheme::contrastF(/*config*/);

     const SerializedColors loadedColors = loadSerializedColors(colorsGroup, defaultColors);
     const DecorationColors loadedDecoColors = loadDecorationColors(colorsGroup, defaultDecoColors);

    _brushes.fg[ColorScheme::NormalText] = loadedColors.NormalText;
    _brushes.fg[ColorScheme::InactiveText] = loadedColors.InactiveText;
    _brushes.fg[ColorScheme::ActiveText] = loadedColors.ActiveText;
    _brushes.fg[ColorScheme::LinkText] = loadedColors.LinkText;
    _brushes.fg[ColorScheme::VisitedText] = loadedColors.VisitedText;
    _brushes.fg[ColorScheme::NegativeText] = loadedColors.NegativeText;
    _brushes.fg[ColorScheme::NeutralText] = loadedColors.NeutralText;
    _brushes.fg[ColorScheme::PositiveText] = loadedColors.PositiveText;

    _brushes.bg[ColorScheme::NormalBackground] = loadedColors.NormalBackground;
    _brushes.bg[ColorScheme::AlternateBackground] = loadedColors.AlternateBackground;

    _brushes.deco[ColorScheme::FocusColor] = loadedDecoColors.Focus;
    _brushes.deco[ColorScheme::HoverColor] = loadedDecoColors.Hover;

    if (tint != Qt::NoBrush) {
        // adjustment
        _brushes.bg[ColorScheme::NormalBackground] =
            KColorUtils::tint(_brushes.bg[ColorScheme::NormalBackground].color(), tint.color(), 0.4);
        _brushes.bg[ColorScheme::AlternateBackground] =
            KColorUtils::tint(_brushes.bg[ColorScheme::AlternateBackground].color(), tint.color(), 0.4);
    }

    // apply state adjustments
    if (state != QPalette::Active || (state == QPalette::Inactive && !hasInactivePalette)) {
        StateEffects effects(state);
        for (auto &fg : _brushes.fg) {
            fg = effects.brush(fg, _brushes.bg[ColorScheme::NormalBackground]);
        }
        for (auto &deco : _brushes.deco) {
            deco = effects.brush(deco, _brushes.bg[ColorScheme::NormalBackground]);
        }
        _brushes.bg[ColorScheme::NormalBackground] = effects.brush(_brushes.bg[ColorScheme::NormalBackground]);
        _brushes.bg[ColorScheme::AlternateBackground] = effects.brush(_brushes.bg[ColorScheme::AlternateBackground]);
    }

    // calculated backgrounds
    _brushes.bg[ColorScheme::ActiveBackground] =
        KColorUtils::tint(_brushes.bg[ColorScheme::NormalBackground].color(),
                          _brushes.fg[ColorScheme::ActiveText].color());
    _brushes.bg[ColorScheme::LinkBackground] =
        KColorUtils::tint(_brushes.bg[ColorScheme::NormalBackground].color(),
                          _brushes.fg[ColorScheme::LinkText].color());
    _brushes.bg[ColorScheme::VisitedBackground] =
        KColorUtils::tint(_brushes.bg[ColorScheme::NormalBackground].color(),
                          _brushes.fg[ColorScheme::VisitedText].color());
    _brushes.bg[ColorScheme::NegativeBackground] =
        KColorUtils::tint(_brushes.bg[ColorScheme::NormalBackground].color(),
                          _brushes.fg[ColorScheme::NegativeText].color());
    _brushes.bg[ColorScheme::NeutralBackground] =
        KColorUtils::tint(_brushes.bg[ColorScheme::NormalBackground].color(),
                          _brushes.fg[ColorScheme::NeutralText].color());
    _brushes.bg[ColorScheme::PositiveBackground] =
        KColorUtils::tint(_brushes.bg[ColorScheme::NormalBackground].color(),
                          _brushes.fg[ColorScheme::PositiveText].color());
}

QBrush Okteta::ColorSchemePrivate::background(ColorScheme::BackgroundRole role) const
{
    if (role >= ColorScheme::NormalBackground && role < ColorScheme::NBackgroundRoles) {
        return _brushes.bg[role];
    } else {
        return _brushes.bg[ColorScheme::NormalBackground];
    }
}

QBrush Okteta::ColorSchemePrivate::foreground(ColorScheme::ForegroundRole role) const
{
    if (role >= ColorScheme::NormalText && role < ColorScheme::NForegroundRoles) {
        return _brushes.fg[role];
    } else {
        return _brushes.fg[ColorScheme::NormalText];
    }
}

QBrush Okteta::ColorSchemePrivate::decoration(ColorScheme::DecorationRole role) const
{
    if (role >= ColorScheme::FocusColor && role < ColorScheme::NDecorationRoles) {
        return _brushes.deco[role];
    } else {
        return _brushes.deco[ColorScheme::FocusColor];
    }
}

qreal Okteta::ColorSchemePrivate::contrast() const
{
    return _contrast;
}

Okteta::ColorScheme::ColorScheme(const ColorScheme &) = default;
Okteta::ColorScheme &Okteta::ColorScheme::operator=(const ColorScheme &) = default;
Okteta::ColorScheme::ColorScheme(ColorScheme &&) = default;
Okteta::ColorScheme &Okteta::ColorScheme::operator=(ColorScheme &&) = default;
Okteta::ColorScheme::~ColorScheme() = default;

Okteta::ColorScheme::ColorScheme(QPalette::ColorGroup state, ColorSet set)
    : d(new ColorSchemePrivate(state, set))
{
}

bool Okteta::ColorScheme::operator==(const ColorScheme &other) const
{
    return d == other.d
        || (d->_contrast == other.d->_contrast
            && d->_brushes == other.d->_brushes)
    ;
}

qreal Okteta::ColorScheme::contrastF()
{
/*
    KConfigGroup g(config ? config : defaultConfig(), "KDE");
    return 0.1 * g.readEntry("contrast", 7);
*/
    return 0.7;
}

QBrush Okteta::ColorScheme::background(BackgroundRole role) const
{
    return d->background(role);
}

QBrush Okteta::ColorScheme::foreground(ForegroundRole role) const
{
    return d->foreground(role);
}

QBrush Okteta::ColorScheme::decoration(DecorationRole role) const
{
    return d->decoration(role);
}

QColor Okteta::ColorScheme::shade(ShadeRole role) const
{
    return shade(background().color(), role, d->contrast());
}

QColor Okteta::ColorScheme::shade(const QColor &color, ShadeRole role)
{
    return shade(color, role, ColorScheme::contrastF());
}

QColor Okteta::ColorScheme::shade(const QColor &color, ShadeRole role, qreal contrast, qreal chromaAdjust)
{
    // nan -> 1.0
    contrast = (1.0 > contrast ? (-1.0 < contrast ? contrast : -1.0) : 1.0);
    qreal y = KColorUtils::luma(color);
    qreal yi = 1.0 - y;

    // handle very dark colors (base, mid, dark, shadow == midlight, light)
    if (y < 0.006) {
        switch (role) {
        case ColorScheme::LightShade:
            return KColorUtils::shade(color, 0.05 + 0.95 * contrast, chromaAdjust);
        case ColorScheme::MidShade:
            return KColorUtils::shade(color, 0.01 + 0.20 * contrast, chromaAdjust);
        case ColorScheme::DarkShade:
            return KColorUtils::shade(color, 0.02 + 0.40 * contrast, chromaAdjust);
        default:
            return KColorUtils::shade(color, 0.03 + 0.60 * contrast, chromaAdjust);
        }
    }

    // handle very light colors (base, midlight, light == mid, dark, shadow)
    if (y > 0.93) {
        switch (role) {
        case ColorScheme::MidlightShade:
            return KColorUtils::shade(color, -0.02 - 0.20 * contrast, chromaAdjust);
        case ColorScheme::DarkShade:
            return KColorUtils::shade(color, -0.06 - 0.60 * contrast, chromaAdjust);
        case ColorScheme::ShadowShade:
            return KColorUtils::shade(color, -0.10 - 0.90 * contrast, chromaAdjust);
        default:
            return KColorUtils::shade(color, -0.04 - 0.40 * contrast, chromaAdjust);
        }
    }

    // handle everything else
    qreal lightAmount = (0.05 + y * 0.55) * (0.25 + contrast * 0.75);
    qreal darkAmount = (- y) * (0.55 + contrast * 0.35);
    switch (role) {
    case ColorScheme::LightShade:
        return KColorUtils::shade(color, lightAmount, chromaAdjust);
    case ColorScheme::MidlightShade:
        return KColorUtils::shade(color, (0.15 + 0.35 * yi) * lightAmount, chromaAdjust);
    case ColorScheme::MidShade:
        return KColorUtils::shade(color, (0.35 + 0.15 * y) * darkAmount, chromaAdjust);
    case ColorScheme::DarkShade:
        return KColorUtils::shade(color, darkAmount, chromaAdjust);
    default:
        return KColorUtils::darken(KColorUtils::shade(color, darkAmount, chromaAdjust), 0.5 + 0.3 * y);
    }
}

void Okteta::ColorScheme::adjustBackground(QPalette &palette, BackgroundRole newRole, QPalette::ColorRole color,
                                    ColorSet set)
{
    palette.setBrush(QPalette::Active,   color, ColorScheme(QPalette::Active,   set).background(newRole));
    palette.setBrush(QPalette::Inactive, color, ColorScheme(QPalette::Inactive, set).background(newRole));
    palette.setBrush(QPalette::Disabled, color, ColorScheme(QPalette::Disabled, set).background(newRole));
}

void Okteta::ColorScheme::adjustForeground(QPalette &palette, ForegroundRole newRole, QPalette::ColorRole color,
                                    ColorSet set)
{
    palette.setBrush(QPalette::Active,   color, ColorScheme(QPalette::Active,   set).foreground(newRole));
    palette.setBrush(QPalette::Inactive, color, ColorScheme(QPalette::Inactive, set).foreground(newRole));
    palette.setBrush(QPalette::Disabled, color, ColorScheme(QPalette::Disabled, set).foreground(newRole));
}

bool Okteta::ColorScheme::isColorSetSupported(ColorScheme::ColorSet set)
{
    QJsonObject globalConfig;
        GlobalConfigStorage::Instance().config(globalConfig);
            auto colors = globalConfig.value(QLatin1String("Colors")).toObject();

    switch (set) {
        case View:
            return colors.contains(QLatin1String("View"));
        case Window:
            return colors.contains(QLatin1String("Window"));
        case Button:
            return colors.contains(QLatin1String("Button"));
        case Selection:
            return colors.contains(QLatin1String("Selection"));
        case Tooltip:
            return colors.contains(QLatin1String("Tooltip"));
        case Complementary:
            return colors.contains(QLatin1String("Complementary"));
        case Header:
            return colors.contains(QLatin1String("Header"));
        case NColorSets:
            break;
    }

    return false;
}

QPalette Okteta::ColorScheme::createApplicationPalette()
{
    QPalette palette;

    static const QPalette::ColorGroup states[QPalette::NColorGroups] = {
        QPalette::Active, QPalette::Inactive, QPalette::Disabled
    };

    // TT thinks tooltips shouldn't use active, so we use our active colors for all states
    ColorScheme schemeTooltip(QPalette::Active, ColorScheme::Tooltip);

    for (auto state : states) {
        ColorScheme schemeView(state, ColorScheme::View);
        ColorScheme schemeWindow(state, ColorScheme::Window);
        ColorScheme schemeButton(state, ColorScheme::Button);
        ColorScheme schemeSelection(state, ColorScheme::Selection);

        palette.setBrush(state, QPalette::WindowText, schemeWindow.foreground());
        palette.setBrush(state, QPalette::Window, schemeWindow.background());
        palette.setBrush(state, QPalette::Base, schemeView.background());
        palette.setBrush(state, QPalette::Text, schemeView.foreground());
        palette.setBrush(state, QPalette::Button, schemeButton.background());
        palette.setBrush(state, QPalette::ButtonText, schemeButton.foreground());
        palette.setBrush(state, QPalette::Highlight, schemeSelection.background());
        palette.setBrush(state, QPalette::HighlightedText, schemeSelection.foreground());
        palette.setBrush(state, QPalette::ToolTipBase, schemeTooltip.background());
        palette.setBrush(state, QPalette::ToolTipText, schemeTooltip.foreground());

        palette.setColor(state, QPalette::Light, schemeWindow.shade(ColorScheme::LightShade));
        palette.setColor(state, QPalette::Midlight, schemeWindow.shade(ColorScheme::MidlightShade));
        palette.setColor(state, QPalette::Mid, schemeWindow.shade(ColorScheme::MidShade));
        palette.setColor(state, QPalette::Dark, schemeWindow.shade(ColorScheme::DarkShade));
        palette.setColor(state, QPalette::Shadow, schemeWindow.shade(ColorScheme::ShadowShade));

        palette.setBrush(state, QPalette::AlternateBase, schemeView.background(ColorScheme::AlternateBackground));
        palette.setBrush(state, QPalette::Link, schemeView.foreground(ColorScheme::LinkText));
        palette.setBrush(state, QPalette::LinkVisited, schemeView.foreground(ColorScheme::VisitedText));
    }

    return palette;
}
