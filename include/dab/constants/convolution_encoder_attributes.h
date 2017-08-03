#ifndef DABDECODE_CONSTANTS_CONVOLUTION_ENCODER_ATTRIBUTES
#define DABDECODE_CONSTANTS_CONVOLUTION_ENCODER_ATTRIBUTES

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

namespace dab
  {

  namespace internal
    {

    namespace constants
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
       * @brief The polynomials of the convolution encoder as defined in ETSI EN 300 401 Section 11.1.1
       *
       * These polynomials determine the encoders 'taps'. The encoder input bit is on the left, meaning that
       * shifting a new input bit, shifts the current content of the encoders shift register to the right.
       * Thus the taps are defined in such a way that the taps are defined by the bits in the polynomials from
       * the left to the right.
       *
       * @note The polynomials are defined in octal since that how they are represented in the standard.
       */
      constexpr std::array<int, 4> kEncoderPolynomials {{
        0133, 0171, 0145, 0133
      }};

      /**
       * @internal
       *
       * @brief The constraint length as defined in ETSI EN 300 401 Section 11.1.1
       *
       * The constraint length of the convolutional encoder specifies how many states the encoder has got.
       * This is specifically interesting since the standard requires the encoder to be emptied by shifting
       * in 0s.
       */
      constexpr int kEncoderConstraintLength{7};

      /**
       * @internal
       *
       * @brief The amount of memory the encoder posesses
       *
       * This constant represents the number of memory cells of the encoder. This constant is interesting, since
       * the number of tailbits of a codeword is a function of the number of memory cells.
       */
      constexpr int kEncoderMemorySize{kEncoderConstraintLength - 1};

      /**
       * @internal
       * @brief Normalized 4-bit parity lookup table
       *
       * The lookup table for expected symbols for the convolution decoder. Since we use softbits,
       * this table is "normalized" for softbits between around +-1.0f.
       *
       * @note These values were precomputed because C++11 does not allow non-const constexpr
       * non-static memberfunction in structs.
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

    }

  }

#endif

