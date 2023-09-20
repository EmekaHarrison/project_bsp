CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -DDEVENV
LDFLAGS = --coverage

LIB_DIR = lib
TEST_DIR = test
BUILD_DIR = build

$(shell mkdir -p $(BUILD_DIR)/test_led_driver)
$(shell mkdir -p $(BUILD_DIR)/test_integration)
$(shell mkdir -p $(BUILD_DIR)/test_terminal)

all:
 @echo "============================ Targets ============================"
 @echo "=> clean to clean the project"
 @echo "=> test_led_driver to build and run the led driver"
 @echo "=> test_integration to build and run the integration test"
 @echo "=> test_terminal to build and run the terminal test"
 @echo "================================================================="

$(BUILD_DIR)/unity.o: test/unity/unity.cpp test/unity/unity.h test/unity/unity_internals.h
 @$(CXX) -c $(CXXFLAGS) $< -I./test/unity -o $@

test_led_driver: $(BUILD_DIR)/test_led_driver/led_driver.o $(BUILD_DIR)/test_led_driver/bsp_digital.o $(BUILD_DIR)/test_led_driver/test.o $(BUILD_DIR)/unity.o
 @$(CXX) $(LDFLAGS) $^ -o $(BUILD_DIR)/$@/test; ./$(BUILD_DIR)/$@/test

$(BUILD_DIR)/test_led_driver/led_driver.o: lib/led_driver/led_driver.cpp lib/led_driver/led_driver.h test/test_led_driver/bsp_digital.h
 @$(CXX) -c $(CXXFLAGS) $(LDFLAGS) $< -I./lib/led_driver -I./test/test_led_driver -o $@

$(BUILD_DIR)/test_led_driver/bsp_digital.o: test/test_led_driver/bsp_digital.cpp test/test_led_driver/bsp_digital.h
 @$(CXX) -c $(CXXFLAGS) $< -I./test/test_led_driver -o $@

$(BUILD_DIR)/test_led_driver/test.o: test/test_led_driver/test.cpp lib/led_driver/led_driver.h test/test_led_driver/bsp_digital.h test/unity/unity.h test/unity/unity_internals.h
 @$(CXX) -c $(CXXFLAGS) $< -I./test/test_led_driver -I./test/unity -I./lib/led_driver -o $@

test_terminal: $(BUILD_DIR)/test_terminal/terminal.o $(BUILD_DIR)/test_terminal/led_driver.o $(BUILD_DIR)/test_terminal/bsp_serial.o $(BUILD_DIR)/test_terminal/test.o $(BUILD_DIR)/unity.o
 @$(CXX) $(LDFLAGS) $^ -o $(BUILD_DIR)/$@/test; ./$(BUILD_DIR)/$@/test

$(BUILD_DIR)/test_terminal/terminal.o: lib/terminal/terminal.cpp lib/terminal/terminal.h test/test_terminal/bsp_serial.h test/test_terminal/led_driver.h
 @$(CXX) -c $(CXXFLAGS) $(LDFLAGS) $< -I./lib/terminal -I./test/test_terminal -o $@

$(BUILD_DIR)/test_terminal/led_driver.o: test/test_terminal/led_driver.cpp test/test_terminal/led_driver.h
 @$(CXX) -c $(CXXFLAGS) $< -I./test/test_terminal -o $@

$(BUILD_DIR)/test_terminal/bsp_serial.o: test/test_terminal/bsp_serial.cpp test/test_terminal/bsp_serial.h
 @$(CXX) -c $(CXXFLAGS) $< -I./test/test_terminal -o $@

$(BUILD_DIR)/test_terminal/test.o: test/test_terminal/test.cpp test/test_terminal/bsp_serial.h test/test_terminal/led_driver.h lib/terminal/terminal.h test/unity/unity.h test/unity/unity_internals.h
 @$(CXX) -c $(CXXFLAGS) $< -I./test/test_terminal -I./test/unity -I./lib/terminal -o $@

test_integration: $(BUILD_DIR)/test_integration/terminal.o $(BUILD_DIR)/test_integration/led_driver.o $(BUILD_DIR)/test_integration/bsp_serial.o $(BUILD_DIR)/test_integration/bsp_digital.o $(BUILD_DIR)/test_integration/test.o $(BUILD_DIR)/unity.o
 @$(CXX) $(LDFLAGS) $^ -o $(BUILD_DIR)/$@/test; ./$(BUILD_DIR)/$@/test

$(BUILD_DIR)/test_integration/terminal.o: lib/terminal/terminal.cpp lib/terminal/terminal.h test/test_integration/bsp_serial.h lib/led_driver/led_driver.h
 @$(CXX) -c $(CXXFLAGS) $(LDFLAGS) $< -I./lib/terminal -I./lib/led_driver -I./test/test_integration -o $@

$(BUILD_DIR)/test_integration/led_driver.o: lib/led_driver/led_driver.cpp lib/led_driver/led_driver.h test/test_integration/bsp_digital.h
 @$(CXX) -c $(CXXFLAGS) $(LDFLAGS) $< -I./lib/led_driver -I./test/test_integration -o $@

$(BUILD_DIR)/test_integration/bsp_serial.o: test/test_integration/bsp_serial.cpp test/test_integration/bsp_serial.h
 @$(CXX) -c $(CXXFLAGS) $< -I./test/test_integration -o $@

$(BUILD_DIR)/test_integration/bsp_digital.o: test/test_integration/bsp_digital.cpp test/test_integration/bsp_digital.h
 @$(CXX) -c $(CXXFLAGS) $< -I./test/test_integration -o $@

$(BUILD_DIR)/test_integration/test.o: test/test_integration/test.cpp test/test_integration/bsp_serial.h test/test_integration/bsp_digital.h lib/terminal/terminal.h lib/led_driver/led_driver.h test/unity/unity.h test/unity/unity_internals.h
 @$(CXX) -c $(CXXFLAGS) $< -I./test/test_integration -I./test/unity -I./lib/terminal -I./lib/led_driver -o $@

.PHONY: all clean

clean:
 @rm -rf $(BUILD_DIR)
