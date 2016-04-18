#include "mode/modes.h"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/cute_suite.h>
#include <cute/xml_listener.h>
#include <cute/ide_listener.h>

void test_carriers_equals_192()
  {
  ASSERT_EQUAL(192, dabdecode::constants::mode_3::carriers::value);
  }

void test_frame_symbols_equals_152()
  {
  ASSERT_EQUAL(152, dabdecode::constants::mode_3::frame_symbols::value);
  }

void test_fic_symbols_equals_8()
  {
  ASSERT_EQUAL(8, dabdecode::constants::mode_3::fic_symbols::value);
  }

void test_msc_symbols_equals_144()
  {
  ASSERT_EQUAL(144, dabdecode::constants::mode_3::msc_symbols::value);
  }

void test_frame_fibs_equals_4()
  {
  ASSERT_EQUAL(4, dabdecode::constants::mode_3::frame_fibs::value);
  }

void test_frame_cifs_equals_1()
  {
  ASSERT_EQUAL(1, dabdecode::constants::mode_3::frame_cifs::value);
  }

void test_fib_codeword_bits_equals_1024()
  {
  ASSERT_EQUAL(1024, dabdecode::constants::mode_3::fib_codeword_bits::value);
  }

int main(int argc, char * * argv)
  {
  auto testSuite = cute::suite{};

  testSuite += cute::test{test_carriers_equals_192, "Mode 3 should have 192 carriers"};
  testSuite += cute::test{test_frame_symbols_equals_152, "Mode 3 should have 152 symbols per frame"};
  testSuite += cute::test{test_fic_symbols_equals_8, "Mode 3 should have 8 symbols for the FIC"};
  testSuite += cute::test{test_msc_symbols_equals_144, "Mode 3 should have 144 symbols for the MSC"};
  testSuite += cute::test{test_frame_fibs_equals_4, "Mode 3 should have 4 FIBs per frame"};
  testSuite += cute::test{test_frame_cifs_equals_1, "Mode 3 should have 1 CIFs per frame"};
  testSuite += cute::test{test_fib_codeword_bits_equals_1024, "Mode 3 should have 124 bits per FIB codeword"};

  auto xmlFile = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xmlFile.out};

  return !cute::makeRunner(listener, argc, argv)(testSuite, "DAB transfer mode 3 descriptor suite");
  }

