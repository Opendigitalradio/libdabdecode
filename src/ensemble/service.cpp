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

#include "dab/ensemble/service.h"
#include "dab/ensemble/service_component.h"
#include "dab/ensemble/subchannel.h"

namespace dab
  {

  std::uint32_t service::id() const
    {
    return m_id;
    }

  service_type service::type() const
    {
    return m_type;
    }

  std::string const & service::label() const
    {
    return m_label;
    }

  std::shared_ptr<service_component> service::primary() const
    {
    return m_primaryComponent;
    }

  std::shared_ptr<service> service::make(std::uint32_t const id, bool const isLocal)
    {
    return std::shared_ptr<service>{new service{id, isLocal}};
    }

  service::service(std::uint32_t const id, bool const isLocal)
    : m_id{id},
      m_isLocal{isLocal}
    {

    }

  void service::add(std::shared_ptr<service_component> component)
    {
    if(component && m_components.find(component->id()) == m_components.cend())
      {
      m_components[component->id()] = component;
      }
    }

  void service::label(std::string && label)
    {
    m_label = std::move(label);
    }

  void service::type(service_type const type)
    {
    m_type = type;
    }

  void service::primary(std::shared_ptr<service_component> component)
    {
    m_primaryComponent = component;
    }

  void service::set_handler(std::function<void (std::vector<std::uint8_t>)> handler)
    {
    if(m_primaryComponent)
      {
      m_primaryComponent->subchannel()->set_handler(handler);
      }
    }

  }

