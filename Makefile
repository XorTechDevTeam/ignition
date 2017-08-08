# Here you can define name of your project (engine name by default)
XT_PROJECT=XorTech

all:
	@echo "Usage:\n\tmake (LINUX|ANDROID|WINDOWS|OSX|IOS)"

LINUX:
	cmake . -B./build -DPLATFORM:STRING="LINUX" -DPROJECT_NAME:STRING=${XT_PROJECT}
	cd build && make

ANDROID: NOT_SUPPORTED
WINDOWS: NOT_SUPPORTED
OSX: NOT_SUPPORTED
IOS: NOT_SUPPORTED

NOT_SUPPORTED:
	@echo "Not supported yet"