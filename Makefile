# Here you can define name of your project (engine name by default)
XT_PROJECT=XorTech

all:
	@echo "Usage: make (LINUX|ANDROID|WINDOWS|OSX|IOS)"

clean:
	@echo "Clean common build"
	rm -rf build
	mkdir build
	@echo "Clean android"
	cd android && ./gradlew clean

LINUX:
	cmake . -B./build/Linux -DPLATFORM:STRING="LINUX" -DPROJECT_NAME:STRING=${XT_PROJECT}
	cd build/Linux && make

ANDROID:
	cd android && ./gradlew assembleDebug
	adb install -r ./android/app/build/outputs/apk/app-debug.apk

WIN32:
	cmake . -B./build/Win32 -DPLATFORM:STRING="WIN32" -DPROJECT_NAME:STRING=${XT_PROJECT}
	@echo "Use Microsoft Visual Studio to continue"

WINUWP:
	cmake . -B./build/WinUWP -DPLATFORM:STRING="WINUWP" -DPROJECT_NAME:STRING=${XT_PROJECT}
	@echo "Use Microsoft Visual Studio to continue"

WINDOWS:
	@echo "Please, use target WIN32 or WINUWP"
	
OSX: NOT_SUPPORTED
IOS: NOT_SUPPORTED

NOT_SUPPORTED:
	@echo "Not supported yet"
