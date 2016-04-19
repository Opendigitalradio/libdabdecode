#include "ensemble/ensemble.h"

#include <fstream>
#include <iostream>

int main()
  {
  auto syncStream = std::ifstream{"data/syn", std::ios::binary};
  auto dataStream = std::ifstream{"data/dat", std::ios::binary};

  if(!syncStream)
    {
    std::cerr << "Could not open frame stream!\n";
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
      std::cout << "Ensemble \"" << ensemble.name() << "\" @ " << std::hex << ensemble.id() << '\n';
      }

    ensemble.update();
    }

  }

