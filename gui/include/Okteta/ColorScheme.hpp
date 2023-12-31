#ifndef OKTETA_COLORSCHEME_HPP
#define OKTETA_COLORSCHEME_HPP

#include <QExplicitlySharedDataPointer>
#include <QPalette>

class QColor;
class QBrush;

namespace Okteta {

class ColorSchemePrivate;

/**
  * @class KColorScheme kcolorscheme.h KColorScheme
  *
  * No-KDE version KColorScheme for Okteta Widgets Library
  * @note see description on KDE Github
  * https://api.kde.org/frameworks/kconfigwidgets/html/classKColorScheme.html
  */
class ColorScheme
{
public:
    /**
     * This enumeration describes the color set for which a color is being
     * selected.
     *
     * Color sets define a color "environment", suitable for drawing all parts
     * of a given region. Colors from different sets should not be combined.
     */
    enum ColorSet {
        /**
         * Views; for example, frames, input fields, etc.
         *
         * If it contains things that can be selected, it is probably a View.
         */
        View,
        /**
         * Non-editable window elements; for example, menus.
         *
         * If it isn't a Button, View, or Tooltip, it is probably a Window.
         */
        Window,
        /**
         * Buttons and button-like controls.
         *
         * In addition to buttons, "button-like" controls such as non-editable
         * dropdowns, scrollbar sliders, slider handles, etc. should also use
         * this role.
         */
        Button,
        /**
         * Selected items in views.
         *
         * Note that unfocused or disabled selections should use the Window
         * role. This makes it more obvious to the user that the view
         * containing the selection does not have input focus.
         */
        Selection,
        /**
         * Tooltips.
         *
         * The tooltip set can often be substituted for the view
         * set when editing is not possible, but the Window set is deemed
         * inappropriate. "What's This" help is an excellent example, another
         * might be pop-up notifications (depending on taste).
         */
        Tooltip,
        /**
         * Complementary areas.
         *
         * Some applications want some areas to have a different color scheme.
         * Usually dark areas over a light theme. For instance the fullscreen UI
         * of a picture viewer, or the logout/lock screen of the plasma workspace
         * ask for a dark color scheme even on light themes.
         * @since 5.19
         */
        Complementary,
        /**
         * Colors for header areas that should be used both by the top toolbar and the titlebar.
         * @since 5.69
         */
        Header,
        /**
         * Number of color sets.
         * Note: don't use this
         * @since 5.65
         */
        NColorSets,
    };

    /**
     * This enumeration describes the background color being selected from the
     * given set.
     *
     * Background colors are suitable for drawing under text, and should never
     * be used to draw text. In combination with one of the overloads of
     * KColorScheme::shade, they may be used to generate colors for drawing
     * frames, bevels, and similar decorations.
     */
    enum BackgroundRole {
        /**
         * Normal background.
         */
        NormalBackground,
        /**
         * Alternate background; for example, for use in lists.
         *
         * This color may be the same as BackgroundNormal, especially in sets
         * other than View and Window.
         */
        AlternateBackground,
        /**
         * Third color; for example, items which are new, active, requesting
         * attention, etc.
         *
         * Alerting the user that a certain field must be filled out would be a
         * good usage (although NegativeBackground could be used to the same
         * effect, depending on what you are trying to achieve). Unlike
         * ActiveText, this should not be used for mouseover effects.
         */
        ActiveBackground,
        /**
         * Fourth color; corresponds to (unvisited) links.
         *
         * Exactly what this might be used for is somewhat harder to qualify;
         * it might be used for bookmarks, as a 'you can click here' indicator,
         * or to highlight recent content (i.e. in a most-recently-accessed
         * list).
         */
        LinkBackground,
        /**
         * Fifth color; corresponds to visited links.
         *
         * This can also be used to indicate "not recent" content, especially
         * when a color is needed to denote content which is "old" or
         * "archival".
         */
        VisitedBackground,
        /**
         * Sixth color; for example, errors, untrusted content, etc.
         */
        NegativeBackground,
        /**
         * Seventh color; for example, warnings, secure/encrypted content.
         */
        NeutralBackground,
        /**
         * Eighth color; for example, success messages, trusted content.
         */
        PositiveBackground,
        /**
         * Number of background roles.
         * @since 5.65
         */
        NBackgroundRoles,
    };

