package com.honeycomb.sdk.test;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;

import com.honeycomb.sdk.Honeycomb;
import com.honeycomb.sdk.HoneycombListener;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Honeycomb.prepare(this, BuildConfig.HC_COMP_ID, BuildConfig.HC_APP_ID);
        Honeycomb.setListener(new HCListener(this));
    }

    public void showAd(View view) {
        Honeycomb.showAd();
    }
}
