
# main makefile for ObjectHandler under Borland C++

.autodepend
#.silent

# MAKE Options
!ifdef __MT__
    MAKE = $(MAKE) -D__MT__
!endif
!ifdef _RTLDLL
    MAKE = $(MAKE) -D_RTLDLL
!endif
!ifdef _DEBUG
    MAKE = $(MAKE) -D_DEBUG
!endif
!ifdef SAFE
    MAKE = $(MAKE) -DSAFE
!endif

# Primary target:
# ObjectHandler library
objecthandler::
    cd ObjectHandler
    $(MAKE)
    cd ..

# the installation directive requires the OBJECT_HANDLER_DIR environment variable to
# point to the installed version of ObjectHandler
install : inst
inst:: objecthandler
    if exist "$(OBJECT_HANDLER_DIR)\ObjectHandler" rmdir /S /Q "$(OBJECT_HANDLER_DIR)\ObjectHandler"
    xcopy ObjectHandler\*.hpp "$(OBJECT_HANDLER_DIR)\ObjectHandler" /S /I

    if exist "$(OBJECT_HANDLER_DIR)\lib" rmdir /S /Q "$(OBJECT_HANDLER_DIR)\lib"
    xcopy lib\*.lib "$(OBJECT_HANDLER_DIR)\lib" /S /I
    xcopy lib\*.pdb "$(OBJECT_HANDLER_DIR)\lib" /S /I


# Documentation
docs-all:
    cd Docs
    $(MAKE) all
    cd ..

docs-html:
    cd Docs
    $(MAKE) html
    cd ..

docs-html-online:
    cd Docs
    $(MAKE) html-online
    cd ..

docs-pdf:
    cd Docs
    $(MAKE) pdf
    cd ..

docs-ps:
    cd Docs
    $(MAKE) ps
    cd ..


# Clean up
clean::
    cd ObjectHandler
    $(MAKE) clean
    cd ..
