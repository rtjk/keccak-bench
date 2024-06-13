#pragma once

#include "../keccak/cross/fips202.h"

#include "../keccak/cross/fips202.c"
#include "../keccak/cross/keccakf1600.c"

#define XOF_STATE cross_shake256incctx

/* ************************************************************************************* */

static inline
void xof_init(XOF_STATE *state) {
    cross_shake256_inc_init(state);
}

static inline
void xof_absorb(XOF_STATE *state, const unsigned char *input, unsigned int inputByteLen) {
    cross_shake256_inc_absorb(state, (const uint8_t *)input, inputByteLen);
}

static inline
void xof_finalize(XOF_STATE *state) {
    cross_shake256_inc_finalize(state);
}

static inline
void xof_squeeze(XOF_STATE *state, unsigned char *output, unsigned int outputByteLen) {
    cross_shake256_inc_squeeze(output, outputByteLen, state);
}

static inline
void xof_release(XOF_STATE *state) {
    //shake256_inc_release(state);
}


/* ************************************************************************************* */

static inline
void xof_cycle(
    const unsigned char *input, unsigned int inputByteLen, 
    unsigned char *output, unsigned int outputByteLen) {

    XOF_STATE state;

    xof_init(&state);
    xof_absorb(&state, input, inputByteLen);
    xof_finalize(&state);
    xof_squeeze(&state, output, outputByteLen);
    xof_release(&state);
}

/* ************************************************************************************* */
/* ************************************************************************************* */


#include "../keccak/qtesla/fips202x4.h"

#include "../keccak/qtesla/fips202x4.c"
#include "../keccak/qtesla/keccak4x/KeccakP-1600-times4-SIMD256.c"

#define XOF_X4_STATE __m256i

static inline
void xof_x4_cycle(
    const unsigned char *in1,
    const unsigned char *in2,
    const unsigned char *in3,
    const unsigned char *in4,
    unsigned int inLen, 
    unsigned char *out1,
    unsigned char *out2,
    unsigned char *out3,
    unsigned char *out4, 
    unsigned int outLen) {

    XOF_X4_STATE state[25]; //////////////////////////// <-------------
    
    for (int i = 0; i < 25; i++)
        state[i] = _mm256_xor_si256(state[i], state[i]); // zero state

    keccak_absorb4x(state, SHAKE256_RATE, in1, in2, in3, in4, inLen, 0x04);
    keccak_squeezeblocks4x(out1, out2, out3, out4, outLen/SHAKE256_RATE, state, SHAKE256_RATE);
    
    }



/* ************************************************************************************* */

/*
#include "../keccak/rbcabral/keccak.h"

#include "../keccak/rbcabral/keccak_mul_all.c"
#include "../keccak/rbcabral/sha3_readble.c"

*/

/* ************************************************************************************* */
