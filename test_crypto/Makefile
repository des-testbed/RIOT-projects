export PROJECT = test_crypto
include ../Makefile.applications_common

#These boards do not have enough ROM:
export BOARD_BLACKLIST = wsn430-v1_3b msb-430h chronos msb-430 telosb redbee-econotag wsn430-v1_4

# list here all modules that are used in your project
USEMODULE += posix
USEMODULE += uart0
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += auto_init
USEMODULE += crypto_3des
USEMODULE += crypto_aes
USEMODULE += crypto_rc5
USEMODULE += crypto_skipjack
USEMODULE += crypto_twofish
USEMODULE += crypto_sha256

include $(RIOTBASE)/Makefile.include
