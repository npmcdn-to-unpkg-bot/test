

 [boost webpage http://www.boost.org/](http://www.boost.org/)


### 1. get code
        1) download the latest release  http://www.boost.org/users/history
            cd <path-boost-you-want-to-put>
            mkdir third_party
            cd third_pary
            tar --bzip2 -xvf boost_1_57_0.tar.bz2
### 2) use git  https://github.com/boostorg/boost.git


        This is a sketch of the resulting directory structure:

        boost_1_57_0/ .................The “boost root directory”
                index.htm .........A copy of www.boost.org starts here
                boost/ .........................All Boost Header files
                libs/ ............Tests, .cpps, docs, etc., by library
                        index.html ........Library documentation starts here
                        algorithm/
                        any/
                        array/
                        …more libraries…
                status/ .........................Boost-wide test suite
                tools/ ...........Utilities, e.g. Boost.Build, quickbook, bcp
                more/ ..........................Policy documents, etc.
                doc/ ...............A subset of all Boost library docs

### 2. build
        Most Boost libraries are header-only: they consist entirely of header files containing templates and inline functions, and require no separately-compiled library binaries or special treatment when linking

        The only Boost libraries that must be built separately are:

        Boost.Chrono
        Boost.Context
        Boost.Filesystem
        Boost.GraphParallel
        Boost.IOStreams
        Boost.Locale
        Boost.MPI
        Boost.ProgramOptions
        Boost.Python (see the Boost.Python build documentation before building and installing it)
        Boost.Regex
        Boost.Serialization
        Boost.Signals
        Boost.System
        Boost.Thread
        Boost.Timer
        Boost.Wave
        A few libraries have optional separately-compiled binaries:

        Boost.DateTime has a binary component that is only needed if you're using its to_string/from_string or serialization features, or if you're targeting Visual C++ 6.x or Borland.
        Boost.Graph also has a binary component that is only needed if you intend to parse GraphViz files.
        Boost.Math has binary components for the TR1 and C99 cmath functions.
        Boost.Random has a binary component which is only needed if you're using random_device.
        Boost.Test can be used in “header-only” or “separately compiled” mode, although separate compilation is recommended for serious use.
        Boost.Exception provides non-intrusive implementation of exception_ptr for 32-bit _MSC_VER==1310 and _MSC_VER==1400 which requires a separately-compiled binary. This is enabled by #define BOOST_ENABLE_NON_INTRUSIVE_EXCEPTION_PTR.

### 3. Build and install boost
        $ cd boost_1_57_0
        $ ./bootstrap.sh --help
        $    ./bootstrap.sh \
            --with-libraries=chrono,date_time,filesystem,log,program_options,random,system,test,thread \
            --prefix=<path-to-install>
        $ ./b2 install
        headers and binaries are both copied.

### 4. Or, Build Custom Binaries
        http://www.boost.org/doc/libs/1_57_0/more/getting_started/unix-variants.html
        or
        

