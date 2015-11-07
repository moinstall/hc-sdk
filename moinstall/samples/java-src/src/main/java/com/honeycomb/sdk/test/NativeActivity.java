package com.honeycomb.sdk.test;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import com.honeycomb.sdk.Honeycomb;

/**
 * Created by camobap on 7/29/15.
 */
public class NativeActivity extends AppCompatActivity {

    static {
        System.loadLibrary("honeycombtest");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        HoneycombNDKWrapper.prepare(this, BuildConfig.HC_COMP_ID, BuildConfig.HC_APP_ID);
        Honeycomb.setListener(new HCListener(this));
    }

    public void showAd(View view) {
        HoneycombNDKWrapper.showAd();
    }
}