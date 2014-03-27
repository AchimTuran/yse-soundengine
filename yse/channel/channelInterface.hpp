/*
  ==============================================================================

    channel.h
    Created: 30 Jan 2014 4:20:50pm
    Author:  yvan

  ==============================================================================
*/

#ifndef CHANNELINTERFACE_H_INCLUDED
#define CHANNELINTERFACE_H_INCLUDED

#include <string>
#include "../headers/defines.hpp"
#include "../headers/types.hpp"
#include "channel.hpp"
#include "../templates/interfaceObject.hpp"


namespace YSE {
  
  namespace SOUND {
    class managerObject;
    class implementationObject;
  }

  namespace CHANNEL{


    /**
      Channels are used to control groups of sounds simultaniously. (Quite comparable to
      channel groups on a mixing console.) Every sound has to be linked to a channel at
      creation time. Channel can also be linked to another channel, thus creating a tree-like
      structure with subchannels. During DSP callback, all channels will render their
      audio in a separate thread. For this reason it might be a good idea to distribute
      your sounds over several channels.

      For convenience, several typical channels are already created by the system. There's the
      MainMix, which is the root of the channel tree. Other channels (all linked to MainMix) are:

      - FX     : Intended for short audio effects
      - Music  : Intended for playlists and other music
      - Ambient: Intended for environmental sounds
      - Voice  : Intended for dialogs
      - Gui    : Intended for interface sounds

      Of course you can use these channels for anything you like.
      */

    class API interfaceObject : public TEMPLATE::interfaceObject<channelSubSystem> {
    public:

      /**
          Creates the channel object. You do have to call this before using a custom channel.
          Premade channels (FX and such) call this function internally.

          @param name     The name of the channel. This can be used in logfiles.
          @param parent   The parent channel. All channels must be linked to an existing channel.
          */
      interfaceObject&  create(const char * name, channel& parent);

      /**
          Changes the volume of a channel. Range is 0-1.
          */
      interfaceObject&  setVolume(Flt value);

      /**
          Get the volume of a channel.
          */
      Flt getVolume();

      /**
          Move the channel to another branch in the channel tree. This detaches the channel from its
          current parent and links it to another channel. All sounds and subchannels move along.

          @param parent The new parent channel to link this channel to.
          */
      interfaceObject& moveTo(interfaceObject& parent);

      /**
          Because reverb needs a lot of processing power, there's only one actual reverb object. By default this is attached to the mainMix,
          thereby affecting all channels. If you want to use the reverb on only a subset of channels, call this function on
          the intended channel. The reverb will be moved to this channel.
          */
      interfaceObject& attachReverb();

      /** Allow or disallow sounds within this channel to be virtual. If you don't know
          what that means, read up on virtualisation in the manual. This function merely
          turns virtualisation off or on for sounds in this channel.
          */
      interfaceObject& setVirtual(Bool value);

      /** Check if this channel allows sounds to go virtual.
      */
      bool getVirtual();

      const char * getName() { return name.c_str(); }

      /**
          The real initialisation of a channel is not done in the constructor.
          */
      interfaceObject();

    private:

      /**
          A special version of create. It is used internally to create the global channel. This is not meant to be used anywhere else.
          */
      void createGlobal();

      Flt volume; // to remember the channel volume
      Bool allowVirtual; // allows virtual sounds in this channel (defaults to true)
      std::string name;

      // friend classes
      friend class CHANNEL::implementationObject;
      friend class SOUND::implementationObject;
      friend class system;
      friend class SOUND::managerObject;
    };
  }
  
  /**
   Use these functors to get access to the premade channels.
  */
  channel& ChannelMaster ();
  channel& ChannelFX     ();
  channel& ChannelMusic  ();
  channel& ChannelAmbient();
  channel& ChannelVoice  ();
  channel& ChannelGui    ();
}




#endif  // CHANNEL_H_INCLUDED