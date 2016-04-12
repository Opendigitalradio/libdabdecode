#include "mode/modes.h"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/cute_suite.h>
#include <cute/xml_listener.h>
#include <cute/ide_listener.h>

void test_carriers_equals_768()
  {
  ASSERT_EQUAL(768, dabdecode::mode_4::carriers::value);
  }

void test_frame_symbols_equals_75()
  {
  ASSERT_EQUAL(75, dabdecode::mode_4::frame_symbols::value);
  }

void test_fic_symbols_equals_3()
  {
  ASSERT_EQUAL(3, dabdecode::mode_4::fic_symbols::value);
  }

void test_msc_symbols_equals_72()
  {
  ASSERT_EQUAL(72, dabdecode::mode_4::msc_symbols::value);
  }

void test_frame_fibs_equals_6()
  {
  ASSERT_EQUAL(6, dabdecode::mode_4::frame_fibs::value);
  }

void test_frame_cifs_equals_2()
  {
  ASSERT_EQUAL(2, dabdecode::mode_4::frame_cifs::value);
  }

void test_fib_codeword_bits_equals_768()
  {
  ASSERT_EQUAL(768, dabdecode::mode_4::fib_codeword_bits::value);
  }

int main(int argc, char * * argv)
  {
  auto testSuite = cute::suite{};

  testSuite += cute::test{test_carriers_equals_768, "Mode 4 should have 768 carriers"};
  testSuite += cute::test{test_frame_symbols_equals_75, "Mode 4 should have 75 symbols per frame"};
  testSuite += cute::test{test_fic_symbols_equals_3, "Mode 4 should have 3 symbols for the FIC"};
  testSuite += cute::test{test_msc_symbols_equals_72, "Mode 4 should have 72 symbols for the MSC"};
  testSuite += cute::test{test_frame_fibs_equals_6, "Mode 4 should have 6 FIBs per frame"};
  testSuite += cute::test{test_frame_cifs_equals_2, "Mode 4 should have 2 CIFs per frame"};
  testSuite += cute::test{test_fib_codeword_bits_equals_768, "Mode 4 should have 768 bits per FIB codeword"};

  auto xmlFile = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xmlFile.out};

  return !cute::makeRunner(listener, argc, argv)(testSuite, "DAB transfer mode 4 descriptor suite");
  }

