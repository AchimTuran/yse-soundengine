/*
  ==============================================================================

    device.hpp
    Created: 10 Apr 2014 2:43:14pm
    Author:  yvan

  ==============================================================================
*/

#ifndef DEVICEINTERFACE_HPP_INCLUDED
#define DEVICEINTERFACE_HPP_INCLUDED
#include <string>
#include <vector>
#include "../classes.hpp"
#include "../yse.hpp"

// TODO: this should be removed at some point. We don't want any juce references in the public interface
namespace juce {
  class AudioIODevice;
}

namespace YSE {
  namespace DEVICE {

    class API interfaceObject {
    public:
      interfaceObject(juce::AudioIODevice * pimpl);

      const char * getName() const;
      const char * getTypeName() const;

      // These functions cannot be used if YSE is compiled as DLL, because
      // you can't pass a vector if this is the case.
      const std::vector<std::string> & getOutputChannelNames() const;
      const std::vector<std::string> & getInputChannelNames() const;
      const std::vector<double> & getAvailableSampleRates() const;
      const std::vector<int> & getAvailableBufferSizes() const;

      // use these instead.
      UInt getNumOutputChannelNames() const;
      const char * getOutputChannelName(UInt nr) const;

      UInt getNumInputChannelNames() const;
      const char * getInputChannelName(UInt nr) const;

      UInt getNumAvailableSampleRates() const;
      double getAvailableSampleRate(UInt nr) const;

      UInt getNumAvailableBufferSizes() const;
      Int getAvailableBufferSize(UInt nr) const;

      int getDefaultBufferSize() const;
      int getOutputLatency() const;
      int getInputLatency() const;

    private:
      std::vector<std::string> outputChannelNames;
      std::vector<std::string> inputChannelNames;
      std::vector<double> sampleRates;
      std::vector<int> bufferSizes;

      juce::AudioIODevice * pimpl;

      friend class DEVICE::managerObject;
    };
  }

  
}



#endif  // DEVICE_HPP_INCLUDED
