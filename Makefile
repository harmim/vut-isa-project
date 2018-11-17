# Author: Dominik Harmim <xharmi00@stud.fit.vutbr.cz>

EXECUTABLE := feedreader
BUILD_DIR := cmake-build-release
PACK := xharmi00
DOC_DIR = doc
DOC = manual.pdf


.PHONY: $(EXECUTABLE)
$(EXECUTABLE):
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Release ..
	cmake --build $(BUILD_DIR)
	cp $(BUILD_DIR)/$(EXECUTABLE) .


.PHONY: clean
clean:
	rm -rf $(EXECUTABLE) $(BUILD_DIR) $(PACK).tar $(DOC)
	cd $(DOC_DIR) && make clean


.PHONY: pack
pack: $(PACK).tar

$(PACK).tar: doc
	tar -cf $@ CMakeLists.txt Makefile README $(DOC) src/*


.PHONY: test
test:
	@ echo 'TODO'


.PHONY: doc
doc: $(DOC)

.PHONY: $(DOC)
$(DOC):
	cd $(DOC_DIR) && make
	cp $(DOC_DIR)/$(DOC) .
