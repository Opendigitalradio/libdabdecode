#include "mode/modes.h"

#include <stdexcept>

namespace dabdecode
  {

  namespace
    {

    [[noreturn]] void throw_invalid_mode(std::size_t const mode)
      {
      throw std::logic_error{std::string{"Invalid mode number "} + std::to_string(mode)};
      }

    }

  std::size_t frame_size(std::size_t const mode)
    {
    switch(mode)
      {
      case 1:
        return mode_1::symbol_bits::value * mode_1::frame_symbols::value;
        break;
      case 2:
        return mode_2::symbol_bits::value * mode_2::frame_symbols::value;
        break;
      case 3:
        return mode_3::symbol_bits::value * mode_3::frame_symbols::value;
        break;
      case 4:
        return mode_4::symbol_bits::value * mode_4::frame_symbols::value;
        break;
      default:
        throw_invalid_mode(mode);
      }
    }

  std::size_t fic_size(std::size_t const mode)
    {
    switch(mode)
      {
      case 1:
        return mode_1::symbol_bits::value * mode_1::fic_symbols::value;
        break;
      case 2:
        return mode_2::symbol_bits::value * mode_2::fic_symbols::value;
        break;
      case 3:
        return mode_3::symbol_bits::value * mode_3::fic_symbols::value;
        break;
      case 4:
        return mode_4::symbol_bits::value * mode_4::fic_symbols::value;
        break;
      default:
        throw_invalid_mode(mode);
      }
    }

  std::size_t punctured_codeword_size(std::size_t const mode)
    {
    switch(mode)
      {
      case 1:
        return mode_1::fib_codeword_bits::value * 3;
        break;
      case 2:
        return mode_2::fib_codeword_bits::value * 3;
        break;
      case 3:
        return mode_3::fib_codeword_bits::value * 3;
        break;
      case 4:
        return mode_4::fib_codeword_bits::value * 3;
        break;
      default:
        throw_invalid_mode(mode);
      }
    }

  std::size_t fic_codeword_size(std::size_t const mode)
    {
    switch(mode)
      {
      case 1:
        return mode_1::fib_codeword_bits::value;
        break;
      case 2:
        return mode_2::fib_codeword_bits::value;
        break;
      case 3:
        return mode_3::fib_codeword_bits::value;
        break;
      case 4:
        return mode_4::fib_codeword_bits::value;
        break;
      default:
        throw_invalid_mode(mode);
      }
    }

  std::size_t fibs_in_codeword(std::size_t const mode)
    {
    switch(mode)
      {
      case 1:
        return mode_1::fib_codeword_bits::value / 256;
        break;
      case 2:
        return mode_2::fib_codeword_bits::value / 256;
        break;
      case 3:
        return mode_3::fib_codeword_bits::value / 256;
        break;
      case 4:
        return mode_4::fib_codeword_bits::value / 256;
        break;
      default:
        throw_invalid_mode(mode);
      }
    }

  }

