# Here you can define name of your project (engine name by default)
XT_PROJECT=XorTech

all:
	@echo "Usage:\n\tmake (LINUX|ANDROID|WINDOWS|OSX|IOS)"

clean:
	@echo "Clean common build"
	rm -rf build
	mkdir build
	@echo "Clean android"
	cd android && ./gradlew clean

LINUX:
	cmake . -B./build -DPLATFORM:STRING="LINUX" -DPROJECT_NAME:STRING=${XT_PROJECT}
	cd build && make

ANDROID:
	cd android && ./gradlew assembleDebug
	adb install -r ./android/app/build/outputs/apk/app-debug.apk

WINDOWS: NOT_SUPPORTED
OSX: NOT_SUPPORTED
IOS: NOT_SUPPORTED

NOT_SUPPORTED:
	@echo "Not supported yet"