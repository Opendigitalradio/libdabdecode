#include "mode/modes.h"

#include <stdexcept>

namespace dabdecode
  {

  using namespace constants;

  std::size_t frame_size(transport_mode const mode) noexcept
    {
    switch(mode)
      {
      case transport_mode::mode_1:
        return mode_1::symbol_bits::value * mode_1::frame_symbols::value;
        break;
      case transport_mode::mode_2:
        return mode_2::symbol_bits::value * mode_2::frame_symbols::value;
        break;
      case transport_mode::mode_3:
        return mode_3::symbol_bits::value * mode_3::frame_symbols::value;
        break;
      case transport_mode::mode_4:
        return mode_4::symbol_bits::value * mode_4::frame_symbols::value;
        break;
      }
    }

  std::size_t fic_size(transport_mode const mode) noexcept
    {
    switch(mode)
      {
      case transport_mode::mode_1:
        return mode_1::symbol_bits::value * mode_1::fic_symbols::value;
        break;
      case transport_mode::mode_2:
        return mode_2::symbol_bits::value * mode_2::fic_symbols::value;
        break;
      case transport_mode::mode_3:
        return mode_3::symbol_bits::value * mode_3::fic_symbols::value;
        break;
      case transport_mode::mode_4:
        return mode_4::symbol_bits::value * mode_4::fic_symbols::value;
        break;
      }
    }

  std::size_t punctured_codeword_size(transport_mode const mode) noexcept
    {
    switch(mode)
      {
      case transport_mode::mode_1:
        return mode_1::fib_codeword_bits::value * 3;
        break;
      case transport_mode::mode_2:
        return mode_2::fib_codeword_bits::value * 3;
        break;
      case transport_mode::mode_3:
        return mode_3::fib_codeword_bits::value * 3;
        break;
      case transport_mode::mode_4:
        return mode_4::fib_codeword_bits::value * 3;
        break;
      }
    }

  std::size_t fic_codeword_size(transport_mode const mode) noexcept
    {
    switch(mode)
      {
      case transport_mode::mode_1:
        return mode_1::fib_codeword_bits::value;
        break;
      case transport_mode::mode_2:
        return mode_2::fib_codeword_bits::value;
        break;
      case transport_mode::mode_3:
        return mode_3::fib_codeword_bits::value;
        break;
      case transport_mode::mode_4:
        return mode_4::fib_codeword_bits::value;
        break;
      }
    }

  std::size_t fibs_in_codeword(transport_mode const mode) noexcept
    {
    switch(mode)
      {
      case transport_mode::mode_1:
        return mode_1::fib_codeword_bits::value / 256;
        break;
      case transport_mode::mode_2:
        return mode_2::fib_codeword_bits::value / 256;
        break;
      case transport_mode::mode_3:
        return mode_3::fib_codeword_bits::value / 256;
        break;
      case transport_mode::mode_4:
        return mode_4::fib_codeword_bits::value / 256;
        break;
      }
    }

  std::size_t frame_symbols(transport_mode const mode) noexcept
    {
    switch(mode)
      {
      case transport_mode::mode_1:
        return mode_1::frame_symbols::value;
        break;
      case transport_mode::mode_2:
        return mode_2::frame_symbols::value;
        break;
      case transport_mode::mode_3:
        return mode_3::frame_symbols::value;
        break;
      case transport_mode::mode_4:
        return mode_4::frame_symbols::value;
        break;
      }
    }

  std::size_t symbol_size(transport_mode const mode) noexcept
    {
    switch(mode)
      {
      case transport_mode::mode_1:
        return mode_1::carriers::value * 2;
        break;
      case transport_mode::mode_2:
        return mode_2::carriers::value * 2;
        break;
      case transport_mode::mode_3:
        return mode_3::carriers::value * 2;
        break;
      case transport_mode::mode_4:
        return mode_4::carriers::value * 2;
        break;
      }
    }

  }

