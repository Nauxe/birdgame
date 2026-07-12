from conan import ConanFile


class BirdgameConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"
    
    def requirements(self):
        self.requires("sdl/3.4.8")
        self.requires("sdl_image/3.4.4")
        self.requires("sdl_ttf/3.2.2")

    def layout(self):
        self.folders.build = "build"
        self.folders.generators = "build/generators"
