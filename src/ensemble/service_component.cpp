#include "ensemble/service_component.h"

namespace dabdecode
  {

  service_component::service_component(std::uint16_t const id, constants::transport_mechanism const transport,
                                       bool const isPrimary, bool const caApplies)
    : m_id{id},
      m_transport{transport},
      m_isPrimary{isPrimary},
      m_caApplies{caApplies}
    {
    if(transport == constants::transport_mechanism::stream_audio || transport == constants::transport_mechanism::package_data)
      {
      m_subchannelId = id & 63;
      m_type = (id >> 6) & 63;
      }
    }

  std::uint16_t service_component::id() const
    {
    return m_id;
    }

  constants::transport_mechanism service_component::transport() const
    {
    return m_transport;
    }

  bool service_component::primary() const
    {
    return m_isPrimary;
    }

  bool service_component::ca_applies() const
    {
    return m_caApplies;
    }

  std::uint8_t service_component::subchannel() const
    {
    return m_subchannelId;
    }

  std::uint8_t service_component::type() const
    {
    return m_type;
    }

  bool service_component::operator<(service_component const & other) const
    {
    return m_id < other.m_id;
    }

  bool service_component::operator==(service_component const & other) const
    {
    return m_id == other.m_id;
    }

  void service_component::subchannel(std::uint8_t const id)
    {
    m_subchannelId = id;
    }

  void service_component::type(std::uint8_t const type)
    {
    m_type = type;
    }

  }