    /**
     * This enumeration describes the foreground color being selected from the
     * given set.
     *
     * Foreground colors are suitable for drawing text or glyphs (such as the
     * symbols on window decoration buttons, assuming a suitable background
     * brush is used), and should never be used to draw backgrounds.
     *
     * For window decorations, the following is suggested, but not set in
     * stone:
     * @li Maximize - PositiveText
     * @li Minimize - NeutralText
     * @li Close - NegativeText
     * @li WhatsThis - LinkText
     * @li Sticky - ActiveText
     */
    enum ForegroundRole {
        /**
         * Normal foreground.
         */
        NormalText,
        /**
         * Second color; for example, comments, items which are old, inactive
         * or disabled. Generally used for things that are meant to be "less
         * important". InactiveText is not the same role as NormalText in the
         * inactive state.
         */
        InactiveText,
        /**
         * Third color; for example items which are new, active, requesting
         * attention, etc. May be used as a hover color for clickable items.
         */
        ActiveText,
        /**
         * Fourth color; use for (unvisited) links. May also be used for other
         * clickable items or content that indicates relationships, items that
         * indicate somewhere the user can visit, etc.
         */
        LinkText,
        /**
         * Fifth color; used for (visited) links. As with LinkText, may be used
         * for items that have already been "visited" or accessed. May also be
         * used to indicate "historical" (i.e. "old") items or information,
         * especially if InactiveText is being used in the same context to
         * express something different.
         */
        VisitedText,
        /**
         * Sixth color; for example, errors, untrusted content, deletions,
         * etc.
         */
        NegativeText,
        /**
         * Seventh color; for example, warnings, secure/encrypted content.
         */
        NeutralText,
        /**
         * Eighth color; for example, additions, success messages, trusted
         * content.
         */
        PositiveText,
        /**
         * Number of foreground roles.
         * @since 5.65
         */
        NForegroundRoles,
    };

    /**
     * This enumeration describes the decoration color being selected from the
     * given set.
     *
     * Decoration colors are used to draw decorations (such as frames) for
     * special purposes. Like color shades, they are neither foreground nor
     * background colors. Text should not be painted over a decoration color,
     * and decoration colors should not be used to draw text.
     */
    enum DecorationRole {
        /**
         * Color used to draw decorations for items which have input focus.
         */
        FocusColor,
        /**
         * Color used to draw decorations for items which will be activated by
         * clicking.
         */
        HoverColor,
        /**
         * Number of decoration roles.
         * @since 5.65
         */
        NDecorationRoles,
    };

    /**
     * This enumeration describes the color shade being selected from the given
     * set.
     *
     * Color shades are used to draw "3d" elements, such as frames and bevels.
     * They are neither foreground nor background colors. Text should not be
     * painted over a shade, and shades should not be used to draw text.
     */
    enum ShadeRole {
        /**
         * The light color is lighter than dark() or shadow() and contrasts
         * with the base color.
         */
        LightShade,
        /**
         * The midlight color is in between base() and light().
         */
        MidlightShade,
        /**
         * The mid color is in between base() and dark().
         */
        MidShade,
        /**
         * The dark color is in between mid() and shadow().
         */
        DarkShade,
        /**
         * The shadow color is darker than light() or midlight() and contrasts
         * the base color.
         */
        ShadowShade,
        /**
         * Number of shade roles.
         * @since 5.65
         */
        NShadeRoles,
    };

    /** Destructor */
    ~ColorScheme();

    ColorScheme(const ColorScheme &);
    ColorScheme &operator=(const ColorScheme &);
    ColorScheme(ColorScheme &&);
    ColorScheme &operator=(ColorScheme &&);

    /**
     * Construct a palette from given color set and state. Colors are taken
     * from the given KConfig. If null, the application's color scheme is used
     *  (either the system default or one set by KColorSchemeManager).
     *
     * @note KColorScheme provides direct access to the color scheme for users
     * that deal directly with widget states. Unless you are a low-level user
     * or have a legitimate reason to only care about a fixed, limited number
     * of states (e.g. windows that cannot be inactive), consider using a
     * ::KStatefulBrush instead.
     */
    explicit ColorScheme(QPalette::ColorGroup = QPalette::Normal, ColorSet = View);

    /**
     * Retrieve the requested background brush.
     */
    QBrush background(BackgroundRole = NormalBackground) const;

    /**
     * Retrieve the requested foreground brush.
     */
    QBrush foreground(ForegroundRole = NormalText) const;

