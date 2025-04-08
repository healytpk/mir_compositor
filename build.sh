rm -f comp
g++ -o comp *.cpp `pkg-config --cflags miral` `pkg-config --libs miral` \
                  `pkg-config --cflags gtk+-x11-3.0 ` `pkg-config --libs gtk+-x11-3.0` \
                  -std=c++23

#-ggdb3 -fsanitize=address,leak,undefined,pointer-compare,pointer-subtract,float-divide-by-zero,float-cast-overflow -fsanitize-address-use-after-scope -fcf-protection=full -fstack-protector-all -fstack-clash-protection -fvtv-debug -fvtv-counts -finstrument-functions -D_GLIBC_DEBUG -D_GLIBC_DEBUG_PEDANTIC -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
