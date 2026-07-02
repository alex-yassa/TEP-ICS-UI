.PHONY: all clean cm4 cm7 ensure_makefiles

all: cm4 cm7

ensure_makefiles:
	python3 ensure_makefiles.py

cm4: ensure_makefiles
	python3 port_eez_ui.py
	$(MAKE) -C STM32CubeIDE/CM4/Release all

cm7: ensure_makefiles
	$(MAKE) -C STM32CubeIDE/CM7/Release all

clean:
	-$(MAKE) -C STM32CubeIDE/CM4/Release clean
	-$(MAKE) -C STM32CubeIDE/CM7/Release clean

