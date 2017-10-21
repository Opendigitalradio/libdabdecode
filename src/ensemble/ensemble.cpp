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

#include "dab/ensemble/ensemble.h"
#include "dab/ensemble/service.h"
#include "dab/ensemble/service_component.h"

#include "dab/frame/cif.h"
#include "dab/frame/fib.h"

#include <dab/constants/transmission_modes.h>

#include <algorithm>
#include <chrono>
#include <cstring>
#include <thread>
#include <vector>

namespace dab
  {

  using namespace internal;
  using namespace internal::types;

  ensemble::ensemble(symbol_queue_t & symbols, transmission_mode const & mode)
    : m_symbolQueue{symbols},
      m_mode{mode}
    {
    }

  std::string const & ensemble::label() const
    {
    return m_label;
    }

  std::uint16_t ensemble::id() const
    {
    return m_id;
    }

  std::uint8_t ensemble::country() const
    {
    return m_id >> 12;
    }

  std::uint16_t ensemble::reference() const
    {
    return m_id & 0xFFF;
    }

  std::map<std::uint32_t, std::shared_ptr<service>> const & ensemble::services() const
    {
    return m_services;
    }

  void ensemble::label(std::string const & label)
    {
    m_label = label;
    }

  void ensemble::id(std::uint16_t const id)
    {
    m_id = id;
    }

  void ensemble::add(std::shared_ptr<subchannel> subchannel)
    {
    if(subchannel && m_subchannels.find(subchannel->id()) == m_subchannels.cend())
      {
      m_subchannels[subchannel->id()] = subchannel;
      }
    }

  void ensemble::add(std::shared_ptr<service> service)
    {
    if(service && m_services.find(service->id()) == m_services.cend())
      {
      m_services[service->id()] = service;
      }
    }

  void ensemble::add(std::shared_ptr<service_component> component)
    {
    if(component && m_components.find(component->id()) == m_components.cend())
      {
      m_components[component->id()] = component;
      }
    }

  void ensemble::activate(std::shared_ptr<service> const & service, std::function<void (std::vector<std::uint8_t>)> handler)
    {
    if(service && m_services.find(service->id()) != m_services.cend())
      {
      m_activeService = service;
      service->set_handler(handler);
      }
    }

  bool ensemble::update()
    {
    m_aborted = false;
    if(next_frame())
      {
      auto const & fic = m_frame->fic();
      m_ficParser.parse(fic);

      if(m_activeService)
        {
        auto const primaryComponent = m_activeService->primary();

        if(primaryComponent)
          {
          auto const subchannel =  primaryComponent->subchannel();

          auto const start = subchannel->start();
          auto const end = start + subchannel->size();

          for(auto const & cif : m_frame->msc())
            {
            subchannel->process(cif.begin() + start * constants::kCuBits, cif.begin() + end * constants::kCuBits);
            }
          }
        }

      return true;
      }
    else
      {
      if(!m_aborted)
        {
        m_id = 0;
        m_label = "";
        }
      return false;
      }
    }

  void ensemble::abort()
    {
    m_aborted = true;
    }

  ensemble::operator bool() const
    {
    return m_label.size() && m_id;
    }

  bool ensemble::next_frame()
    {
    auto symbol = std::vector<float>{};
    auto extracted = std::vector<std::vector<float>>(m_mode.frame_symbols);

    while(!m_symbolQueue.try_dequeue(extracted))
      {
      std::this_thread::sleep_for(std::chrono::microseconds{100});
      if(m_aborted)
        {
        return false;
        }
      }

    std::vector<float> bits(extracted.size() * extracted.front().size());
    std::size_t copied{};
    for(auto const & symbol : extracted)
      {
      std::memcpy(bits.data() + copied * symbol.size(), symbol.data(), sizeof(float) * symbol.size());
      ++copied;
      }

    m_frame = std::unique_ptr<frame>(new frame{std::move(bits), m_mode});
    return (bool)m_frame;
    }

  }
