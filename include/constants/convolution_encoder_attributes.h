#ifndef __DABDECODE_CONSTANTS__CONVOLUTION_ENCODER_ATTRIBUTES
#define __DABDECODE_CONSTANTS__CONVOLUTION_ENCODER_ATTRIBUTES

#include <array>
#include <cstdint>

/**
 * @file
 * @author Felix Morgner
 * @copyright 3-Clause-BSD
 *
 * @brief This file contains constants derived from the DAB standard that apply to the convolution encode/decoder
 *
 * DAB uses convolution encoding to provide forward error correction. The basic properties of the encoder that are
 * always the same are collected in this file. Note that the decoder can be derived from the encoders properties.
 */

namespace dabdecode
  {

/**
 * @internal
 *
 * @brief The length of the convolution encoder input as defined in ETSI EN 300 401 Section 11.1.1
 *
 * The encoder consumes dabdecode#kEncoderInputLength bits and produces dabdecode#kEncoderOutputLength parity
 * bits. This is done in oder to achieve redundancy before transmission since this hardens the data against
 * transmission errors.
 */
  constexpr int kEncoderInputLength{1};

/**
 * @internal
 *
 * @brief The length of the convolution encoder output as defined in ETSI EN 300 401 Section 11.1.1
 * @see dabdecode#kEncoderInputLength
 */
  constexpr int kEncoderOutputLength{4};

  /**
   * @internal
   *
   * The polynomials of the convolution encoder as defined in ETSI EN 300 401 Section 11.1.1
   */
  constexpr std::array<int, 4> kEncoderPolynomials {{
    0133, 0171, 0145, 0133
  }};

  /**
   * @internal
   *
   * The lookup table for expected symbols for the convolution decoder. Since we use softbits,
   * this table is "normalized" for softbits between around +-1.0f.
   */
  constexpr std::array<float, 64> kDecoderLookupTable {{
     0.7071067691,  0.7071067691,  0.7071067691,  0.7071067691,
     0.7071067691,  0.7071067691,  0.7071067691, -0.7071067691,
     0.7071067691,  0.7071067691, -0.7071067691,  0.7071067691,
     0.7071067691,  0.7071067691, -0.7071067691, -0.7071067691,
     0.7071067691, -0.7071067691,  0.7071067691,  0.7071067691,
     0.7071067691, -0.7071067691,  0.7071067691, -0.7071067691,
     0.7071067691, -0.7071067691, -0.7071067691,  0.7071067691,
     0.7071067691, -0.7071067691, -0.7071067691, -0.7071067691,
    -0.7071067691,  0.7071067691,  0.7071067691,  0.7071067691,
    -0.7071067691,  0.7071067691,  0.7071067691, -0.7071067691,
    -0.7071067691,  0.7071067691, -0.7071067691,  0.7071067691,
    -0.7071067691,  0.7071067691, -0.7071067691, -0.7071067691,
    -0.7071067691, -0.7071067691,  0.7071067691,  0.7071067691,
    -0.7071067691, -0.7071067691,  0.7071067691, -0.7071067691,
    -0.7071067691, -0.7071067691, -0.7071067691,  0.7071067691,
    -0.7071067691, -0.7071067691, -0.7071067691, -0.7071067691
  }};

  }

#endif

