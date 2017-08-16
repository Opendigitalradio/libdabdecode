/*
 * Copyright (C) 2017 Opendigitalradio (http://www.opendigitalradio.org/)
 * Copyright (C) 2017 Felix Morgner <felix.morgner@hsr.ch>
 * Copyright (C) 2017 Tobias Stauber <tobias.stauber@hsr.ch>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DABDECODE_CONSTANTS_CHANNEL_SIZE_TABLES
#define DABDECODE_CONSTANTS_CHANNEL_SIZE_TABLES

#include <array>
#include <cstdint>

namespace dab
  {

  namespace internal
    {

    namespace constants
      {

      /**
       * @internal
       *
       * @brief An element of the subchannel descriptor table #kUepSubchannelDescriptors
       *
       * Objects of this type represent a subchannel descriptor for a given bitrate
       * and protection level. These objects are used to determine the size of a
       * subchannel for any given configuration.
       *
       * @see dabdecode::constants::kUepSubchannelDescriptors
       */
      struct uep_subchannel_descriptor
        {
        /**
         * @internal
         *
         * @brief The size of the subchannel
         *
         * This member represents the size of the subchannel in Capacity Units (CU)
         */
        std::uint16_t const size;

        /**
         * @internal
         *
         * @brief The protection level
         *
         * This member represents the protection level associated used on this subchannel
         */
        std::uint8_t const protectionLevel;


        /**
         * @internal
         *
         * @brief The bitrate
         *
         * This member contains the bitrate of the subchannel in kbit/s.
         */
        std::uint16_t const bitrate;
        };

      /**
       * @internal
       *
       * @brief The standard table of subchannel descriptors
       *
       * This array represents Table 6 of ETSI EN 300 401 Section 6.2.1. It is used
       * to look up the channel size for a give short-form table index. Note that, in
       * accordance with the standard, some entries are "missing", meaning they would
       * represent an invalid configuration and are therefore left out in the standard.
       * There exists however no holes! Each spot in the table is occupied, and thus
       * the complete table is linearly addressable.
       */
      constexpr std::array<uep_subchannel_descriptor, 64> kUepSubchannelDescriptors {{
        { 16, 5, 32 }, { 21, 4, 32 }, { 24, 3, 32 }, { 29, 2, 32 }, { 35, 1, 32 },
        { 24, 5, 48 }, { 29, 4, 48 }, { 35, 3, 48 }, { 42, 2, 48 }, { 52, 1, 48 },
        { 29, 5, 56 }, { 35, 4, 56 }, { 42, 3, 56 }, { 52, 2, 56 },
        { 32, 5, 64 }, { 42, 4, 64 }, { 48, 3, 64 }, { 58, 2, 64 }, { 70, 1, 64 },
        { 40, 5, 80 }, { 52, 4, 80 }, { 58, 3, 80 }, { 70, 2, 80 }, { 84, 1, 80 },
        { 48, 5, 96 }, { 58, 4, 96 }, { 70, 3, 96 }, { 84, 2, 96 }, {104, 1, 96 },
        { 58, 5, 112}, { 70, 4, 112}, { 84, 3, 112}, {104, 2, 112},
        { 64, 5, 128}, { 84, 4, 128}, { 96, 3, 128}, {116, 2, 128}, {140, 1, 128},
        { 80, 5, 160}, {104, 4, 160}, {116, 3, 160}, {140, 2, 160}, {168, 1, 160},
        { 96, 5, 192}, {116, 4, 192}, {140, 3, 192}, {168, 2, 192}, {208, 1, 192},
        {116, 5, 224}, {140, 4, 224}, {168, 3, 224}, {208, 2, 224}, {232, 1, 224},
        {128, 5, 256}, {168, 4, 256}, {192, 3, 256}, {232, 2, 256}, {280, 1, 256},
        {160, 5, 320}, {208, 4, 320},                {280, 2, 320},
        {192, 5, 384},                {280, 3, 384},                {416, 1, 384},
      }};

      /**
       * @internal
       *
       * @brief A function to "look up" eep bitrates
       *
       * Technically this is no table, but it is a very compact and useful function to
       * translate a combination of FIG 0/1 options, sizes and protection levels into
       * the corresponding bitrate. The tables from which this function has been derived
       * are documented as Table 7 and Table 8 in ETSI EN 300 401 Section 6.2.1.
       *
       * @param option The FIG 0/1 long-form subchannel descriptor option
       * @param size The FIG 0/1 long-form subchannel descriptor size in CUs
       * @param level The FIG 0/1 long-form subchannel descriptor protection level
       */
      constexpr std::uint16_t eep_table_bitrate(std::uint8_t const option, std::uint16_t const size, std::uint8_t const level)
        {
        return !option ?
                       (size * 8 / (!level ? 12 : level == 1 ? 8 : level == 2 ?  6 : 4))
                       :
                       (size * 32 / (!level ? 27 : level == 1 ? 21 : level == 2 ? 18 : 15));
        }

      }

    }

  }

#endif
