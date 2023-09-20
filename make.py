"""
To run the test, use the following command in the terminal of same directory:

#run: python3 make.py
#it will then request that you enter the name of the target; type the name of the target
# then repeat the process again for the other targets.

for example:

python3 make.py
enter target name: test_led_driver

python3 make.py
enter target name: test_integration

python3 make.py
enter target name: test_terminal

python3 make.py
enter target name: clean

"""

import os

CXX = "g++"
CXXFLAGS = "-Wall -Wextra -Wpedantic -DDEVENV"
LDFLAGS = "--coverage"

LIB_DIR = "lib"
TEST_DIR = "test"
BUILD_DIR = "build"


def create_directory(directory):
    os.makedirs(directory, exist_ok=True)


def compile_object_file(source_file, object_file, includes=[]):
    includes_str = " ".join([f"-I{include}" for include in includes])
    command = f"{CXX} -c {CXXFLAGS} {LDFLAGS} {includes_str} {source_file} -o {object_file}"
    os.system(command)


def build_target(target, object_files):
    object_files_str = " ".join(object_files)
    command = f"{CXX} {LDFLAGS} {object_files_str} -o {BUILD_DIR}/{target}/test; ./{BUILD_DIR}/{target}/test"
    os.system(command)


def build_led_driver_test():
    create_directory(f"{BUILD_DIR}/test_led_driver")
    compile_object_file(f"{LIB_DIR}/led_driver/led_driver.cpp", f"{BUILD_DIR}/test_led_driver/led_driver.o",
                        includes=[f"./{LIB_DIR}/led_driver", f"./{TEST_DIR}/test_led_driver"])
    compile_object_file(f"{TEST_DIR}/test_led_driver/bsp_digital.cpp",
                        f"{BUILD_DIR}/test_led_driver/bsp_digital.o", includes=[f"./{TEST_DIR}/test_led_driver"])
    compile_object_file(f"{TEST_DIR}/test_led_driver/test.cpp", f"{BUILD_DIR}/test_led_driver/test.o",
                        includes=[f"./{TEST_DIR}/test_led_driver", f"./{TEST_DIR}/unity", f"./{LIB_DIR}/led_driver"])
    compile_object_file(f"{TEST_DIR}/unity/unity.cpp",
                        f"{BUILD_DIR}/unity.o", includes=["./test/unity"])
    build_target("test_led_driver", [f"{BUILD_DIR}/test_led_driver/led_driver.o",
                 f"{BUILD_DIR}/test_led_driver/bsp_digital.o", f"{BUILD_DIR}/test_led_driver/test.o", f"{BUILD_DIR}/unity.o"])


def build_terminal_test():
    create_directory(f"{BUILD_DIR}/test_terminal")
    compile_object_file(f"{LIB_DIR}/terminal/terminal.cpp", f"{BUILD_DIR}/test_terminal/terminal.o",
                        includes=[f"./{LIB_DIR}/terminal", f"./{TEST_DIR}/test_terminal"])
    compile_object_file(f"{TEST_DIR}/test_terminal/led_driver.cpp",
                        f"{BUILD_DIR}/test_terminal/led_driver.o", includes=[f"./{TEST_DIR}/test_terminal"])
    compile_object_file(f"{TEST_DIR}/test_terminal/bsp_serial.cpp",
                        f"{BUILD_DIR}/test_terminal/bsp_serial.o", includes=[f"./{TEST_DIR}/test_terminal"])
    compile_object_file(f"{TEST_DIR}/test_terminal/test.cpp", f"{BUILD_DIR}/test_terminal/test.o",
                        includes=[f"./{TEST_DIR}/test_terminal", f"./{TEST_DIR}/unity", f"./{LIB_DIR}/terminal"])
    compile_object_file(f"{TEST_DIR}/unity/unity.cpp",
                        f"{BUILD_DIR}/unity.o", includes=["./test/unity"])
    build_target("test_terminal", [f"{BUILD_DIR}/test_terminal/terminal.o", f"{BUILD_DIR}/test_terminal/led_driver.o",
                 f"{BUILD_DIR}/test_terminal/bsp_serial.o", f"{BUILD_DIR}/test_terminal/test.o", f"{BUILD_DIR}/unity.o"])


def build_integration_test():
    create_directory(f"{BUILD_DIR}/test_integration")
    compile_object_file(f"{LIB_DIR}/terminal/terminal.cpp", f"{BUILD_DIR}/test_integration/terminal.o",
                        includes=[f"./{LIB_DIR}/terminal", f"./{LIB_DIR}/led_driver", f"./{TEST_DIR}/test_integration"])
    compile_object_file(f"{LIB_DIR}/led_driver/led_driver.cpp", f"{BUILD_DIR}/test_integration/led_driver.o",
                        includes=[f"./{LIB_DIR}/led_driver", f"./{TEST_DIR}/test_integration"])
    compile_object_file(f"{TEST_DIR}/test_integration/bsp_serial.cpp",
                        f"{BUILD_DIR}/test_integration/bsp_serial.o", includes=[f"./{TEST_DIR}/test_integration"])
    compile_object_file(f"{TEST_DIR}/test_integration/bsp_digital.cpp",
                        f"{BUILD_DIR}/test_integration/bsp_digital.o", includes=[f"./{TEST_DIR}/test_integration"])
    compile_object_file(f"{TEST_DIR}/test_integration/test.cpp", f"{BUILD_DIR}/test_integration/test.o", includes=[
                        f"./{TEST_DIR}/test_integration", f"./{TEST_DIR}/unity", f"./{LIB_DIR}/terminal", f"./{LIB_DIR}/led_driver"])
    compile_object_file(f"{TEST_DIR}/unity/unity.cpp",
                        f"{BUILD_DIR}/unity.o", includes=["./test/unity"])
    build_target("test_integration", [f"{BUILD_DIR}/test_integration/terminal.o", f"{BUILD_DIR}/test_integration/led_driver.o",
                 f"{BUILD_DIR}/test_integration/bsp_serial.o", f"{BUILD_DIR}/test_integration/bsp_digital.o", f"{BUILD_DIR}/test_integration/test.o", f"{BUILD_DIR}/unity.o"])


def clean():
    os.system(f"rm -rf {BUILD_DIR}")


def main():
    print("============================ Targets ============================")
    print("=> clean to clean the project")
    print("=> test_led_driver to build and run the led driver")
    print("=> test_integration to build and run the integration test")
    print("=> test_terminal to build and run the terminal test")
    print("=================================================================")

    target = input("Enter the target: ")

    if target == "clean":
        clean()
    elif target == "test_led_driver":
        build_led_driver_test()
    elif target == "test_integration":
        build_integration_test()
    elif target == "test_terminal":
        build_terminal_test()
    else:
        print("Invalid target")


if __name__ == "__main__":
    main()
