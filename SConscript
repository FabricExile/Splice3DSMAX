#
# Copyright (c) 2010-2017 Fabric Software Inc. All rights reserved.
#

import os, platform

Import('parentEnv')

buildOS = platform.system()
buildArch = 'x86_64'
buildType = 'Release'

scenegraph_dir = os.environ['FABRIC_SCENE_GRAPH_DIR']
prebuilt_dir = os.path.join(scenegraph_dir, 'ThirdParty', 'PreBuilt', buildOS, buildArch, 'VS2013', 'Release')

env = parentEnv.Clone()

stageDir = env.Dir(scenegraph_dir).Dir('stage').Dir(buildOS).Dir(buildArch).Dir(buildType)

maxVersions = ['2015', '2016', '2017']

if os.environ.has_key('FABRIC_SPLICE_MAX_VERSION'):
  maxVersions = [os.environ['FABRIC_SPLICE_MAX_VERSION']]


env['ENV'] = os.environ
  
qt_dir = os.path.join(prebuilt_dir, 'qt', '4.8.7')
env['ENV']['QT_DIR'] = qt_dir

qtwinmigrate_dir = os.path.join(prebuilt_dir, 'qt-solutions', 'qtwinmigrate')
env['ENV']['QTWINMIGRATE_DIR'] = qtwinmigrate_dir

# reset the Max SDK so it gets the one in our repo, just in case :)
env['ENV']['MaxSDKPath'] = ''
env['ENV']['FABRIC_DIR'] = os.environ['FABRIC_DIR']
env['ENV']['FABRIC_SCENE_GRAPH_DIR'] = scenegraph_dir


maxFiles = []
srcnodeDir = env.Dir('.').srcnode().abspath
maxBuild = None
for maxVersion in maxVersions:
    prevBuild = maxBuild
    maxBuild = env.Command(
        'build max '+maxVersion,
        [],
        [
            ['cmd.exe', '/c', os.path.join(srcnodeDir, 'build.bat'), '16', maxVersion, 'x64', os.path.join(srcnodeDir, 'Fabric3dsmax.sln')],
        ]
    )
    Depends(maxBuild,prevBuild)
    maxFiles.append(maxBuild)

alias = env.Alias('splicemax', maxFiles)
spliceData = (alias, maxFiles)
Return('spliceData')
