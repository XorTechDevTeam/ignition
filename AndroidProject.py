'''
    Usage:
        python AndroidProject --name <ProjectName> --package <Your package> --minSdk <android-23>

    Common Params:
    --name              - project name
    --package           - android package
    --minSdk            - min version of android sdk
    --trgSdk            - target version of android sdk
    --clean             - remove all files and recreate project
    --rebuild           - rebuild whole project
    --install           - start gradlew and install project after generation
    --disarch           - remove arch from build list
    --exclude           - exclude source file from search

    Variables:
    $APPLICATION$   - App name
    $PACKAGE$       - Current package
    $MINSDK$        - Min SDK
    $TRGSDK$        - Target sdk
    $ARCHLIST$      - List of supported NDK ABI FILTERS
    $CDECLPACKAGE$  - C Func declaration for NDK
    $DATETIME$      - Current Date & Time in format DD.MM.YYYY | HH.MM.SS
    $GITCOMMIT$     - current git commit
    $GITBRANCH$     - current git branch
'''
import os
import re
import sys
import string
import shutil
import fnmatch
import argparse
import datetime
import subprocess

__SCRIPT_VERSION__ = '0.0.1'
__JAVA_SOURCE__    = '*.java'

projectInfo = {
    'appname':  'XorTech',                          #Application name (without spaces)
    'applabel': 'XorTech',                          #Public name
    'package':  'com.android.xtengine',             #OurPackage
    'minSdk':   '23',                               #Min SDK
    'trgSdk':   '23',                               #Target SDK
    'appicons': ['ic_launcher.png'],                #Our icons (app icon, notification icons and etc.)
    'archlist': ["'x86'", 
                 "'x86_64'", 
                 "'armeabi'", 
                 "'armeabi-v7a'", 
                 "'arm64-v8a'"],                    #Supported abiFilters
    'rebuild':  False,                              #if true - remove all sources and generate new
    'mode':     'DEBUG',                            #Build mode (DEBUG|RELEASE)
    'install':  False,                              #Should install after generation (make & install)
    'javasrc': ['src/Core/Platform/Android/java']   #Java Sources
}

commonReplaceList = {}

def findJavaSources(jPathList):
    global __JAVA_SOURCE__
    sources = []
    for jPath in jPathList:
        for root, dirs, files in os.walk(jPath):
            for filename in fnmatch.filter(files, __JAVA_SOURCE__):
                sources.append(os.path.join(root, filename))
    return sources

# --- GEN TASK ---
def task_createDirectories():
    global projectInfo

    if os.path.exists('build/Android') and projectInfo['rebuild']:
        shutil.rmtree('build/Android', True)

    dirs = [
        'build',
        'build/Android',
        # App
        'build/Android/app',
        'build/Android/app/src',
        'build/Android/app/src/main',
        'build/Android/app/src/main/java',
        # Package
        # ------- 
        # Strings
        'build/Android/app/src/main/res',
        'build/Android/app/src/main/res/values',
        # Icons
        'build/Android/app/src/main/res/mipmap-hdpi',
        'build/Android/app/src/main/res/mipmap-mdpi',
        'build/Android/app/src/main/res/mipmap-xhdpi',
        'build/Android/app/src/main/res/mipmap-xxhdpi',
        # Build outputs
        'build/Android/build',
        # Gradle
        'build/Android/gradle',
        'build/Android/gradle/wrapper'
    ]

    pack = projectInfo['package'].split('.')
    if len(pack) == 1:
        print("> ERROR: Invalid package {0}".format(projectInfo['package']))
        return False
    else:
        prev = "build/Android/app/src/main/java/{0}"
        for itv in pack:
            way = prev.format(itv)
            prev = way + "/{0}"
            dirs.append(way)

    for dir in dirs:
        if not os.path.exists(dir):
            os.makedirs(dir)
            print("> Create directory {0}".format(dir))

    return True

