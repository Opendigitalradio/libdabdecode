#include "frame.h"

#include <vector>
#include <fstream>
#include <iostream>


std::vector<float> get_frame(std::ifstream & sync, std::ifstream & data)
  {
  auto didSync   = '\0';
  auto skipWidth = std::size_t{};
  auto extracted = std::vector<float>(sizeof(float) * 1536 * 2 * 75);
  auto iptr = reinterpret_cast<char *>(extracted.data());

  while(sync >> didSync && !didSync)
    {
    ++skipWidth;
    }

  data.ignore(sizeof(float) * 1536 * 2 * skipWidth);
  data.read(iptr, sizeof(float) * 1536 * 2);

  for(std::intmax_t symbol{1}; symbol < 75; ++symbol)
    {
    if(!data.read(iptr + symbol * sizeof(float) * 1536 * 2, sizeof(float) * 1536 * 2))
      {
      throw std::ios::failure{"Premature end of data stream"};
      }

    if(!sync.ignore(1 * sizeof(didSync)))
      {
      throw std::ios::failure{"Premature end of sync stream"};
      }
    }

  return extracted;
  }

int main() try
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

    while(syncStream && dataStream)
      {
      auto frame = dabdecode::frame{get_frame(syncStream, dataStream), 1};
      auto fic = frame.fic();

      for(auto const & fib : fic)
        {
        if(fib)
          {
          std::cout << "CRC OK\n";
          }
        }
      }

  }
catch(...)
  {

  }

