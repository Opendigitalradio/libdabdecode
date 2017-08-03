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

