package com.honeycomb.sdk.test;

import android.content.Context;
import android.widget.Toast;

import com.honeycomb.sdk.HoneycombListener;

/**
 * Created by camobap on 8/21/15.
 */
public final class HCListener implements HoneycombListener {

    private Context mContext;

    public HCListener(Context context) {
        mContext = context;
    }

    @Override
    public void onAdDownloading() {
        Toast.makeText(mContext, "Ad downloading...", Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onAdDownloaded() {
        Toast.makeText(mContext, "Ad downloaded", Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onAdShow() {
    }

    @Override
    public void onAdClick() {
        Toast.makeText(mContext, "Ad click", Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onAdClose() {
    }

    @Override
    public void onError(String reason) {
        Toast.makeText(mContext, "Error: " + reason, Toast.LENGTH_SHORT).show();
    }
}
