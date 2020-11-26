
# Configurations:

VERBOSE=n
OPT=g
USE_NANO=y
USE_LTO=n
SEMIHOST=n
USE_FPU=y
ENFORCE_NOGPL=n

# Libraries:
INCLUDES += -I$(PROGRAM_PATH_AND_NAME)/inc
SRC = $(wildcard $(PROGRAM_PATH_AND_NAME)/src/*.c)
