/*
  ==============================================================================

    ioDevice.h
    Created: 12 Jun 2014 6:43:05pm
    Author:  yvan

  ==============================================================================
*/

#ifndef IODEVICE_H_INCLUDED
#define IODEVICE_H_INCLUDED

#include <string>
#include <vector>
#include "ioCallback.h"
#include "../headers/defines.hpp"
#include "../headers/types.hpp"

namespace YSE {
  namespace IO {
    class ioDevice {
    public:
      virtual ~ioDevice();

      const std::wstring & getName() const { return name; }
      const std::wstring & getTypeName() const { return typeName; }

      virtual std::vector<std::wstring> getOutputChannelNames() = 0;
      virtual std::vector<std::wstring> getInputChannelNames() = 0;

      virtual std::vector<Dbl> getAvailableSampleRates() = 0;
      virtual std::vector<Int> getAvailableBufferSizes() = 0;
      virtual int getDefaultBufferSize() = 0;

      virtual std::wstring open(const int& inputChannels, const int &outputChannels, double sampleRate, int bufferSize) = 0;
      virtual void close() = 0;
      virtual bool isOpen() = 0;
      virtual void start(ioCallback * callback) = 0;
      virtual void stop() = 0;
      virtual void isPlaying() = 0;
      virtual std::wstring getLastError() = 0;
      virtual int getCurrentBufferSize() = 0;
      virtual double getCurrentSampleRate() = 0;
      virtual int getCurrentBitDepth() = 0;
      virtual int getActiveInputChannels() const = 0;
      virtual int getActiveOutputChannels() const = 0;
      virtual int getOutputLatency() = 0;
      virtual int getInputLatency() = 0;

      virtual bool enablePreprocessing(bool value);

    protected:
      ioDevice(const std::wstring & name, const std::wstring & type);

      std::wstring name, typeName;
    };
  }
}



#endif  // IODEVICE_H_INCLUDED
