/*
 * MELKONIAN Marc - 13410425
 * base64.c - base64 coding
 * Date: 04 May 2015
 */

#include "base64.h"

/*
 * Encode a string to its base64 representation
 * Doc: https://tools.ietf.org/html/rfc4648#page-5
 * input : 3 * 8-bit group => 4 x 6 bit-group => 4 x printable characters
 * (each 6-bit value represents the index in the alphabet table to get a
 * printable character)
 * ie:  the fig. below guides the bitwise operations
 * bytes            A                 B                 C
 * input   | 1 0 1 1 0 1 1 1 | 1 0 0 0 1 0 1 0 | 1 0 1 1 0 0 1 1 |
 * output  | 1 0 1 1 0 1|1 1   1 0 0 0|1 0 1 0   1 0|1 1 0 0 1 1 |
 */
char*
to_base64(char* s)
{
        const char base64symbols[] =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "0123456789+/";

        char * res;
        int slen;   /* input string length */
        int outlen; /* encoded string length */

        slen = strlen(s);
        outlen = ((slen / 3) * 4) + 1; /* output length */
        res = calloc(outlen, 1);
        if (!res) {
                return NULL;
        }

        int i, j = 0;
        int block1, block2, block3, block4;

        /* as stated in the RFC4648, output string length must be a multiple
         * of 3, so the last block must be handled separately since input
         * length % 3 is not necessarily equal to 0 */
        for (i=0; i < (slen-(slen%3)); i+=3) {/* 3-byte blocks (= 24 bits) */
                /* from 3 x 8-bit (1-byte) blocks to 4 x 6-bit blocks */
                block1 = (s[i+0] >> 2) & 0x3F;
                block2 = ((s[i+0] << 4) | (s[i+1] >> 4)) & 0x3F;
                block3 = ((s[i+1] << 2) | (s[i+2] >> 6)) & 0x3F;
                block4 = s[i+2] & 0x3F;

                /* translate to printable characters */
                res[j++] = base64symbols[block1];
                res[j++] = base64symbols[block2];
                res[j++] = base64symbols[block3];
                res[j++] = base64symbols[block4];
        }

        /* characters left to be encoded, padding char is '=' */
        if ((i - slen) % 3 != 0) {
                res[j++] = base64symbols[(s[i] >> 2) & 0x3F];
                if (i == (slen - 1)) {
                        res[j++] = base64symbols[((s[i] & 0x3) << 4)];
                        res[j++] = '=';
                } else {
                        res[j++] = base64symbols[((s[i] & 0x3) << 4) |
                                ((s[i+1] & 0xF0) >> 4)];
                        res[j++] = base64symbols[((s[i+1] & 0xF) << 2)];
                }
                res[j++] = '=';
        }
        res[j] = '\0';

        return res;
}

#ifdef DEBUG
int
main()
{
        char* str[] = {
                "123456789",
                "1234567890",
                "13410425@foad.iedparis8.net",
                "abcdefghi",
                "A0b1C3d4",
                "cet algorithme fonctionne-t-il ?",
                "=_test_!*@/-ésotériqueè?zZ^",
                NULL
        };

        puts("=== TO BASE64 ===");
        int i;
        for (i = 0; str[i]; i++) {
                printf("to_base64: %s => %s\n", str[i], to_base64(str[i]));
        }

        return 0;
}
#endif
