#ifndef __DABDECODE_CONSTANTS__CONVOLUTION_ENCODER_ATTRIBUTES
#define __DABDECODE_CONSTANTS__CONVOLUTION_ENCODER_ATTRIBUTES

#include <array>
#include <cstdint>

namespace dabdecode
  {

  /*
   * @internal
   *
   * The length of the convolution encoder input as defined in ETSI EN 300 401 Section 11.1.1
   */
  constexpr int kEncoderInputLength{1};

  /*
   * @internal
   *
   * The length of the convolution encoder output as defined in ETSI EN 300 401 Section 11.1.1
   */
  constexpr int kEncoderOutputLength{4};

  /*
   * @internal
   *
   * The polynomials of the convolution encoder as defined in ETSI EN 300 401 Section 11.1.1
   */
  constexpr std::array<int, 4> kEncoderPolynomials {{
    0133, 0171, 0145, 0133
  }};

  /*
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

