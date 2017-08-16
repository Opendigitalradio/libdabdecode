# pylint: disable=missing-docstring
from os import (
    chdir,
    getenv,
    sep
)
from conans import ConanFile, CMake


class DABDecodeTestConan(ConanFile):
    name = 'libdabdecode package test'
    version = '1.0.1'
    description = 'The Conan.io package test for libdabdecode'
    settings = (
        'arch',
        'build_type',
        'compiler',
        'os',
    )
    requires = 'libdabdecode/{version}@{user}/{channel}'.format(**{
        'channel': getenv('CONAN_USERNAME', 'Opendigitalradio'),
        'user': getenv('CONAN_CHANNEL', 'stable'),
        'version': version,
    })
    generators = 'cmake'

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_dir=self.conanfile_directory)
        cmake.build()

    def test(self):
        chdir('bin')
        self.run('.{separator}package_test'.format(**{
            'separator': sep
        }))
