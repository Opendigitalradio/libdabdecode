#include "ensemble/service_component.h"
#include "ensemble/subchannel.h"

namespace dab
  {
  std::uint16_t service_component::id() const
    {
    return m_id;
    }

  transport_mechanism service_component::transport() const
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

  std::shared_ptr<__internal_dabdecode::subchannel> service_component::subchannel() const
    {
    return m_subchannel;
    }

  std::uint8_t service_component::type() const
    {
    return m_type;
    }

  std::shared_ptr<service_component> service_component::make(std::uint16_t const id, transport_mechanism const transport,
                                                             bool const isPrimary, bool const caApplies)
    {
    return std::shared_ptr<service_component>(new service_component{id, transport, isPrimary, caApplies});
    }

  service_component::service_component(std::uint16_t const id, transport_mechanism const transport,
                                       bool const isPrimary, bool const caApplies)
    : m_id{id},
      m_transport{transport},
      m_isPrimary{isPrimary},
      m_caApplies{caApplies}
    {
    if(transport == transport_mechanism::stream_audio || transport == transport_mechanism::package_data)
      {
      m_subchannelId = id & 63;
      m_type = (id >> 6) & 63;
      }
    }

  void service_component::subchannel(std::shared_ptr<__internal_dabdecode::subchannel> subchannel)
    {
    if(subchannel)
      {
      m_subchannel = subchannel;
      m_subchannelId = subchannel->id();
      }
    }

  void service_component::type(std::uint8_t const type)
    {
    m_type = type;
    }

  }

