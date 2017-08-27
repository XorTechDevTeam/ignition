/**
 *  This is part of XorTech Android Application
 *
 *  Copyright (C) XorTech Dev Team 2017
 *  License: see LICENSE.md for details
 */
package $PACKAGE$;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;

import java.io.File;


public class $APPLICATION$ extends Activity {

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

    @Override protected void onDestroy() {
        super.onDestroy();
        XtEngine.xtOnDestroy();
    }
}
