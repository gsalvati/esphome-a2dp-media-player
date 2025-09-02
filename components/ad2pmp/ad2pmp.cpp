#include "a2dp_media_player.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ad2pmp {

static const char *TAG = "a2dp_media_player";

void A2DPMediaPlayer::setup() {
  ESP_LOGD(TAG, "Inicializando A2DP Media Player...");
  auto cfg = i2s_stream.defaultConfig();
  cfg.i2s_format = I2S_STD_FORMAT;
  cfg.sample_rate = 44100;
  cfg.bits_per_sample = 16;
  cfg.channels = 2;
  i2s_stream.begin(cfg);

  a2dp_source.set_data_callback_in_frames([this](Frame *data, int32_t len) -> int32_t {
    return this->get_audio_data(data, len);
  });

  std::vector<const char*> bt_names = {global_variables::get_global<std::string>("bt_device_name").c_str()};
  a2dp_source.start(bt_names);
}

void A2DPMediaPlayer::loop() {
  if (this->state == media_player::MEDIA_PLAYER_STATE_PLAYING) {
    // Lógica para streaming contínuo, se necessário
  }
}

void A2DPMediaPlayer::connect_to_speaker() {
  ESP_LOGD(TAG, "Conectando ao speaker Bluetooth: %s", global_variables::get_global<std::string>("bt_device_name").c_str());
  a2dp_source.connect_to(global_variables::get_global<std::string>("bt_device_name").c_str());
}

int32_t A2DPMediaPlayer::get_audio_data(Frame *data, int32_t len) {
  static float phase = 0.0;
  for (int i = 0; i < len; i++) {
    int16_t sample = (int16_t)(sin(phase) * 32767.0);
    data[i].channel1 = sample;
    data[i].channel2 = sample;
    phase += 2.0 * M_PI * 440.0 / 44100.0;
    if (phase >= 2.0 * M_PI) phase -= 2.0 * M_PI;
  }
  ESP_LOGD(TAG, "Fornecendo %d frames de áudio", len);
  return len;
}

media_player::MediaPlayerTraits A2DPMediaPlayer::get_traits() {
  auto traits = media_player::MediaPlayerTraits();
  traits.set_supports_pause(true);
  return traits;
}

void A2DPMediaPlayer::control(const media_player::MediaPlayerCall &call) {
  if (call.get_command().has_value()) {
    switch (call.get_command().value()) {
      case media_player::MEDIA_PLAYER_COMMAND_PLAY:
        ESP_LOGD(TAG, "Comando: Play");
        this->state = media_player::MEDIA_PLAYER_STATE_PLAYING;
        a2dp_source.play();
        break;
      case media_player::MEDIA_PLAYER_COMMAND_PAUSE:
        ESP_LOGD(TAG, "Comando: Pause");
        this->state = media_player::MEDIA_PLAYER_STATE_PAUSED;
        a2dp_source.pause();
        break;
      default:
        break;
    }
  }
}

}  // namespace ad2pmp
}  // namespace esphome