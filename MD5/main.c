/* Niema Attarian - MD5 Hashing Algorithm */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* Code has been adapted from https://gist.github.com/creationix/4710780 and https://en.wikipedia.org/wiki/MD5  */
/* These will contain the hash  */
uint32_t hash0, hash1, hash2, hash3;



void md5(uint8_t *initial_msg, size_t initial_len){ /* This md5 function takes in parameters of any initial messgae of any length */
    /* Preparing the message */
    uint8_t *msg = NULL;
    
    /* Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating  */
    /* s specifies the per-round shift amounts  */
    uint32_t s[] = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };

    /* Use binary integer part of the sines of integers (in radians) as constants */
    const uint32_t K[] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    /* Initialize variables:  */
    hash0 = 0x67452301;   // A
    hash1 = 0xefcdab89;   // B
    hash2 = 0x98badcfe;   // C
    hash3 = 0x10325476;   // D

    /* Defining the auxiliary functions that take input of three 32-bit words */
    /*
        & - bit-wise AND
        | - bit-wise OR
        ~ - bit-wise NOT
        ^ - bit-wise TO THE POWER OF
        x >> y - Shifting the x value to the right y bits
        x << y - Shifting the x value to the left y bits
    */
    #define F(x, y, z) (((x) & (y)) | ((~x) & (z))) /* (X and Y) OR ((not X) and Y) */
    #define G(x, y, z) (((x) & (z)) | ((y) & (~z))) /* (X and Z) OR (Y and (not Z)) */
    #define H(x, y, z) ((x) ^ (y) ^ (z))            /* (X to the power of Y to the power of Z) */
    #define I(x, y, z) ((y) ^ ((x) | (~z)))         /* (Y to the power of (X or (not Z))) */

    /* This function rotates x values left n-number of bits */
    #define LEFT_ROTATE_FUNCTION(x, n) (((x) << (n)) | ((x) >> (32-(n))))


}


int main(int argc, char *argv[]) {

    /* Return error if single file name isn't given  */
    if (argc != 2){
        printf("Error: expected single filename as arguemnt.\n");
        return 1;
    }

    /* Reads in the file as a binary file  */
    FILE *infile = fopen(argv[1], "rb");
    /* Error if file cannot be opened  */
    if(!infile) {
        printf("Error: couldn't open file %s. \n", argv[1]);
        return 1;
    }

    /* close the file  */
    fclose(infile);

    return 0;
}