def copyIcons():
    global projectInfo
    iconNames       = projectInfo['appicons']
    commonPath      = 'res/icons/android'
    iconsPathList   = ['mipmap-hdpi', 'mipmap-mdpi', 'mipmap-xhdpi', 'mipmap-xxhdpi']

    for icon in iconNames:
        for iconType in iconsPathList:
            fromFile = '{0}/{1}/{2}'.format(commonPath, iconType, icon)
            toFile = 'build/Android/app/src/main/res/{0}/{1}'.format(iconType, icon)
            shutil.copyfile(fromFile, toFile)
            print("> Copy {0} to {1}".format(fromFile, toFile))

def generateManifest():
    print("> Copy AndroidManifest.xml")
    shutil.copyfile('src/Core/Platform/Android/gradle/app/AndroidManifest.xml', 'build/Android/app/src/main/AndroidManifest.xml')
    print("> Prepare AndroidManifest.xml")
    prepareFile('build/Android/app/src/main/AndroidManifest.xml')

def generateStrings():
    global projectInfo
    path = 'build/Android/app/src/main/res/values/strings.xml'
    source = '<?xml version="1.0" encoding="utf-8"?><resources><string name="xt_app_name">{0}</string></resources>'.format(projectInfo['applabel'])

    with open(path, 'w') as fPtr:
        fPtr.write(source)
        fPtr.close()

def prepareLine(line):
    global commonReplaceList
    newLine = line

    for key in commonReplaceList:
        if key in newLine:
            replaceValue = ""
            if isinstance(commonReplaceList[key], list):
                replaceValue = ','.join(commonReplaceList[key])
            else:
                replaceValue = commonReplaceList[key]
            newLine = newLine.replace(key, replaceValue)
    
    return newLine

def prepareFile(path):
    with open(path, 'r+w') as fPtr:
        source = fPtr.readlines()
        newFileSource = []
        for line in source:
            newLine = prepareLine(line)
            if newLine != line:
                newFileSource.append(newLine)
            else:
                newFileSource.append(line)
        fPtr.seek(0)
        fPtr.truncate()
        fPtr.writelines(newFileSource)
        fPtr.close()
    
def generateGradle():
    # --- TOP CONFIGS ---
    gradleSourcesBase = 'src/Core/Platform/Android/gradle'
    gradleSources = ['build.gradle', 'gradlew', 'gradlew.bat', 'settings.gradle']
    print("> Copy top level sources (common for all projects)")
    for src in gradleSources:
        fromFile = "{0}/{1}".format(gradleSourcesBase, src)
        toFile = 'build/Android/{0}'.format(src)
        shutil.copyfile(fromFile, toFile)
        print("> Copy {0} to {1}".format(fromFile, toFile))
    # --- MAKE GRADLEW EXECUTABLE ---
    #TODO: This code will work only under linux/unix OS
    from sys import platform as _platform
    if _platform == "darwin" or _platform.startswith("linux"):
        print("> Fix executable (1 of 1)")
        import stat
        newMask = 0o111
        targetFile = 'build/Android/gradlew'
        st = os.stat(targetFile)
        print("> Fix file {0}".format(targetFile))
        os.chmod(targetFile, st.st_mode | newMask) #make executable
    # --- GRADLE WRAPPER ---
    print("> Copy gradle wrapper files")
    print("> 0/2")
    shutil.copyfile('{0}/{1}/{2}'.format(gradleSourcesBase, 'gradle/wrapper/', 'gradle-wrapper.jar'),        'build/Android/gradle/wrapper/gradle-wrapper.jar')
    print("> 1/2 | gradle-wrapper.jar")
    shutil.copyfile('{0}/{1}/{2}'.format(gradleSourcesBase, 'gradle/wrapper/', 'gradle-wrapper.properties'), 'build/Android/gradle/wrapper/gradle-wrapper.properties')
    print("> 2/2 | gradle-wrapper.properties")
    # --- GRADLE CONFIGURABLE SOURCES ---
    print("> Copy project build.gradle")
    shutil.copyfile('{0}/{1}/{2}'.format(gradleSourcesBase, 'app/', 'build.gradle'), 'build/Android/app/build.gradle')
    print("> Configure project build.gradle ...")
    prepareFile('build/Android/app/build.gradle')
    print("> DONE")

