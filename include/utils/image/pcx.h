#ifndef IMAGE_FORMAT_PCX_UTILS_H
#define IMAGE_FORMAT_PCX_UTILS_H

#include "../byte.h"

typedef struct _PcxHeader
{
    BYTE Identifier;     /* PCX Id Number (Always 0x0A) */
    BYTE Version;        /* Version Number */
    BYTE Encoding;       /* Encoding Format */
    BYTE BitsPerPixel;   /* Bits per Pixel */
    WORD XStart;         /* Left of image */
    WORD YStart;         /* Top of Image */
    WORD XEnd;           /* Right of Image  */
    WORD YEnd;           /* Bottom of image */
    WORD HorzRes;        /* Horizontal Resolution */
    WORD VertRes;        /* Vertical Resolution */
    BYTE Palette[48];    /* 16-Color EGA Palette */
    BYTE Reserved1;      /* Reserved (Always 0) */
    BYTE NumBitPlanes;   /* Number of Bit Planes */
    WORD BytesPerLine;   /* Bytes per Scan-line */
    WORD PaletteType;    /* Palette Type */
    WORD HorzScreenSize; /* Horizontal Screen Size */
    WORD VertScreenSize; /* Vertical Screen Size */
    BYTE Reserved2[54];  /* Reserved (Always 0) */
} PCXHEAD;

#endif