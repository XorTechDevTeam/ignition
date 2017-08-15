package com.xtengine.XtAndroid;

public class XtEngine {

	static {
		System.loadLibrary("XtAndroid");
	}

	public static native void xtInit(int width, int height);
	public static native void xtUpdate();
	public static native void xtOnPause();
	public static native void xtOnResume();
	public static native void xtOnDestroy();
}