def task_copyFiles():
    global projectInfo
    global commonReplaceList

    sources = findJavaSources(projectInfo['javasrc'])
    
    packageDir = "build/Android/app/src/main/java/" + projectInfo["package"].replace('.', '/') + "/"

    for source in sources:
        replaced = False
        for key in commonReplaceList:
            fromPath = ""
            toPath = ""
            fromPath = source
            if key in source:
                toPath = string.replace(source, key, commonReplaceList[key])
                toPath = toPath[toPath.rindex('/') + 1 : ]
                toPath = packageDir + toPath
                replaced = True
                break
        if not replaced:
            toPath = source
            toPath = toPath[toPath.rindex('/') + 1 : ]
            toPath = packageDir + toPath
        shutil.copyfile(fromPath, toPath)
        print("> Generate source {0}".format(toPath))
        # --- PREPARE THE FILE ---
        prepareFile(toPath)
    # --- STRINGS.XML ---
    print("> Generate localization")
    generateStrings()
    # --- ICONS ---
    print("Task: generate app icons")
    copyIcons()
    # --- APP MANIFEST ---
    print("Task: Generate AndroidManifest.xml")
    generateManifest()
    # --- GRADLE SOURCES ---
    print("Task: generate gradle files")
    generateGradle()
    # --- OK ---
    return True

def task_prepareNativeCode():
    print("Task: prepare native code")
    print("> Generate native declaration")
    shutil.copyfile('src/Core/Platform/Android/XtAndroidProject.h.in', 'src/Core/Platform/Android/XtAndroidProject.h')
    prepareFile('src/Core/Platform/Android/XtAndroidProject.h')
    print('> Native file src/Core/Platform/Android/XtAndroidProject.h ready!')
    return True
# --- ENTRY ---

def gradlew_start():
    global projectInfo

    target = ""
    currentMode = projectInfo['mode'].upper()

    if currentMode == 'RELEASE':
        target        = 'assembleRelease'
        installTarget = 'app-release.apk'
    elif currentMode == 'DEBUG':
        target        = 'assembleDebug'
        installTarget = 'app-debug.apk'
    else:
        print('> ERROR: Invalid build mode (supported DEBUG|RELEASE)')
        return False

    print('> Detail: change working directory to build/Android')
    os.chdir('./build/Android')

    pakIntent = '{0}.{1}'.format(projectInfo['package'], projectInfo['appname'])
    buildCommands = [ './gradlew {0}'.format(target), 'adb install -r app/build/outputs/apk/{0}'.format(installTarget), 'adb shell am start -n {0}/{1}'.format(projectInfo['package'], pakIntent) ]
    failed = False
    failedAt = ''
    callStack = ''

    for buildCommand in buildCommands:
        print('Task: '.format(buildCommand))
        callStack  = buildCommand.split(' ')
        returnCode = subprocess.call(callStack)
        if returnCode != 0:
            print('> Last task FAILED. See error ^ for details ^')
            failed = True
            failedAt = buildCommand
            callStack = ' '.join(callStack)
            break
        print('> Last target done. Return code: {0}'.format(returnCode))

    if failed:
        print('Task failed. Error at {0} (last command {1})'.format(failedAt, callStack))
        return

def generateProject():
    global projectInfo
    print("Task: generate project {0}".format(projectInfo['appname']))

    taskList = [task_createDirectories, task_copyFiles, task_prepareNativeCode]
    for task in taskList:
        if not task() is True:
            print("Error: last task failed. Generator was stopped ...")
            return
    print("\n\nResult: done")
    if projectInfo['install'] is True:
        print("Task: compile via gradle")
        gradlew_start()

