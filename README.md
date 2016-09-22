libdabdecode
============

**libdabdecode** provides functions to decode DAB and DAB+ transmission frames.
Each transmission frame must be provided to **libdabdecode** as a series of
demodulated OFDM symbols (for example by employing **libdabdemod**).

After enough symbols have been consumed and could be decoded, the library
will provide access to the DAB/DAB+ ensemble. Through the ensemble, the
services that are transported in the data stream can be selected and decoded.

Code example:
-------------

```cpp
#include <dabdecode.h>
#include <types/common_types.h>

#include <iostream>
#include <stdexcept>

int main(int argc, char * * argv)
  {
  using namespace dab::literals;

  dab::symbol_queue_t symbols{};

  /*
   * Asynchronously fill the symbol buffer
   */

  auto ensemble = dab::ensemble{symbols, dab::transmission_modes::kTransmissionMode1};

  // Read symbols until the ensemble could be decoded or updating failed
  while(!ensemble && emsemble.update());

  if(!ensemble)
    {
    throw std::runtime_error{"Failed to acquire ensemble!"};
    }

  for(auto const & service : ensemble.services())
    {
    if(service.second->type() == dab::service_type::data)
      {
      std::cout << "Activating first data service\n";

      ensemble.activate(service.second, [&](dab::byte_vector_t const & data) {
        std::cout << "received " << data.size() << " bytes.\n";
      });
      }
    }

  while(ensemble.update());

  // Updating failed. Stop execution
  }
```

Building:
---------

You first need to check out the source code and the respective submodules:

```
$ git clone --recursive https://github.com/Opendigitalradio/libdabdecode.git
```

Like the other members of the **libdabXYZ** family, **libdabdecode** uses CMake
as it build environment. There are several configuration option that
you can choose from when building **libdabdecode**:

| Option                         | Default | Comment                                                 |
| ------------------------------ | ------- | ------------------------------------------------------- |
| `BUILD_DOCUMENTATION`          | **OFF**     | Build the **libdabdecode** documentation.                   |
| `BUILD_DOCUMENTATION_ONLY`     | **OFF**     | Only build the documentation.                           |
| `BUILD_INTERNAL_DOCUMENTATION` | **OFF**     | Generate the developer documentation.                   |
| `CMAKE_BUILD_TYPE`             | **Debug**   | The type of binary to produce.                          |
| `DOCUMENTATION_FOR_THESIS`     | **OFF**     | Build the documentation for the inclusion in the thesis |
| `WITH_ADDRESS_SANITIZER`       | **OFF**     | Include additional memory checks (**slow**)                 |
| `WITH_COMMON_TESTS`            | **OFF**      | Build and run the common library tests.                |
| `WITH_UNDEFINED_SANITIZER`     | **OFF**     | Check for undefined behavior.                           |

To build the library, enter the `build` directory and run cmake or ccmake to
configure the build environment to you liking. Afterward, you can use
`cmake --build .` to build the library. Depending on your selection, the built
library will be in the directory `products/{Debug|Release}/lib`. If you chose
to build the documentation, the pdf will be found in
`dabdecode_doc/latex/refman.pdf`.

You can use this library as a subproject in any CMake based project.
