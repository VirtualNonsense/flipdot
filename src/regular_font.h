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
#define x true
#define o false
const bool RegularFont::chars[] = {
        /*   */
        o, o, o, o,
        o, o, o, o,
        o, o, o, o,
        o, o, o, o,
        o, o, o, o,
        o, o, o, o,
        o, o, o, o,
        o, o, o, o,
        /* ! */
        x,
        x,
        x,
        x,
        x,
        o,
        x,
        o,
        /* " */
        x, o, x,
        x, o, x,
        o, o, o,
        o, o, o,
        o, o, o,
        o, o, o,
        o, o, o,
        o, o, o,
        /* # */
        o, o, x, o, o, x,
        o, x, o, o, x, o,
        x, x, x, x, x, x,
        o, x, o, o, x, o,
        x, x, x, x, x, x,
        o, x, o, o, x, o,
        x, o, o, x, o, o,
        o, o, o, o, o, o,
        /* $ */
        o, o, x, o, o,
        o, x, x, x, x,
        x, o, x, o, o,
        o, x, x, x, o,
        o, o, x, o, x,
        x, x, x, x, o,
        o, o, x, o, o,
        o, o, o, o, o,
        /* % */
        o, x, o, o, o, o, o, x, o,
        x, o, x, o, o, o, x, o, o,
        o, x, o, o, o, x, o, o, o,
        o, o, o, o, x, o, o, o, o,
        o, o, o, x, o, o, o, x, o,
        o, o, x, o, o, o, x, o, x,
        o, x, o, o, o, o, o, x, o,
        o, o, o, o, o, o, o, o, o,
        /* & */
        o, x, x, o, o,
        x, o, o, x, o,
        x, o, o, x, o,
        o, x, x, x, x,
        x, o, o, x, o,
        x, o, o, x, o,
        o, x, x, o, x,
        o, o, o, o, o,
        /* ' */
        x,
        x,
        o,
        o,
        o,
        o,
        o,
        o,
        /* ( */
        o, o, x,
        o, x, o,
        x, o, o,
        x, o, o,
        x, o, o,
        o, x, o,
        o, o, x,
        o, o, o,
        /* ) */
        x, o, o,
        o, x, o,
        o, o, x,
        o, o, x,
        o, o, x,
        o, x, o,
        x, o, o,
        o, o, o,
        /* * */
        o, o, o, o, o,
        o, o, x, o, o,
        x, o, x, o, x,
        o, x, x, x, o,
        x, o, x, o, x,
        o, o, x, o, o,
        o, o, o, o, o,
        o, o, o, o, o,
        /* + */
        o, o, o, o, o,
        o, o, x, o, o,
        o, o, x, o, o,
        x, x, x, x, x,
        o, o, x, o, o,
        o, o, x, o, o,
        o, o, o, o, o,
        o, o, o, o, o,
        /* , */
        o, o,
        o, o,
        o, o,
        o, o,
        o, o,
        o, x,
        x, o,
        o, o,
        /* - */
        o, o, o,
        o, o, o,
        o, o, o,
        x, x, x,
        o, o, o,
        o, o, o,
        o, o, o,
        o, o, o,
        /* . */
        o,
        o,
        o,
        o,
        o,
        o,
        x,
        o,
        /* / */
        o, o, o, o, x,
        o, o, o, x, o,
        o, o, o, x, o,
        o, o, x, o, o,
        o, x, o, o, o,
        o, x, o, o, o,
        x, o, o, o, o,
        o, o, o, o, o,
        /* 0 */
        o, x, x, o,
        x, o, o, x,
        x, o, o, x,
        x, o, x, x,
        x, x, o, x,
        x, o, o, x,
        o, x, x, o,
        o, o, o, o,
        /* 1 */
        o, x,
        x, x,
        o, x,
        o, x,
        o, x,
        o, x,
        o, x,
        o, o,
        /* 2 */
        o, x, x, o,
        x, o, o, x,
        o, o, o, x,
        o, o, x, o,
        o, x, o, o,
        x, o, o, o,
        x, x, x, x,
        o, o, o, o,
        /* 3 */
        o, x, x, o,
        x, o, o, x,
        o, o, o, x,
        o, x, x, o,
        o, o, o, x,
        x, o, o, x,
        o, x, x, o,
        o, o, o, o,
        /* 4 */
        o, o, o, x, o,
        o, o, x, o, o,
        o, x, o, o, o,
        x, o, o, x, o,
        x, x, x, x, x,
        o, o, o, x, o,
        o, o, o, x, o,
        o, o, o, o, o,
        /* 5 */
        x, x, x, x,
        x, o, o, o,
        x, o, o, o,
        x, x, x, o,
        o, o, o, x,
        o, o, o, x,
        x, x, x, o,
        o, o, o, o,
        /* 6 */
        o, x, x, o,
        x, o, o, x,
        x, o, o, o,
        x, x, x, o,
        x, o, o, x,
        x, o, o, x,
        o, x, x, o,
        o, o, o, o,
        /* 7 */
        x, x, x, x, x,
        o, o, o, o, x,
        o, o, o, x, o,
        o, o, x, o, o,
        o, x, o, o, o,
        o, x, o, o, o,
        o, x, o, o, o,
        o, o, o, o, o,
        /* 8 */
        o, x, x, o,
        x, o, o, x,
        x, o, o, x,
        o, x, x, o,
        x, o, o, x,
        x, o, o, x,
        o, x, x, o,
        o, o, o, o,
        /* 9 */
        o, x, x, o,
        x, o, o, x,
        x, o, o, x,
        o, x, x, x,
        o, o, o, x,
        x, o, o, x,
        o, x, x, o,
        o, o, o, o,
        /* : */
        o,
        o,
        x,
        o,
        o,
        x,
        o,
        o,
        /* ; */
        o, o,
        o, o,
        o, x,
        o, o,
        o, o,
        o, o,
        o, x,
        x, o,
        /* < */
        o, o, o, o,
        o, o, o, x,
        o, x, x, o,
        x, o, o, o,
        o, x, x, o,
        o, o, o, x,
        o, o, o, o,
        o, o, o, o,
        /* = */
        o, o, o, o,
        o, o, o, o,
        x, x, x, x,
        o, o, o, o,
        x, x, x, x,
        o, o, o, o,
        o, o, o, o,
        o, o, o, o,
        /* > */
        o, o, o, o,
        x, o, o, o,
        o, x, x, o,
        o, o, o, x,
        o, x, x, o,
        x, o, o, o,
        o, o, o, o,
        o, o, o, o,
        /* ? */
        o, x, x, o,
        x, o, o, x,
        o, o, o, x,
        o, o, x, o,
        o, x, o, o,
        o, o, o, o,
        o, x, o, o,
        o, o, o, o,
        /* @ */
        o, o, x, x, x, o,
        o, x, o, o, o, x,
        x, o, o, x, x, x,
        x, o, x, o, o, x,
        x, o, o, x, x, x,
        o, x, o, o, o, o,
        o, o, x, x, x, o,
        o, o, o, o, o, o,
        /* A */
        o, o, x, o, o,
        o, x, o, x, o,
        x, o, o, o, x,
        x, x, x, x, x,
        x, o, o, o, x,
        x, o, o, o, x,
        x, o, o, o, x,
        o, o, o, o, o,
        /* B */
        x, x, x, o,
        x, o, o, x,
        x, o, o, x,
        x, x, x, o,
        x, o, o, x,
        x, o, o, x,
        x, x, x, o,
        o, o, o, o,
        /* C */
        o, x, x, x,
        x, o, o, o,
        x, o, o, o,
        x, o, o, o,
        x, o, o, o,
        x, o, o, o,
        o, x, x, x,
        o, o, o, o,
        /* D */
        x, x, x, o,
        x, o, o, x,
        x, o, o, x,
        x, o, o, x,
        x, o, o, x,
        x, o, o, x,
        x, x, x, o,
        o, o, o, o,
        /* E */
        x, x, x, x,
        x, o, o, o,
        x, o, o, o,
        x, x, x, o,
        x, o, o, o,
        x, o, o, o,
        x, x, x, x,
        o, o, o, o,
        /* F */
        x, x, x, x,
        x, o, o, o,
        x, o, o, o,
        x, x, x, o,
        x, o, o, o,
        x, o, o, o,
        x, o, o, o,
        o, o, o, o,
        /* G */
        o, x, x, o,
        x, o, o, o,
        x, o, o, o,
        x, o, x, o,
        x, o, o, x,
        x, o, o, x,
        o, x, x, o,
        o, o, o, o,
        /* H */
        x, o, o, x,
        x, o, o, x,
        x, o, o, x,
        x, x, x, x,
        x, o, o, x,
        x, o, o, x,
        x, o, o, x,
        o, o, o, o,
        /* I */
        x,
        x,
        x,
        x,
        x,
        x,
        x,
        o,
        /* J */
        o, o, o, x,
        o, o, o, x,
        o, o, o, x,
        o, o, o, x,
        o, o, o, x,
        x, o, o, x,
        o, x, x, o,
        o, o, o, o,
        /* K */
        x, o, o, o, x,
        x, o, o, x, o,
        x, o, x, o, o,
        x, x, o, o, o,
        x, o, x, o, o,
        x, o, o, x, o,
        x, o, o, o, x,
        o, o, o, o, o,
        /* L */
        x, o, o, o,
        x, o, o, o,
        x, o, o, o,
        x, o, o, o,
        x, o, o, o,
        x, o, o, o,
        x, x, x, x,
        o, o, o, o,
        /* M */
        x, o, o, o, x,
        x, x, o, x, x,
        x, o, x, o, x,
        x, o, o, o, x,
        x, o, o, o, x,
        x, o, o, o, x,
        x, o, o, o, x,
        o, o, o, o, o,
        /* N */
        x, o, o, o, x,
        x, o, o, o, x,
        x, x, o, o, x,
        x, o, x, o, x,
        x, o, o, x, x,
        x, o, o, o, x,
        x, o, o, o, x,
        o, o, o, o, o,
        /* O */
        o, x, x, o,
        x, o, o, x,
        x, o, o, x,
        x, o, o, x,
        x, o, o, x,
        x, o, o, x,
        o, x, x, o,
        o, o, o, o,
        /* P */
        x, x, x, o,
        x, o, o, x,
        x, o, o, x,
        x, x, x, o,
        x, o, o, o,
        x, o, o, o,
        x, o, o, o,
        o, o, o, o,
        /* Q */
        o, x, x, x, o, o,
        x, o, o, o, x, o,
        x, o, o, o, x, o,
        x, o, o, o, x, o,
        x, o, o, o, x, o,
        x, o, o, o, x, o,
        o, x, x, x, x, x,
        o, o, o, o, o, o,
        /* R */
        x, x, x, o,
        x, o, o, x,
        x, o, o, x,
        x, x, x, o,
        x, x, o, o,
        x, o, x, o,
        x, o, o, x,
        o, o, o, o,
        /* S */
        o, x, x, o,
        x, o, o, x,
        x, o, o, o,
        o, x, x, o,
        o, o, o, x,
        x, o, o, x,
        o, x, x, o,
        o, o, o, o,
        /* T */
        x, x, x, x, x,
        o, o, x, o, o,
        o, o, x, o, o,
        o, o, x, o, o,
        o, o, x, o, o,
        o, o, x, o, o,
        o, o, x, o, o,
        o, o, o, o, o,
        /* U */
        x, o, o, x,
        x, o, o, x,
        x, o, o, x,
        x, o, o, x,
        x, o, o, x,
        x, o, o, x,
        o, x, x, o,
        o, o, o, o,
        /* V */
        x, o, o, o, x,
        x, o, o, o, x,
        x, o, o, o, x,
        x, o, o, o, x,
        x, o, o, o, x,
        o, x, o, x, o,
        o, o, x, o, o,
        o, o, o, o, o,
        /* W */
        x, o, o, o, o, o, x,
        x, o, o, o, o, o, x,
        x, o, o, o, o, o, x,
        x, o, o, o, o, o, x,
        x, o, o, x, o, o, x,
        x, o, x, o, x, o, x,
        o, x, o, o, o, x, o,
        o, o, o, o, o, o, o,
        /* X */
        x, o, o, o, x,
        x, o, o, o, x,
        o, x, o, x, o,
        o, o, x, o, o,
        o, x, o, x, o,
        x, o, o, o, x,
        x, o, o, o, x,
        o, o, o, o, o,
        /* Y */
        x, o, o, o, x,
        x, o, o, o, x,
        o, x, o, x, o,
        o, x, o, x, o,
        o, o, x, o, o,
        o, o, x, o, o,
        o, o, x, o, o,
        o, o, o, o, o,
        /* Z */
        x, x, x, x, x,
        o, o, o, o, x,
        o, o, o, x, o,
        o, o, x, o, o,
        o, x, o, o, o,
        x, o, o, o, o,
        x, x, x, x, x,
        o, o, o, o, o,
        /* [ */
        x, x,
        x, o,
        x, o,
        x, o,
        x, o,
        x, o,
        x, x,
        o, o,
        /* \ */
        x, o, o, o, o,
        o, x, o, o, o,
        o, x, o, o, o,
        o, o, x, o, o,
        o, o, o, x, o,
        o, o, o, x, o,
        o, o, o, o, x,
        o, o, o, o, o,
        /* ] */
        x, x,
        o, x,
        o, x,
        o, x,
        o, x,
        o, x,
        x, x,
        o, o,
        /* ^ */
        o, o, x, o, o,
        o, x, o, x, o,
        x, o, o, o, x,
        o, o, o, o, o,
        o, o, o, o, o,
        o, o, o, o, o,
        o, o, o, o, o,
        o, o, o, o, o,
        /* _ */
        o, o, o, o, o,
        o, o, o, o, o,
        o, o, o, o, o,
        o, o, o, o, o,
        o, o, o, o, o,
        o, o, o, o, o,
        x, x, x, x, x,
        o, o, o, o, o,
        /* ` */
        x, o,
        o, x,
        o, o,
        o, o,
        o, o,
        o, o,
        o, o,
        o, o,
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
        4, 1, 3, 6, 5, 9, 5, 1, 3, 3, 5, 5, 2, 3, 1, 5,
        4, 2, 4, 4, 5, 4, 4, 5, 4, 4, 1, 2, 4, 4, 4, 4,
/*@*/   6, 5, 4, 4, 4, 4, 4, 4, 4, 1, 4, 5, 4, 5, 5, 4,
/*P*/   4, 6, 4, 4, 5, 4, 5, 7, 5, 5, 5, 2, 5, 2, 5, 5,
/*]*/   2, 4, 4, 4, 4, 4, 3, 4, 4, 1, 2, 4, 2, 7, 4, 4,
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
#undef x
#undef o

const int RegularFont::jumps[] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        0, 32, 40, 64, 112, 152, 224, 264, 272, 296, 320, 360, 400, 416, 440, 448,
        488, 520, 536, 568, 600, 640, 672, 704, 744, 776, 808, 816, 832, 864, 896, 928,
        960, 1008, 1048, 1080, 1112, 1144, 1176, 1208, 1240, 1272, 1280, 1312, 1352, 1384, 1424, 1464,
        1496, 1528, 1576, 1608, 1640, 1680, 1712, 1752, 1808, 1848, 1888, 1928, 1944, 1984, 2000, 2040,
        2080, 2096, 2128, 2160, 2192, 2224, 2256, 2280, 2312, 2344, 2352, 2368, 2400, 2416, 2472, 2504,
        2536, 2568, 2600, 2624, 2656, 2680, 2712, 2752, 2792, 2832, 2864, 2904, 2928, 2936, 2960, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, 2992, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, 3032, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, 3072, -1, -1, -1, -1, -1, 3104, -1, -1, 3136,
        -1, -1, -1, -1, 3168, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, 3200, -1, -1, -1, -1, -1, 3232, -1, -1, -1,
};

const int RegularFont::heights[] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
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
