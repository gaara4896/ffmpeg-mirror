/*
 * Copyright (C) 2001-2003 Michael Niedermayer <michaelni@gmx.at>
 *
 * This file is part of Libav.
 *
 * Libav is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * Libav is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Libav; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */


#if COMPILE_TEMPLATE_ALTIVEC
#include "swscale_altivec_template.c"
#endif

#if COMPILE_TEMPLATE_ALTIVEC
static inline void RENAME(yuv2yuvX)(SwsContext *c, const int16_t *lumFilter, const int16_t **lumSrc, int lumFilterSize,
                                    const int16_t *chrFilter, const int16_t **chrSrc, int chrFilterSize, const int16_t **alpSrc,
                                    uint8_t *dest, uint8_t *uDest, uint8_t *vDest, uint8_t *aDest, long dstW, long chrDstW)
{
    yuv2yuvX_altivec_real(lumFilter, lumSrc, lumFilterSize,
                          chrFilter, chrSrc, chrFilterSize,
                          dest, uDest, vDest, dstW, chrDstW);
}

/**
 * vertical scale YV12 to RGB
 */
static inline void RENAME(yuv2packedX)(SwsContext *c, const int16_t *lumFilter, const int16_t **lumSrc, int lumFilterSize,
                                       const int16_t *chrFilter, const int16_t **chrSrc, int chrFilterSize,
                                       const int16_t **alpSrc, uint8_t *dest, long dstW, long dstY)
{
    /* The following list of supported dstFormat values should
       match what's found in the body of ff_yuv2packedX_altivec() */
    if (!(c->flags & SWS_BITEXACT) && !c->alpPixBuf &&
         (c->dstFormat==PIX_FMT_ABGR  || c->dstFormat==PIX_FMT_BGRA  ||
          c->dstFormat==PIX_FMT_BGR24 || c->dstFormat==PIX_FMT_RGB24 ||
          c->dstFormat==PIX_FMT_RGBA  || c->dstFormat==PIX_FMT_ARGB))
            ff_yuv2packedX_altivec(c, lumFilter, lumSrc, lumFilterSize,
                                   chrFilter, chrSrc, chrFilterSize,
                                   dest, dstW, dstY);
    else
        yuv2packedXinC(c, lumFilter, lumSrc, lumFilterSize,
                       chrFilter, chrSrc, chrFilterSize,
                       alpSrc, dest, dstW, dstY);
}
#endif

static void RENAME(sws_init_swScale)(SwsContext *c)
{
    enum PixelFormat srcFormat = c->srcFormat;

    c->yuv2yuvX     = RENAME(yuv2yuvX    );
    c->yuv2packedX  = RENAME(yuv2packedX );
}
