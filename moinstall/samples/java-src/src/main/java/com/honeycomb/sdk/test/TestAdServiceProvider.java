package com.honeycomb.sdk.test;

import com.honeycomb.sdk.internal.model.AdRequest;
import com.honeycomb.sdk.internal.model.AdResponse;
import com.honeycomb.sdk.internal.network.AdNetworkServiceProvider;

import java.util.Collections;
import java.util.List;

/**
 * Created by camobap on 9/9/15.
 */
public class TestAdServiceProvider implements AdNetworkServiceProvider {
    @Override
    public AdResponse requestAd(AdRequest adRequest) {
        return new AdResponse(AdResponse.Status.SUCCESS,
                "http://www.moinstall.com/wp-content/themes/moinstall/img/logo.png",
                "http://www.moinstall.com", Collections.<String>emptyList());
    }

    @Override
    public void processBeacons(AdResponse response) {

    }
}
