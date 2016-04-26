#include "ensemble/ensemble.h"

#include <fstream>
#include <iostream>

int main()
  {
  auto syncStream = std::ifstream{"data/syn", std::ios::binary};
  auto dataStream = std::ifstream{"data/dat", std::ios::binary};

  if(!syncStream)
    {
    std::cerr << "Could not open synchronization stream!\n";
    return 1;
    }

  if(!dataStream)
    {
    std::cerr << "Could not open frame stream!\n";
    return 1;
    }

  auto ensemble = dabdecode::ensemble{syncStream, dataStream};

  while(syncStream && dataStream)
    {
    if(ensemble)
      {
      std::cout << "Ensemble \"" << ensemble.label() << "\" @ " << ensemble.id() << '\n';

      for(auto const & service : ensemble.services())
        {
        std::cout << "\t Service " << service.id() << '\n';
        }
      }

    ensemble.update();
    }

  }

