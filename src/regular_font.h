//
// Created by anachtmann on 8/23/21.
//

#ifndef FLIPDOT_REGULAR_FONT_H
#define FLIPDOT_REGULAR_FONT_H

#include "font.h"

class RegularFont : public PixelFont {
public:

private:
    static const bool chars[];
    static const int widths[];
    static const int heights[];
    static const int jumps[];

    const bool *get_chars() override {
        return chars;
    }


    const int *get_jumps() override {
        return jumps;
    }

    const int *get_widths() override {
        return widths;
    }

    const int *get_heights() override {
        return heights;
    }

};
#define X true
#define O false
const bool RegularFont::chars[] = {
        /* ! */
        X,
        X,
        X,
        X,
        X,
        O,
        X,
        O,
        /* " */
        X, O, X,
        X, O, X,
        O, O, O,
        O, O, O,
        O, O, O,
        O, O, O,
        O, O, O,
        O, O, O,
        /* # */
        O, O, X, O, O, X,
        O, X, O, O, X, O,
        X, X, X, X, X, X,
        O, X, O, O, X, O,
        X, X, X, X, X, X,
        O, X, O, O, X, O,
        X, O, O, X, O, O,
        O, O, O, O, O, O,
        /* $ */
        O, O, X, O, O,
        O, X, X, X, X,
        X, O, X, O, O,
        O, X, X, X, O,
        O, O, X, O, X,
        X, X, X, X, O,
        O, O, X, O, O,
        O, O, O, O, O,
        /* % */
        O, X, O, O, O, O, O, X, O,
        X, O, X, O, O, O, X, O, O,
        O, X, O, O, O, X, O, O, O,
        O, O, O, O, X, O, O, O, O,
        O, O, O, X, O, O, O, X, O,
        O, O, X, O, O, O, X, O, X,
        O, X, O, O, O, O, O, X, O,
        O, O, O, O, O, O, O, O, O,
        /* & */
        O, X, X, O, O,
        X, O, O, X, O,
        X, O, O, X, O,
        O, X, X, X, X,
        X, O, O, X, O,
        X, O, O, X, O,
        O, X, X, O, X,
        O, O, O, O, O,
        /* ' */
        X,
        X,
        O,
        O,
        O,
        O,
        O,
        O,
        /* ( */
        O, O, X,
        O, X, O,
        X, O, O,
        X, O, O,
        X, O, O,
        O, X, O,
        O, O, X,
        O, O, O,
        /* ) */
        X, O, O,
        O, X, O,
        O, O, X,
        O, O, X,
        O, O, X,
        O, X, O,
        X, O, O,
        O, O, O,
        /* * */
        O, O, O, O, O,
        O, O, X, O, O,
        X, O, X, O, X,
        O, X, X, X, O,
        X, O, X, O, X,
        O, O, X, O, O,
        O, O, O, O, O,
        O, O, O, O, O,
        /* + */
        O, O, O, O, O,
        O, O, X, O, O,
        O, O, X, O, O,
        X, X, X, X, X,
        O, O, X, O, O,
        O, O, X, O, O,
        O, O, O, O, O,
        O, O, O, O, O,
        /* , */
        O, O,
        O, O,
        O, O,
        O, O,
        O, O,
        O, X,
        X, O,
        O, O,
        /* - */
        O, O, O,
        O, O, O,
        O, O, O,
        X, X, X,
        O, O, O,
        O, O, O,
        O, O, O,
        O, O, O,
        /* . */
        O,
        O,
        O,
        O,
        O,
        O,
        X,
        O,
        /* / */
        O, O, O, O, X,
        O, O, O, X, O,
        O, O, O, X, O,
        O, O, X, O, O,
        O, X, O, O, O,
        O, X, O, O, O,
        X, O, O, O, O,
        O, O, O, O, O,
        /* 0 */
        O, X, X, O,
        X, O, O, X,
        X, O, O, X,
        X, O, X, X,
        X, X, O, X,
        X, O, O, X,
        O, X, X, O,
        O, O, O, O,
        /* 1 */
        O, X,
        X, X,
        O, X,
        O, X,
        O, X,
        O, X,
        O, X,
        O, O,
        /* 2 */
        O, X, X, O,
        X, O, O, X,
        O, O, O, X,
        O, O, X, O,
        O, X, O, O,
        X, O, O, O,
        X, X, X, X,
        O, O, O, O,
        /* 3 */
        O, X, X, O,
        X, O, O, X,
        O, O, O, X,
        O, X, X, O,
        O, O, O, X,
        X, O, O, X,
        O, X, X, O,
        O, O, O, O,
        /* 4 */
        O, O, O, X, O,
        O, O, X, O, O,
        O, X, O, O, O,
        X, O, O, X, O,
        X, X, X, X, X,
        O, O, O, X, O,
        O, O, O, X, O,
        O, O, O, O, O,
        /* 5 */
        X, X, X, X,
        X, O, O, O,
        X, O, O, O,
        X, X, X, O,
        O, O, O, X,
        O, O, O, X,
        X, X, X, O,
        O, O, O, O,
        /* 6 */
        O, X, X, O,
        X, O, O, X,
        X, O, O, O,
        X, X, X, O,
        X, O, O, X,
        X, O, O, X,
        O, X, X, O,
        O, O, O, O,
        /* 7 */
        X, X, X, X, X,
        O, O, O, O, X,
        O, O, O, X, O,
        O, O, X, O, O,
        O, X, O, O, O,
        O, X, O, O, O,
        O, X, O, O, O,
        O, O, O, O, O,
        /* 8 */
        O, X, X, O,
        X, O, O, X,
        X, O, O, X,
        O, X, X, O,
        X, O, O, X,
        X, O, O, X,
        O, X, X, O,
        O, O, O, O,
        /* 9 */
        O, X, X, O,
        X, O, O, X,
        X, O, O, X,
        O, X, X, X,
        O, O, O, X,
        X, O, O, X,
        O, X, X, O,
        O, O, O, O,
        /* : */
        O,
        O,
        X,
        O,
        O,
        X,
        O,
        O,
        /* ; */
        /* < */
        /* = */
        /* > */
        /* ? */
        /* @ */
        /* A */
        /* B */
        /* C */
        /* D */
        /* E */
        /* F */
        /* G */
        /* H */
        /* I */
        /* J */
        /* K */
        /* L */
        /* M */
        /* N */
        /* O */
        /* P */
        /* Q */
        /* R */
        /* S */
        /* T */
        /* U */
        /* V */
        /* W */
        /* X */
        /* Y */
        /* Z */
        /* [ */
        /* \ */
        /* ] */
        /* ^ */
        /* _ */
        /* ` */
        /* a */
        /* b */
        /* c */
        /* d */
        /* e */
        /* f */
        /* g */
        /* h */
        /* i */
        /* j */
        /* k */
        /* l */
        /* m */
        /* n */
        /* O */
        /* p */
        /* q */
        /* r */
        /* s */
        /* t */
        /* u */
        /* v */
        /* w */
        /* X */
        /* y */
        /* z */
        /* { */
        /* | */
        /* } */
        /* ~ */
        /* € */
        /* Ä */
        /* Ö */
        /* Ü */
        /* ß */
        /* ä */
        /* ö */
        /* ü */
};
const int RegularFont::widths[] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, 1, 3, 6, 5, 9, 5, 1, 3, 3, 5, 5, 2, 3, 1, 5,
        4, 2, 4, 4, 5, 4, 4, 5, 4, 4, 1, 2, 4, 4, 4, 4,
        6, 5, 4, 4, 4, 4, 4, 4, 4, 1, 4, 5, 4, 5, 5, 4,
        4, 6, 4, 4, 5, 4, 5, 7, 5, 5, 5, 2, 5, 2, 5, 5,
        2, 4, 4, 4, 4, 4, 3, 4, 4, 1, 2, 4, 2, 7, 4, 4,
        4, 4, 3, 4, 3, 4, 5, 5, 5, 4, 5, 3, 1, 3, 4, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, 4, -1, -1, -1, -1, -1, 4, -1, -1, 4,
        -1, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, 4, -1, -1, -1, -1, -1, 4, -1, -1, -1
};
#undef X
#undef O

