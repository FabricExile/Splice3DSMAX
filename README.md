Fabric for Autodesk 3ds Max
===================================
Fabric for 3ds Max is the integration of Fabric Canvas in 3ds Max.

The plugin allows you to use Fabric inside your 3ds Max projects for procedural geometry creation, deformation and controlling the transformation of objects (e.g. for rigging).

Repository Status
=================

This repository will be maintained and kept up to date by Fabric Software to match the latest Fabric Core / Fabric Fabric.

Supported platforms
===================

Windows

Building
========

A scons (http://www.scons.org/) build script is provided. Fabric Fabric for 3DSMAX depends on
* A dynamic build of Fabric Core (matching the latest version).
* The FabricAPI repository checked out one level above (http://github.com/fabric-engine/FabricAPI)

Fabric Fabric for 3ds Max requires a certain folder structure to build properly. You will need to have the FabricAPI cloned as well on your drive, as such:

    FabricAPI
    Applications/Fabric3DSMAX

You can use the bash script below to clone the repositories accordingly:

    git clone git@github.com:fabric-engine/FabricAPI.git
    mkdir Applications
    cd Applications
    git clone git@github.com:fabric-engine/Fabric3DSMAX.git
    cd Fabric3DSMAX
    scons

To inform scons where to find the Fabric Core includes as well as the thirdparty libraries, you need to set the following environment variables:

* FABRIC_BUILD_OS: Should be the type of OS you are building for (Windows, Darwin, Linux)
* FABRIC_BUILD_ARCH: The architecture you are building for (x86, x86_64)
* FABRIC_BUILD_TYPE: The optimization type (Release, Debug)
* FABRIC_SPLICE_VERSION: Refers to the version you want to build. Typically the name of the branch (for example 1.13.0)
* FABRIC_CAPI_DIR: Should point to Fabric Engine's Core folder.
* 3DSMAX_INCLUDE_DIR: The include folder of the Autodesk 3DSMAX installation. (for example: C:\Program Files\Autodesk\3DSMAX2014\include)
* 3DSMAX_LIB_DIR: The library folder of the Autodesk 3DSMAX installation. (for example: C:\Program Files\Autodesk\3DSMAX2014\lib)
* 3DSMAX_VERSION: The 3DSMAX version to use including eventual SP suffix. (for example: 2014SP2)

The temporary files will be built into the *.build* folder, while the structured output files will be placed in the *.stage* folder.

To perform a build you can just run

    scons all -j8

To clean the build you can run

    scons clean

License
==========

The license used for this DCC integration can be found in the root folder of this repository.
