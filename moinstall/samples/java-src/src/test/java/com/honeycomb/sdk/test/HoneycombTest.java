package com.honeycomb.sdk.test;

import android.app.Activity;
import android.test.ActivityInstrumentationTestCase2;
import android.test.UiThreadTest;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;

import com.honeycomb.sdk.Honeycomb;

import java.lang.reflect.Field;
import java.util.concurrent.TimeUnit;

/**
 * <a href="http://d.android.com/tools/testing/testing_android.html">Testing Fundamentals</a>
 */
public class HoneycombTest extends ActivityInstrumentationTestCase2<MainActivity> {
    private static final long TIME_TO_SHOW = TimeUnit.SECONDS.toMillis(5);
    private static final long TIME_TO_CLOSE = TimeUnit.SECONDS.toMillis(1);

    public HoneycombTest() {
        super(MainActivity.class);
    }

    @Override
    protected void setUp() throws Exception {
        super.setUp();

        Field field = Honeycomb.class.getDeclaredField("mServer");
        field.setAccessible(true);
        field.set(null, new TestAdServiceProvider());
        field.setAccessible(false);
    }

    public void testSuccess() {
    }

    public void testActivity() throws Exception {
        MainActivity activity = getActivity();
        assertNotNull(activity);
    }

    public void testShowAd() throws Exception {
        MainActivity activity = getActivity();
        assertNotNull(activity);

        activity.showAd(null);

        Thread.sleep(TIME_TO_SHOW);

        View view = Honeycomb.getAdView();
        assertNotNull(view);
    }

    public void testAdClose() throws Exception {
        MainActivity activity = getActivity();
        assertNotNull(activity);

        activity.showAd(null);

        Thread.sleep(TIME_TO_SHOW);

        View view = Honeycomb.getAdView();
        assertNotNull(view);

        final ImageButton button = (ImageButton) view.findViewById(com.honeycomb.sdk.R.id.interstitial_close);
        assertNotNull(view);
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                button.performClick();
            }
        });
        Thread.sleep(TIME_TO_CLOSE);

        assertNull(Honeycomb.getAdView());
    }
}