    /**
     * Retrieve the requested decoration brush.
     */
    QBrush decoration(DecorationRole) const;

    /**
     * Retrieve the requested shade color, using
     * KColorScheme::background(KColorScheme::NormalBackground)
     * as the base color and the contrast setting from the KConfig used to
     * create this KColorScheme instance.
     *
     * @note Shades are chosen such that all shades would contrast with the
     * base color. This means that if base is very dark, the 'dark' shades will
     * be lighter than the base color, with midlight() == shadow().
     * Conversely, if the base color is very light, the 'light' shades will be
     * darker than the base color, with light() == mid().
     */
    QColor shade(ShadeRole) const;

    /**
     * Returns the contrast for borders as a floating point value.
     * @param config pointer to the config from which to read the contrast
     * setting. If null, the application's color scheme will be used
     *   (either the system default or one set by KColorSchemeManager).
     * @return the contrast (between 0.0 for minimum and 1.0 for maximum
     *         contrast)
     */
    static qreal contrastF();

    /**
     * Retrieve the requested shade color, using the specified color as the
     * base color and the application's contrast setting.
     *
     * @note Shades are chosen such that all shades would contrast with the
     * base color. This means that if base is very dark, the 'dark' shades will
     * be lighter than the base color, with midlight() == shadow().
     * Conversely, if the base color is very light, the 'light' shades will be
     * darker than the base color, with light() == mid().
     */
    static QColor shade(const QColor &, ShadeRole);

    /**
     * Retrieve the requested shade color, using the specified color as the
     * base color and the specified contrast.
     *
     * @param contrast Amount roughly specifying the contrast by which to
     * adjust the base color, between -1.0 and 1.0 (values between 0.0 and 1.0
     * correspond to the value from KColorScheme::contrastF)
     * @param chromaAdjust (optional) Amount by which to adjust the chroma of
     * the shade (1.0 means no adjustment)
     *
     * @note Shades are chosen such that all shades would contrast with the
     * base color. This means that if base is very dark, the 'dark' shades will
     * be lighter than the base color, with midlight() == shadow().
     * Conversely, if the base color is very light, the 'light' shades will be
     * darker than the base color, with light() == mid().
     *
     * @see KColorUtils::shade
     */
    static QColor shade(const QColor &, ShadeRole, qreal contrast, qreal chromaAdjust = 0.0);

    /**
     * Adjust a QPalette by replacing the specified QPalette::ColorRole with
     * the requested background color for all states. Using this method is
     * safer than replacing individual states, as it insulates you against
     * changes in QPalette::ColorGroup.
     *
     * @note Although it is possible to replace a foreground color using this
     * method, it's bad usability to do so. Just say "no".
     */
    static void adjustBackground(QPalette &,
                                 BackgroundRole newRole = NormalBackground,
                                 QPalette::ColorRole color = QPalette::Base,
                                 ColorSet set = View);

    /**
     * Adjust a QPalette by replacing the specified QPalette::ColorRole with
     * the requested foreground color for all states. Using this method is
     * safer than replacing individual states, as it insulates you against
     * changes in QPalette::ColorGroup.
     *
     * @note Although it is possible to replace a background color using this
     * method, it's bad usability to do so. Just say "no".
     */
    static void adjustForeground(QPalette &,
                                 ForegroundRole newRole = NormalText,
                                 QPalette::ColorRole color = QPalette::Text,
                                 ColorSet set = View);

    /**
     * Used to obtain the QPalette that will be used to set the application
     * palette from KDE Platform theme.
     *
     * @param config KConfig from which to load the colors
     *
     * @returns the QPalette
     *
     * @since 5.0
     */
    static QPalette createApplicationPalette();

    /**
     * Used to check if the color scheme has a given set.
     *
     * @param config KConfig from which to load the colors
     *
     * @param set The color set to check for.
     *
     * @returns whether the color scheme has a given color set
     *
     * @since 5.75
     */
    static bool isColorSetSupported(ColorScheme::ColorSet set);

    /**
     * @since 5.92
     */
    bool operator==(const ColorScheme &other) const;

private:
    QExplicitlySharedDataPointer<ColorSchemePrivate> d;
};

} // namespace Okteta

Q_DECLARE_METATYPE(Okteta::ColorScheme)

#endif   // OKTETA_COLORSCHEME_HPP
