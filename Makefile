
CMAKE ?= /usr/bin/cmake
CTEST ?= /usr/bin/ctest
PYTHON_EXE ?= python3.8
VENV_DIR ?= venv
BUILD_DIR ?= build
BUILD_TOOL ?= Ninja
BUILD_TYPE ?= RelWithDebInfo
CXX_STARDARD ?= 20
JOBS ?= 8
EXERCISE ?= 1

.PHONY: install all exec-test test exec-benchmark benchmark init check-format format clang-tidy lint

$(BUILD_DIR)/rules.ninja:
	@mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && \
	conan install .. &&\
	$(CMAKE) \
   	-DCMAKE_CXX_STANDARD=$(CXX_STANDARD) \
	-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
    -G$(BUILD_TOOL) \
	-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
	-DAOC_EXERCISE=$(EXERCISE) \
	-Wdev \
	-Wall \
	..

init: $(BUILD_DIR)/rules.ninja
	ln -sf $(BUILD_DIR)/compile_commands.json .

clean:
	@rm -Rf $(BUILD_DIR)

all:
	$(CMAKE) --build $(BUILD_DIR) --target all -- -j$(JOBS)

check-format:
	$(CMAKE) --build $(BUILD_DIR) --target check-format

format:
	$(CMAKE) --build $(BUILD_DIR) --target format

clang-tidy:
	$(CMAKE) --build $(BUILD_DIR) --target clang-tidy

lint: clang-tidy