const int RegularFont::jumps[] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, 0, 8, 32, 80, 120, 192, 232, 240, 264, 288, 328, 368, 384, 408, 416,
        456, 488, 504, 536, 568, 608, 640, 672, 712, 744, 776, 784, 800, 832, 864, 896,
        928, 976, 1016, 1048, 1080, 1112, 1144, 1176, 1208, 1240, 1248, 1280, 1320, 1352, 1392, 1432,
        1464, 1496, 1544, 1576, 1608, 1648, 1680, 1720, 1776, 1816, 1856, 1896, 1912, 1952, 1968, 2008,
        2048, 2064, 2096, 2128, 2160, 2192, 2224, 2248, 2280, 2312, 2320, 2336, 2368, 2384, 2440, 2472,
        2504, 2536, 2568, 2592, 2624, 2648, 2680, 2720, 2760, 2800, 2832, 2872, 2896, 2904, 2928, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, 2960, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, 3000, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, 3040, -1, -1, -1, -1, -1, 3072, -1, -1, 3104,
        -1, -1, -1, -1, 3136, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, 3168, -1, -1, -1, -1, -1, 3200, -1, -1, -1,
};

const int RegularFont::heights[] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, 8, -1, -1, 8,
        -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, 8, -1, -1, -1
};


#endif //FLIPDOT_REGULAR_FONT_H
