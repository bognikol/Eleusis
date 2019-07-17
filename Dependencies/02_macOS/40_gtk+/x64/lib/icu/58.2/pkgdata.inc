GENCCODE_ASSEMBLY_TYPE=-a gcc-darwin
SO=dylib
SOBJ=dylib
A=a
LIBPREFIX=lib
LIB_EXT_ORDER=.58.2.dylib
COMPILE=/Applications/Xcode.app/Contents/Developer/usr/bin/gcc -DU_ATTRIBUTE_DEPRECATED= -I/Users/bogdannikolic/gtk/inst/include -arch x86_64 -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/usr/include -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk   -DU_HAVE_ATOMIC=1 -DU_HAVE_STRTOD_L=1  -arch x86_64 -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/usr/include -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk -mmacosx-version-min=10.12 -DU_CHARSET_IS_UTF8=1 -DU_USING_ICU_NAMESPACE=0 -fno-common -c
LIBFLAGS=-I/Users/bogdannikolic/gtk/inst/include  -dynamic
GENLIB=/Applications/Xcode.app/Contents/Developer/usr/bin/gcc -dynamiclib -dynamic -arch x86_64 -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/usr/include -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk -mmacosx-version-min=10.12 -DU_CHARSET_IS_UTF8=1 -DU_USING_ICU_NAMESPACE=0 -L/Users/bogdannikolic/gtk/inst/lib -L/Users/bogdannikolic/gtk/inst/lib -arch x86_64 -L/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/usr/lib -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk -mmacosx-version-min=10.12 -Wl,-headerpad_max_install_names -Wl,-rpath,/Users/bogdannikolic/gtk/inst/lib 
LDICUDTFLAGS=
LD_SONAME=-Wl,-compatibility_version -Wl,58 -Wl,-current_version -Wl,58.2 -install_name /Users/bogdannikolic/gtk/inst/lib/
RPATH_FLAGS=
BIR_LDFLAGS=
AR=ar
ARFLAGS=r -c
RANLIB=ranlib
INSTALL_CMD=/usr/bin/install -c
