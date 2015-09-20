package com.honeycomb.sdk.test;

import android.app.Activity;

import com.honeycomb.sdk.Honeycomb;

/**
 * This class need to help test native code and if fact this is just a simple wrapper over
 * {@link com.honeycomb.sdk.Honeycomb}
 *
 * Created by camobap on 7/12/15.
 */
public class HoneycombNDKWrapper {

    /**
     * See {@link com.honeycomb.sdk.Honeycomb#version()}
     */
    public static native String version();

    /**
     * See {@link com.honeycomb.sdk.Honeycomb#prepare(Activity, String)}
     */
    public static native void prepare(final Activity activity, final String companyId, final String appId);

    /**
     * See {@link com.honeycomb.sdk.Honeycomb#setEnabled(boolean)}}
     */
    public static native void setEnabled(boolean enabled);

    /**
     * See {@link com.honeycomb.sdk.Honeycomb#isEnabled()}
     */
    public static native boolean isEnabled();

    /**
     * See {@link com.honeycomb.sdk.Honeycomb#showAd()}
     */
    public static native void showAd();
}
