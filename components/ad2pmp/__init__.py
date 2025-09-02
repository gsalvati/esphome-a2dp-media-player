import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID

# Define o namespace, pode ser útil no futuro
ad2pmp_ns = cg.esphome_ns.namespace("ad2pmp")

# Esquema de configuração mínimo para registrar o componente
CONFIG_SCHEMA = cv.COMPONENT_SCHEMA

async def to_code(config):
    # Esta função pode ficar vazia por enquanto
    pass