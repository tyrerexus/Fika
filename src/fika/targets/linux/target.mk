# TODO: Move these out.
include src/fika/targets/common/target.mk
include src/fika/targets/x86_64/target.mk
include src/fika/targets/linux_64/target.mk

OBJECTS += src/fika/targets/linux/io.o \
		   src/fika/targets/linux/fs.o