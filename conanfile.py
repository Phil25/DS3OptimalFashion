from conans import ConanFile, CMake, tools

class SourceModAddonManager(ConanFile):
    generators = "cmake"
    settings = "os", "compiler", "build_type", "arch"
    requires = (
        "cmake_installer/3.14.5@conan/stable",
    )

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()