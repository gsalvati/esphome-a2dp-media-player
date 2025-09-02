import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import media_player
from esphome.const import CONF_ID

# Note que estamos usando o namespace definido no __init__.py
from . import ad2pmp_ns 

A2DPMediaPlayer = ad2pmp_ns.class_("A2DPMediaPlayer", media_player.MediaPlayer, cg.Component)

CONFIG_SCHEMA = cv.All(
    media_player.MEDIA_PLAYER_SCHEMA.extend({
        cv.GenerateID(): cv.declare_id(A2DPMediaPlayer),
    }).extend(cv.COMPONENT_SCHEMA),

    cv.require_library(
        name="ESP32-A2DP",
        owner="pschatzmann",
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