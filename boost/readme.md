

 [boost webpage](http://www.boost.org/)


### 1. get code
        1) download the latest release  http://www.boost.org/users/history
        cd <path-boost-you-want-to-put>
        mkdir third_party
        cd third_pary
        tar --bzip2 -xvf boost_1_57_0.tar.bz2
### 2) use git  https://github.com/boostorg/boost.git


        This is a sketch of the resulting directory structure:

> boost_1_57_0/ .................The “boost root directory”
> > index.htm .........A copy of www.boost.org starts here
> > boost/ .........................All Boost Header files
>
> > libs/ ............Tests, .cpps, docs, etc., by library
> > > index.html ........Library documentation starts here
> > > algorithm/
> > > any/
> > > array/
> > > …more libraries…
> > status/ .........................Boost-wide test suite
> > tools/ ...........Utilities, e.g. Boost.Build, quickbook, bcp
> > more/ ..........................Policy documents, etc.
> > doc/ ...............A subset of all Boost library docs

### 2. build
   Most of codes in boost 