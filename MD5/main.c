/* 
Niema Attarian - MD5 Hashing Algorithm 
*
*
Compile and run the code using the following:
    - make main
    - ./main {text}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*  
    Code has been adapted from https://en.wikipedia.org/wiki/MD5#Pseudocode  
    These will contain the hash  
*/
uint32_t hash0, hash1, hash2, hash3;

void md5(uint8_t *initial_message){ /* This md5 function takes in parameters of any initial messgae of any length */
    
    size_t initial_length = strlen(initial_message);    /* takes in the message as an argument and returns its length */
    
    /* Preparing the message */
    uint8_t *message = NULL;
    /*  
        Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating 
        s specifies the per-round shift amounts  
    */
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

    /*  
        Padding  
        The initial step of allocating "1" bit to the message
        followed by a number of "0" bits until the length is congruent to 488, modulo 512 in bits
    */

    /*  
        Adapted from https://gist.github.com/creationix/4710780
        Appending the "1" bit 
    */
    int new_length = ((((initial_length + 8) / 64) + 1) * 64) - 8;

    /* Appending the "0" bits (allocating 64 extra bytes) */
    message = calloc(new_length + 64, 1);   /* calloc() allocates the memory and also initializes the allocated memory block to zero. */

    memcpy(message, initial_message, initial_length);

    /* Writing the "1" bit to the message */
    message[initial_length] = 128;

    /* 
        Appending the length
        Adding the initial bit message input at the end of the buffer in the form of 64-bit representation 
    */
    uint32_t bits_length = 8*initial_length;
    memcpy(message + new_length, &bits_length, 4); /* Creates a memory block copy */

    /*
        x >> y - Shifting the x value to the right y bits
        x << y - Shifting the x value to the left y bits

        This function rotates x values left n-number of bits 
    */
    #define LEFT_ROTATE_FUNCTION(x, n) (((x) << (n)) | ((x) >> (32-(n))))

    /* Process Message in 16-word blocks */
    for(int chunk = 0; chunk < new_length; chunk += 64)
    {
        /* Break chunk into sixteen 32-bit words M[j], 0 ≤ j ≤ 15 */
        uint32_t *M = (uint32_t *) (message + chunk);
        // char M[64];
        // M[64] = '\0';
        // strncpy(M, &new_length[chunk*64], 64);
        // printf("Chunk(no: %d) %s\n", chunk, M);

        /* Initialising the MD Buffer */
        uint32_t A = hash0;
        uint32_t B = hash1;
        uint32_t C = hash2;
        uint32_t D = hash3;

        /* Main loop */
        int32_t i;
        for(i = 0; i<64; i++) {
            
            int32_t F, g;

            /* Defining the auxiliary functions that take input of three 32-bit words
                & - bit-wise AND
                | - bit-wise OR
                ~ - bit-wise NOT
                ^ - bit-wise NOT EQUALS TO
            */

            if(0 <= i <= 15){
                F = (B & C) | ((~B) & D);   /* (B and C) or ((not B) and D) */
                g = i;
            }
            else if(16 <= i <= 31){
                F = (D & B) | ((~D) & C);   /* (D and B) or ((not D) and C) */
                g = (5*i + 1) % 16;
            }
            else if(32 <= i <= 47){
                F = B ^ C ^ D;              /* B xor C xor D */
                g = (3*i + 5) % 16;
            }
            else if(48 <= i <= 63){
                F = C ^ (B | (~D));         /* C xor (B or (not D)) */
                g = (7*i) % 16;
            }

            /* M[g] must be a 32-bits block */
            F = F + A + K[i] + M[g];
            A = D;
            D = C;
            C = B;
            B = B + LEFT_ROTATE_FUNCTION(F, s[i]);

        }// end main loop

        /* Add this chunk's hash to results so far */
        hash0 = hash0 + A;
        hash1 = hash1 + B;
        hash2 = hash2 + C;
        hash3 = hash3 + D;

    } // end for

} // MD5

int main(int argc, char *argv[]) {

    // FILE *infile;
    // char c;
    
    // /* Return error if single file name isn't given  */
    // if (argc != 2){
    //     printf("Error: expected single filename as arguemnt.\n");
    //     return 1;
    // }

    // /* Reads in the file as a binary file  */
    // /* Opening the File */
    // infile = fopen(argv[1], "rb");
    
    // /* Error if file cannot be opened  */
    // if(!infile) {
    //     printf("Error: couldn't open file %s. \n", argv[1]);
    //     return 1;
    // }

    // /* Read contents of the file */
    // c = fgetc(infile); 
    // printf ("======   The contents of the file    ======\n"); 
    // while (c != EOF) 
    // { 
    //     /* Prints the contents of file to console */
    //     printf ("%c", c); 
    //     c = fgetc(infile); 
    // } 
    // printf ("\n"); 

    /* var char digest[16] := hash0, append hash1, append hash2, append hash3 (Output is in little-endian) */
    char *message = argv[1];
 
    /* Calling the MD5 function and parameters */
    md5(message);

    uint8_t *append;

    /* Display hashed output */
    printf ("\n====== The hashed output of the file ======\n"); 
    append=(uint8_t *)&hash0;
    printf("%2.2x%2.2x%2.2x%2.2x", append[0], append[1], append[2], append[3], hash0);
    append=(uint8_t *)&hash1;
    printf("%2.2x%2.2x%2.2x%2.2x", append[0], append[1], append[2], append[3], hash1);
    append=(uint8_t *)&hash2;
    printf("%2.2x%2.2x%2.2x%2.2x", append[0], append[1], append[2], append[3], hash2);
    append=(uint8_t *)&hash3;
    printf("%2.2x%2.2x%2.2x%2.2x", append[0], append[1], append[2], append[3], hash3);
    
    printf("\n");
    /* close the file  */
    // fclose(infile);

    return 0;
}

// Input:   a
// Output:  ab3efa27f761a726f6974bc1366fe7d0