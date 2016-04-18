#include "frame/fib/fig/figs.h"

namespace dabdecode
  {

  fig::fig(std::vector<uint8_t> const & data)
    : m_dataField{data.cbegin(), data.cend()}
    {

    }

  std::size_t fig::length() const
    {
    return m_dataField.size();
    }

  std::shared_ptr<extension> fig::extension() const
    {
    return m_extension;
    }

  std::shared_ptr<fig> make_fig(std::vector<uint8_t> const & data)
    {
    auto type = (data[0] >> 5) & 7;
    auto length = data[0] & 31;

    auto beginIterator = data.cbegin() + 1;
    auto endIterator = beginIterator + length;

    switch(type)
      {
      case 0:
        return std::make_shared<fig_0>(std::vector<uint8_t>{beginIterator, endIterator});
      case 1:
        return std::make_shared<fig_1>(std::vector<uint8_t>{beginIterator, endIterator});
      default:
        return std::make_shared<fig>(std::vector<uint8_t>{beginIterator, endIterator});
      }
    }

  }

