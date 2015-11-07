package com.honeycomb.sdk.test;

import android.app.Activity;
import android.test.ActivityInstrumentationTestCase2;
import android.view.View;

import java.util.concurrent.TimeUnit;

/**
 * Created by camobap on 7/29/15.
 *
 * TODO design & develop approach to test coco2dx specific native code
 */
public class HoneycombNDKTest extends ActivityInstrumentationTestCase2<NativeActivity> {
    public HoneycombNDKTest() {
        super(NativeActivity.class);
    }

    @Override
    protected void setUp() throws Exception {
        super.setUp();
    }

    public void testSuccess() {
    }

    /**
     * Goal of this test is check crash absence,
     * because native interface will not work from java layer.
     * It will works only for cocos2d-x or unity3d
     *
     * @throws Exception
     */
    public void disabledTestActivity() throws Exception {
        Activity activity = getActivity();
        assertNotNull(activity);
    }

    /**
     * Goal of this test is check crash absence,
     * because native interface will not work from java layer.
     * It will works only for cocos2d-x or unity3d
     *
     * @throws Exception
     */
    public void disabledTestShowAd() throws Exception {
        NativeActivity activity = getActivity();
        assertNotNull(activity);

        activity.showAd(null);

        Thread.sleep(TimeUnit.SECONDS.toMillis(10));

        activity.findViewById(R.id.interstitial_banner);
    }
}
