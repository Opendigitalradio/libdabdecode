#include "ensemble/service.h"
#include "ensemble/service_component.h"

namespace dabdecode
  {

  service::service(std::uint32_t const id, bool const isLocal)
    : m_id{id},
      m_isLocal{isLocal}
    {

    }

  bool service::operator<(service const & other) const
    {
    return m_id < other.m_id;
    }

  std::uint32_t service::id() const
    {
    return m_id;
    }

  void service::add(service_component && component)
    {
    m_components.insert(std::move(component));
    }

  }

