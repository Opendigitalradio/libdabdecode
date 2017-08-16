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

#ifndef DABDECODE_ENSEMBLE_SUBCHANNEL
#define DABDECODE_ENSEMBLE_SUBCHANNEL

#include "dab/constants/convolution_encoder_attributes.h"
#include "dab/viterbi/fsm.h"

#include <cstdint>
#include <memory>
#include <vector>
#include <functional>

namespace dab
  {

  struct ensemble;

  namespace internal
    {

    struct fic_parser;

    /**
     * @internal
     *
     * @brief This class represents a DAB subchannel
     *
     * A DAB subchannel transports the actual data of a Service Component (SC).
     * Each subchannel is associated with exactly one SC and contains the information
     * required to decode the data contained in the subchannel.
     */
    struct subchannel
      {
      /**
       * @internal
       *
       * @brief Get the ID of the subchannel
       */
      std::uint16_t id() const;

      /**
       * @internal
       *
       * @brief Get the start CU of the subchannel
       */
      std::uint16_t start() const;

      /**
       * @internal
       *
       * @brief Get the size in CUs of the subchannel
       */
      std::uint16_t size() const;

      /**
       * @internal
       *
       * @brief Get the bitrate of the subchannel
       */
      std::uint16_t bitrate() const;

      /**
       * @internal
       *
       * @brief Check if the subchannel uses Equal Error Protection (EEP)
       */
      bool isEep() const;

      /**
       * @internal
       *
       * @brief Get the EEP (see #isEep) protection level.
       *
       * @note The value returned by this function is only of significance if the subchannel
       * actually uses EEP.
       */
      std::uint8_t eepProtectionLevel() const;

      /**
       * @internal
       *
       * @brief Get the EEP (see #isEep) protection table.
       *
       * @note The value returned by this function is only of significance if the subchannel
       * actually uses EEP.
       */
      std::uint8_t eepProtectionTable() const;

      /**
       * @internal
       *
       * @brief Set the data handler
       */
      void set_handler(std::function<void (std::vector<std::uint8_t>)> handler);

      private:
        static std::shared_ptr<subchannel> make(std::uint16_t const id, std::uint16_t const start, std::uint16_t const size,
                                                std::uint16_t const bitrate, bool const isEep,
                                                std::uint16_t const eepProtectionLevel);
        /**
         * @internal
         *
         * @brief Construct a subchannel
         *
         * A subchannel is described by a variety of parameters that make it possible
         * to recover the data transported within it.
         *
         * @param id The subchannel id as defined in ETSI EN 300 401 Section 6.2.1
         * @param start The subchannels start address (CU) as defined in ETSI EN 300 401 Section 6.2.1
         * @param size The size in CUs of the subchannel calculated from the data contained in FIG 0/1
         * @param bitrate The bitrate of the subchannel also calculated from FIG 0/1
         * @param isEep A boolean flag determining if UEP or EEP is used for the subchannel
         * @param eepProtectionLevel The protection level of the subchannel if EEP is used
         *
         * @note In the case of Equal Error Protection (EEP) being used for the subchannel,
         * eepProtectionLevel contains the protection level that is used. Since two different
         * tables are used for the different protection level we need to encode which one is used.
         * This information is stored in the LSB of the "upper" byte of eepProtectionLevel.
         */
        subchannel(std::uint16_t  const id, std::uint16_t const start, std::uint16_t const size,
                   std::uint16_t const bitrate, bool const isEep, std::uint16_t const eepProtectionLevel);

        /**
         * @internal
         *
         * @brief Process the data in the range @p smaplesStart to @p samplesEnd exclusive
         */
        void process(std::vector<float>::const_iterator samplesStart, std::vector<float>::const_iterator samplesEnd);

        /**
         * @internal
         *
         * @brief Process EEP protected data
         */
        void process_eep();

        std::uint16_t const m_id;
        std::uint16_t const m_start;
        std::uint16_t const m_size;
        std::uint16_t const m_bitrate;
        bool const m_isEep;
        std::uint8_t const m_eepProtectionLevel;
        std::uint8_t const m_eepProtectionTable;

        std::vector<std::vector<float>> m_deinterleavingBuffer;
        std::vector<float> m_deinterleavedData{};

        fsm const m_fsm;

        std::vector<std::uint8_t> m_data{};
        std::uint8_t m_processedFragments{};

        std::function<void (std::vector<std::uint8_t>)> m_handler;

        friend ensemble;
        friend fic_parser;
      };

    }

  }

#endif
