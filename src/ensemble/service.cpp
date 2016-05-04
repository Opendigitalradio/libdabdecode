#include "ensemble/service.h"
#include "ensemble/service_component.h"

namespace dabdecode
  {

  bool service::operator<(service const & other) const
    {
    return m_id < other.m_id;
    }

  bool service::operator==(service const & other) const
    {
    return m_id == other.m_id;
    }

  std::uint32_t service::id() const
    {
    return m_id;
    }

  constants::service_type service::type() const
    {
    return m_type;
    }

  service::service(std::uint32_t const id, bool const isLocal)
    : m_id{id},
      m_isLocal{isLocal}
    {

    }

  void service::add(service_component const & component)
    {
    m_components.insert(component.id());
    }

  void service::label(std::string && label)
    {
    m_label = std::move(label);
    }

  void service::type(constants::service_type const type)
    {
    m_type = type;
    }

  }

