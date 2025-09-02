import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import media_player
from esphome.const import CONF_ID

DEPENDENCIES = ['esp32_ble_tracker']

ad2pmp_ns = cg.esphome_ns.namespace('ad2pmp')
A2DPMediaPlayer = ad2pmp_ns.class_('A2DPMediaPlayer', media_player.MediaPlayer, cg.Component)

CONFIG_SCHEMA = cv.All(  # Usamos cv.All para encadear as validações
    media_player.MEDIA_PLAYER_SCHEMA.extend({
        cv.GenerateID(): cv.declare_id(A2DPMediaPlayer),
    }).extend(cv.COMPONENT_SCHEMA),

    # ADICIONE ESTAS LINHAS:
    # Elas informam ao ESPHome para baixar as bibliotecas necessárias do registro do PlatformIO
    cv.require_library(
        name="ESP32-A2DP",
        owner="pschatzmann",
        version="1.8.3"  # Opcional, mas recomendado para travar uma versão estável
    ),
    cv.require_library(
        name="arduino-audio-tools",
        owner="pschatzmann"
    )
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await media_player.register_media_player(var, config)