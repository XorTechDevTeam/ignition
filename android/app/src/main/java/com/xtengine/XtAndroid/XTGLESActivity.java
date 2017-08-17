package com.xtengine.XtAndroid;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;

import java.io.File;


public class XTGLESActivity extends Activity {

    XTGLES2View mView;

    @Override protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        mView = new XTGLES2View(getApplication());
        setContentView(mView);
    }

    @Override protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        mView.onResume();
    }
}