def cleanup():
    print("Task: clean")

def git_load():
    global commonReplaceList
 
    if subprocess.check_output('git status'.split(' ')).startswith('fatal'):
        print('> Info: git not available')
        return

    commonReplaceList['$GITCOMMIT$'] = subprocess.check_output('git rev-parse HEAD'.split(' ')).replace('\n', '')
    commonReplaceList['$GITBRANCH$'] = subprocess.check_output('git rev-parse --abbrev-ref HEAD'.split(' ')).replace('\n', '')

def getBuildTime():
    nowTime = datetime.datetime.now()
    return nowTime.strftime("%d/%m/%Y - %H/%M/%S")

def main():
    global projectInfo
    parser = argparse.ArgumentParser(description='Android Project Generator')
    parser.add_argument('--name',    type=str, action='store', help='Project name')
    parser.add_argument('--package', type=str, action='store', help='Android package name')
    parser.add_argument('--minSdk',  type=str, action='store', help='Define min. android sdk')
    parser.add_argument('--trgSdk',  type=str, action='store', help='Target android sdk')
    parser.add_argument('--label',   type=str, action='store', help='Application label')
    parser.add_argument('--mode',    type=str, action='store', help='Set build mode (DEBUG|RELEASE)')
    parser.add_argument('--rebuild', action='store_true', help='Remove old project directory and generate project')
    parser.add_argument('--install', action='store_true', help='Start gradlew and install project after generation')
    parser.add_argument('--clean',   action='store_true', help='Clean the project')
    parser.add_argument('--disarch', nargs='+', help='Disable arch passed in list')
    
    args = parser.parse_args()

    for k, v in vars(args).iteritems():
        if k == 'clean' and v:
            cleanup()
            break
        if k == 'disarch':
            if not v is None:
                for arch in v:
                    rmarch = "'{0}'".format(arch)
                    print('> Disable arch {0}'.format(rmarch))
                    projectInfo['archlist'].remove(rmarch)
                
                totalArchCount = len(projectInfo['archlist'])
                print('> To compile: {0}'.format(totalArchCount))
                if totalArchCount == 0:
                    print("ERROR: Invalid generator configuration! We haven't any one platform to generate project")
                    return
            else:
                continue
        else:
            if not v is None:
                if k == 'name':
                    projectInfo['appname'] = v
                elif k == 'label':
                    projectInfo['applabel'] = v
                else:
                    projectInfo[k] = v

    # Update global vars
    global commonReplaceList
    commonReplaceList = {
        '$APPLICATION$' :   projectInfo['appname'],
        '$PACKAGE$':        projectInfo['package'],
        '$MINSDK$':         projectInfo['minSdk'],
        '$TRGSDK$':         projectInfo['trgSdk'],
        '$ARCHLIST$':       projectInfo['archlist'],
        '$CDECLPACKAGE$':   ('Java_{0}'.format('_'.join(projectInfo['package'].split('.')))),
        '$DATETIME$':       getBuildTime()
    }

    git_load()
    print("> Build stamp: {0}".format(commonReplaceList['$DATETIME$']))

    # Create project
    generateProject()

def welcome():
    global __SCRIPT_VERSION__
    PROJ_ASCII = """
    __   __          ______       _ _     _ 
    \ \ / /          | ___ \     (_) |   | |
     \ V /  ___  _ __| |_/ /_   _ _| | __| |
     /   \ / _ \| '__| ___ \ | | | | |/ _` |
    / /^\ \ (_) | |  | |_/ / |_| | | | (_| |
    \/   \/\___/|_|  \____/ \__,_|_|_|\__,_|
    V{0}
    """.format(__SCRIPT_VERSION__)
    print(PROJ_ASCII)

if __name__ == "__main__":
    welcome()
    main()
else:
    print("This is not a module!")