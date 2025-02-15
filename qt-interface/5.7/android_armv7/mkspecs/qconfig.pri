#configuration
CONFIG +=  cross_compile shared qpa release qt_no_framework
host_build {
    QT_ARCH = x86_64
    QT_TARGET_ARCH = arm
} else {
    QT_ARCH = arm
}
QT_CONFIG +=  minimal-config small-config medium-config large-config full-config no-pkg-config evdev c++11 accessibility egl eglfs opengl opengles2 shared qpa reduce_exports clock-gettime clock-monotonic mremap getaddrinfo ipv6ifname inotify eventfd poll_poll png doubleconversion freetype harfbuzz system-zlib openssl rpath concurrent audio-backend release

#versioning
QT_VERSION = 5.7.0
QT_MAJOR_VERSION = 5
QT_MINOR_VERSION = 7
QT_PATCH_VERSION = 0

#namespaces
QT_LIBINFIX = 
QT_NAMESPACE = 

QT_EDITION = OpenSource
QT_LICHECK = licheck64
QT_RELEASE_DATE = 2016-06-13

QT_COMPILER_STDCXX = 201103
QT_GCC_MAJOR_VERSION = 4
QT_GCC_MINOR_VERSION = 9
QT_GCC_PATCH_VERSION = 0
