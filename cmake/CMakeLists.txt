set(SOURCES
    main.cpp
)

set(PUBLIC_HEADERS

)

set(PRIVATE_HEADERS

)

set(CMAKE_BUILD_TYPE
    "Debug"
)

add_library(test STATIC ${SOURCES} ${PUBLIC_HEADERS} ${PRIVATE_HEADERS})

    set(WEBRTC_FLAGS
        -DV8_DEPRECATION_WARNINGS
        -DEXPAT_RELATIVE_PATH
        -DFEATURE_ENABLE_VOICEMAIL
        -DGTEST_RELATIVE_PATH
        -DJSONCPP_RELATIVE_PATH
        -DLOGGING=1
        -DSRTP_RELATIVE_PATH
        -DFEATURE_ENABLE_SSL
        -DFEATURE_ENABLE_PSTN
        -DHAVE_SCTP
        -DHAVE_SRTP
        -DHAVE_WEBRTC_VIDEO
        -DHAVE_WEBRTC_VOICE
        -D_FILE_OFFSET_BITS=64
        -DCHROMIUM_BUILD
        -DCR_CLANG_REVISION=233105-1
        -DTOOLKIT_VIEWS=1
        -DUI_COMPOSITOR_IMAGE_TRANSPORT
        -DUSE_AURA=1
        -DUSE_ASH=1
        -DUSE_PANGO=1
        -DUSE_CAIRO=1
        -DUSE_DEFAULT_RENDER_THEME=1
        -DUSE_LIBJPEG_TURBO=1
        -DUSE_X11=1
        -DUSE_CLIPBOARD_AURAX11=1
        -DENABLE_ONE_CLICK_SIGNIN
        -DENABLE_PRE_SYNC_BACKUP
        -DENABLE_REMOTING=1
        -DENABLE_WEBRTC=1
        -DENABLE_PEPPER_CDMS
        -DENABLE_CONFIGURATION_POLICY
        -DENABLE_NOTIFICATIONS
        -DENABLE_HIDPI=1
        -DUSE_UDEV
        -DDONT_EMBED_BUILD_METADATA
        -DENABLE_TASK_MANAGER=1
        -DENABLE_EXTENSIONS=1
        -DENABLE_PLUGINS=1
        -DENABLE_SESSION_SERVICE=1
        -DENABLE_THEMES=1
        -DENABLE_AUTOFILL_DIALOG=1
        -DENABLE_SAVE_WALLET_CARDS_LOCALLY=1
        -DENABLE_BACKGROUND=1
        -DENABLE_GOOGLE_NOW=1
        -DCLD_VERSION=2
        -DENABLE_PRINTING=1
        -DENABLE_BASIC_PRINTING=1
        -DENABLE_PRINT_PREVIEW=1
        -DENABLE_SPELLCHECK=1
        -DENABLE_CAPTIVE_PORTAL_DETECTION=1
        -DENABLE_APP_LIST=1
        -DENABLE_SETTINGS_APP=1
        -DENABLE_SUPERVISED_USERS=1
        -DENABLE_MDNS=1
        -DENABLE_SERVICE_DISCOVERY=1
        -DV8_USE_EXTERNAL_STARTUP_DATA
        -DLIBPEERCONNECTION_LIB=1
        -DLINUX
        -DWEBRTC_LINUX
        -DHASH_NAMESPACE=__gnu_cxx
        -DPOSIX
        -DWEBRTC_POSIX
        -DDISABLE_DYNAMIC_CAST
        -D_REENTRANT
        -DUSE_LIBPCI=1
        -DUSE_OPENSSL=1
        -DUSE_OPENSSL_CERTS=1
        -DUSE_GLIB=1
        -DHAVE_GTK # TODO remove this after renderer is ok.
        )

        message("dafei macros:""${WEBRTC_FLAGS}")

    set(CMAKE_CXX_FLAGS "
        -fstack-protector
        --param=ssp-buffer-size=4
        -pthread
        -fno-strict-aliasing
        -Wno-unused-parameter
        -Wno-missing-field-initializers
        -fvisibility=hidden
        -pipe
        -fPIC
        #-Wno-unused-local-typedefs
        -pthread
        -Wno-format
        -Wno-unused-result
        -m64
        -march=x86-64
        -funwind-tables
        #-fno-exceptions
        #-fno-rtti
        -fno-threadsafe-statics
        -fvisibility-inlines-hidden
        -Wno-deprecated
        -std=gnu++11
        -Wno-narrowing
        -Wno-literal-suffix
        ${WEBRTC_FLAGS} ${CMAKE_CXX_FLAGS}")

    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-local-typedefs")
    endif()

    set(CMAKE_SHARED_LINKER_FLAGS "
        -Wl,-z,now 
        -Wl,-z,relro
        -Wl,--fatal-warnings
        -Wl,-z,defs
        -pthread
        -Wl,-z,noexecstack
        -fPIC
        -m64
        ${CMAKE_SHARED_LINKER_FLAGS}")

    # Diffrences between Debug and Release
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}
            -DDYNAMIC_ANNOTATIONS_ENABLED=1
            -DWTF_USE_DYNAMIC_ANNOTATIONS=1
            -D_DEBUG
            #-O0
            -g
            -gdwarf-4
            ")
    elseif (CMAKE_BUILD_TYPE MATCHES "Release")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}
            -DNDEBUG
            -DNVALGRIND
            -DDYNAMIC_ANNOTATIONS_ENABLED=0
            #-O2
            -fno-ident
            -fdata-sections
            -ffunction-sections
            ")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}
            -Wl,-O1
            -Wl,--as-needed
            -Wl,--gc-sections
            ")
    else()
        message(FATAL_ERROR "No CMAKE_BUILD_TYPE ? Some macros and build options will be missed")
    endif()



