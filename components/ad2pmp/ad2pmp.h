#pragma once
#include "esphome.h"
#include "BluetoothA2DPSource.h"
#include "AudioTools.h"

namespace esphome {
namespace ad2pmp {

class A2DPMediaPlayer : public Component, public media_player::MediaPlayer {
 public:
  void setup() override;
  void loop() override;
  void connect_to_speaker();
  media_player::MediaPlayerTraits get_traits() override;
  void control(const media_player::MediaPlayerCall &call) override;

 protected:
  BluetoothA2DPSource a2dp_source;
  I2SStream i2s_stream;
  int32_t get_audio_data(Frame *data, int32_t len);
};

}  // namespace ad2pmp
}  // namespace esphome