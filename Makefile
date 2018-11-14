# Author: Dominik Harmim <xharmi00@stud.fit.vutbr.cz>

EXECUTABLE := feedreader
BUILD_DIR := cmake-build-release
PACK := xharmi00


.PHONY: $(EXECUTABLE)
$(EXECUTABLE):
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Release ..
	cmake --build $(BUILD_DIR)
	cp $(BUILD_DIR)/$(EXECUTABLE) .


.PHONY: clean
clean:
	rm -rf $(EXECUTABLE) $(BUILD_DIR) $(PACK).tar


.PHONY: pack
pack: $(PACK).tar

$(PACK).tar:
	tar -cf $@ CMakeLists.txt Makefile README src/*
