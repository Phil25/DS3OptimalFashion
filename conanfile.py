from conans import ConanFile, CMake, tools

class DS3OptimalFashion(ConanFile):
    generators = "cmake"
    settings = "os", "compiler", "build_type", "arch"
    requires = (
        "cmake_installer/3.14.5@conan/stable",
        "wxwidgets/3.1.4@bincrafters/stable",
    )

    def build(self):
        cmake = CMake(self)

        ver = tools.get_env("APP_VERSION", "undetermined version")
        if not ver:
            ver = "undetermined version"

        cmake.definitions["APP_VERSION"] = str(ver)

        cmake.configure()
        cmake.build()