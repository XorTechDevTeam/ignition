/**
 *  This is part of XorTech Android Application
 *
 *  Copyright (C) XorTech Dev Team 2017
 *  License: see LICENSE.md for details
 */
package $PACKAGE$;

import android.app.Activity;

public class XtEngine {
	static {
		System.loadLibrary("$APPLICATION$");
	}

	public static Activity g_appActivity = null;

	public static native void xtInit(int width, int height);
	public static native void xtUpdate();
	public static native void xtOnPause();
	public static native void xtOnResume();
	public static native void xtOnDestroy();
}
