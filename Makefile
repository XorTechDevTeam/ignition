# Here you can define name of your project (engine name by default)
XT_PROJECT=XorTech
XT_APP_NAME=Xor Tech Demo
XT_BUILD_MODE=DEBUG

# Android
XT_ANDROID_PACKAGE=com.xt.demo
XT_ANDROID_MINSDK=23
XT_ANDROID_TRGSDK=23
#Targets

all:
	@echo "Usage: make (LINUX|ANDROID|WINDOWS|OSX|IOS)"

clean:
	@echo "Clean common build"
	rm -rf build
	mkdir build
	@echo "Clean android"
	rm -f src/Core/Platform/Android/XtAndroidProject.h
	rm -rf src/3rd/AngelScript/lib && mkdir src/3rd/AngelScript/lib && touch src/3rd/AngelScript/lib/delete.me

LINUX:
	cmake . -B./build/Linux -DPLATFORM:STRING="LINUX" -DPROJECT_NAME:STRING=${XT_PROJECT}
	cd build/Linux && make

ANDROID:
	python AndroidProject.py --name ${XT_PROJECT} 		 \
				 --label "${XT_APP_NAME}"	 \
				 --package ${XT_ANDROID_PACKAGE} \
				 --minSdk ${XT_ANDROID_MINSDK} 	 \
				 --trgSdk ${XT_ANDROID_TRGSDK}	 \
				 --mode ${XT_BUILD_MODE}	 \
				 --disarch x86 x86_64

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
