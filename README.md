Fabric for Autodesk 3ds Max
===================================
Fabric for 3ds Max is the integration of Fabric Canvas in 3ds Max.

The plugin allows you to use Fabric inside your 3ds Max projects for procedural geometry creation, deformation and controlling the transformation of objects (e.g. for rigging).

Repository Status
=================

This repository will be maintained and kept up to date by Fabric Software to match the latest Fabric Engine version

Supported platforms
===================

Windows
3ds Max 2015,2016 and 2017

Building and Dependencies
========================

A Visual Studio project is provided, which expects some environment variables to be set:

QTWINMIGRATE_DIR pointing to a build of the qtwinmigrate project https://github.com/qtproject/qt-solutions/tree/master/qtwinmigrate
MaxSDKPath pointing to the Max SDK
QT_DIR pointing to a valid QT 4.8.7 installation
FABRIC_DIR pointing to a supported version of Fabric Engine

Some of this variables might have to be redeclared to follow your path conventions.

License
==========

The license used for this DCC integration can be found in the root folder of this repository.
