/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.honeycomb.cocos2dx;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxHelper;
import org.cocos2dx.lib.Cocos2dxRenderer;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.AlertDialog;
import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.content.res.Configuration;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.Toast;

import com.easyndk.classes.AndroidNDKHelper;
import com.example.android.trivialdrivesample.util.IabHelper;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;

public class Soccer extends Cocos2dxActivity{
	public boolean isBillingSupported = true;
	IAPSetup iapSetup;
	IabHelper mIABHelper;
	static boolean isGooglePlay = true;
	AdView adView;
	
	AdControl adControl;
	protected static boolean showChartBoostAd = true, showRevMobAd = false;
	protected static long prevAdTime = System.currentTimeMillis();
	public static Soccer activity;

	boolean isRevMobAdReceived = false,shouldDisplayAd = false;

	public static final String REMOVE_ADDS_SKU = "com.honeycomb.cocos2dx.Removeads";
//	public static final String REMOVE_ADDS_SKU = "android.test.purchased";
    private static final String REMOVE_ADDS = "remove_ads";
	static SharedPreferences gamePrefrence;
	boolean isLargeDevice;

	private InterstitialAd interstitial;

	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);

		setContentView(com.honeycomb.cocos2dx.R.layout.main);
		interstitial = new InterstitialAd(this);
	    interstitial.setAdUnitId("ca-app-pub-2442035138707094/8795197567");
	    activity = Soccer.this;
		AndroidNDKHelper.SetNDKReciever(this);
		
		Cocos2dxGLSurfaceView mGLView = (Cocos2dxGLSurfaceView) findViewById(com.honeycomb.cocos2dx.R.id.game_gl_surfaceview);

		mGLView.setEGLContextClientVersion(2);
		mGLView.setCocos2dxRenderer(new Cocos2dxRenderer());
		
		new Handler().postDelayed(new Runnable() {
			@Override
			public void run() {
				Soccer.this.runOnUiThread(new Runnable() {
					@Override
					public void run() {
						findViewById(com.honeycomb.cocos2dx.R.id.logolayout).setVisibility(View.GONE);
					}
				});
			}
		}, 3000);
		
		iapSetup = new IAPSetup();
		mIABHelper = iapSetup.mIABHelper;
		
		if ((getResources().getConfiguration().screenLayout &  Configuration.SCREENLAYOUT_SIZE_MASK) == Configuration.SCREENLAYOUT_SIZE_XLARGE) {     
			isLargeDevice = true;
		}else if ((getResources().getConfiguration().screenLayout &  Configuration.SCREENLAYOUT_SIZE_MASK) == Configuration.SCREENLAYOUT_SIZE_LARGE) {
			isLargeDevice = true;
		}else if ((getResources().getConfiguration().screenLayout & Configuration.SCREENLAYOUT_SIZE_MASK) == Configuration.SCREENLAYOUT_SIZE_NORMAL) {
			isLargeDevice = false;
		}else if ((getResources().getConfiguration().screenLayout &  Configuration.SCREENLAYOUT_SIZE_MASK) == Configuration.SCREENLAYOUT_SIZE_SMALL) {
			isLargeDevice = false;
		}
		gamePrefrence = getSharedPreferences("null", MODE_PRIVATE);
	}
	
	static {
		//if(!isGooglePlay){
			System.loadLibrary("game");
//		}
			
	}
	public void startPuchaseFlow(JSONObject prms){
		if(!isAdsFreeVersion()){
			mIABHelper.launchPurchaseFlow(this, REMOVE_ADDS_SKU, 110, iapSetup);	
		}else {
			this.runOnUiThread(new Runnable() {
				public void run() {
					Toast.makeText(Soccer.this, "Already purchased", Toast.LENGTH_SHORT).show();
				}
			});
		}
	};
	
	public boolean isConnectingToInternet(){
		ConnectivityManager connectivity = (ConnectivityManager) this.getSystemService(Context.CONNECTIVITY_SERVICE);
		if (connectivity != null) 
		{
			NetworkInfo[] info = connectivity.getAllNetworkInfo();
			if (info != null) 
				for (int i = 0; i < info.length; i++) 
					if (info[i].getState() == NetworkInfo.State.CONNECTED)
					{
						return true;
					}

		}   
		return false;
	}
	
	 @Override
	 public void onActivityResult(int requestCode, int resultCode, Intent data) {
		 if (!mIABHelper.handleActivityResult(requestCode, resultCode, data)) {
	            // not handled, so handle it ourselves (here's where you'd
	            // perform any handling of activity results not related to in-app
	            // billing...
	            super.onActivityResult(requestCode, resultCode, data);
	        }
	       
	 }
	
	 public void adFunctionalty(JSONObject prms) {
		 
		 // show ad disabled
	 	/*

		 String showbottom = null;
		 String showtop = null;
		 try{
			 showbottom = prms.getString("bottomAd");
			 showtop = prms.getString("topAd");			
		 }
		 catch (JSONException e){
			 e.printStackTrace();
		 }

		 removeAd();
		
		 if(showbottom.equalsIgnoreCase("YES")) {
				 showBottomAd();
		 }
		 if(showtop.equalsIgnoreCase("YES")) {
				 showTopAd();
		 }
		
		 boolean showMenuSceneAds = false;
		 boolean showGameOverSceneAds = false;		

		 try{
			 showMenuSceneAds = prms.getString("menu").equalsIgnoreCase("YES");	
			 showGameOverSceneAds = prms.getString("gameOver").equalsIgnoreCase("YES");
		 }
		 catch (JSONException e){
			 e.printStackTrace();
		 }	
		 
		 showAdmobInterestial(showMenuSceneAds);	
		 showAdmobInterestial(showGameOverSceneAds);
		*/

	 }
	 
	 @Override
	    protected void onStart() {
	        super.onStart();
	    }
	   
	    
	    @Override
	    protected void onStop() {
	        super.onStop();
	    }
	    
	    @Override
	    protected void onResume() {
	        super.onResume();
	        Cocos2dxHelper.onResume();
	               
	    }
	    
	    @Override
	    protected void onPause() {
	        super.onPause();
	        Cocos2dxHelper.onPause();
	    }
		
	    @Override
		public void onBackPressed() {
		    // If an interstitial is on screen, close it. Otherwise continue as normal.
		    
		}
	 
	 public static Object cppCall_logsth(){
			return activity;
		}

	 public void showTopAd() {
				LinearLayout layout = (LinearLayout) findViewById(com.honeycomb.cocos2dx.R.id.top);
				attachAd(layout);
			
		}

		public void showBottomAd() {
				LinearLayout layout = (LinearLayout) findViewById(com.honeycomb.cocos2dx.R.id.bottom);
				attachAd(layout);
			
		}
		
		
		public void removeAd() {
			this.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					
					LinearLayout layoutAdmobBottom = (LinearLayout) findViewById(com.honeycomb.cocos2dx.R.id.bottom);
					layoutAdmobBottom.removeAllViews();
					LinearLayout layoutAdmobTop = (LinearLayout) findViewById(com.honeycomb.cocos2dx.R.id.top);
					layoutAdmobTop.removeAllViews();
				}
			});
		}
		

		private void attachAd(final LinearLayout layout) {
			this.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					if(isGooglePlay){
						if (adView == null) {
							if(isLargeDevice) {
								adView = new AdView(Soccer.this);	
								adView.setAdSize(AdSize.LEADERBOARD);
							}else {
								adView = new AdView(Soccer.this);
								adView.setAdSize(AdSize.BANNER);
							}
							adView.setAdUnitId("ca-app-pub-2442035138707094/7318464369");
							AdRequest adRequest = new AdRequest.Builder()
							.addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
							.addTestDevice("F38303E87BE23CE2B501B4CECED6DF0F")
							.addTestDevice("86B9EA564072174EEC460A3D2A343265").build();

							// Start loading the ad in the background.
							adView.loadAd(adRequest);
							// samsung galaxy tab
							// adRequest.addTestDevice("8B4248C5362C18F658803042A2F868C4");
							adView.loadAd(adRequest);
							layout.addView(adView);
						} 
						else {
							layout.addView(adView);
						}					
					}
					else{

					}
				}
			});
		}

	 public synchronized void onWindowFocusChanged(final boolean pHasWindowFocus) {
			super.onWindowFocusChanged(pHasWindowFocus);
			if (!pHasWindowFocus) {
				return;
			}
			Handler h = new Handler();
			Runnable r = new Runnable() {
				@Override
				public void run() {
					AndroidNDKHelper.SendMessageWithParameters("resumeBackgroundMusic", getDict());
				}
			};
			h.post(r);
		}
		
		

	 private void initallizeAdmobInterstitial() {
		 AdRequest adRequest = new AdRequest.Builder()
			.addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
			.addTestDevice("86B9EA564072174EEC460A3D2A343265")
			.addTestDevice("F38303E87BE23CE2B501B4CECED6DF0F").build();
		 interstitial.loadAd(adRequest);
	}

	
	
	public void showAdmobInterestial(boolean prms){
		if(prms ) {
			initallizeAdmobInterstitial();
			if(interstitial.isLoaded()) {
				prevAdTime = System.currentTimeMillis();
				interstitial.show();
				
			}		
		}
	}

	public void showStartAppInterestial(boolean prms){

	}
		
		public JSONObject getDict() {
			String jsonStr = "{\"fake_dictionary\":\"have_fun\"}";
			JSONObject prmsToSend = null;
			try{
				prmsToSend = new JSONObject(jsonStr);
			}
			catch (JSONException e){
				e.printStackTrace();
			} 
			return prmsToSend;
		}
		

		public void shouldDisplayChartboostAd(boolean prms) {
			//showChartBoostAd = false;
//			if(prms ) {
//				Chartboost.showInterstitial(CBLocation.LOCATION_DEFAULT);
//				Chartboost.cacheInterstitial(CBLocation.LOCATION_DEFAULT);
//			}
		}
		
		public void shouldDisplayRevMobAd(boolean prms) {
			
		}
		
		public void quitGame(JSONObject prms) {
			AlertDialog.Builder exitbuilder = new AlertDialog.Builder(this);
			exitbuilder.setTitle("Girl Superhero")
			.setMessage(com.honeycomb.cocos2dx.R.string.QUIT_MESSAGE)
			.setCancelable(false)
			.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int id) {
					AndroidNDKHelper.SendMessageWithParameters("resetListener", getDict());
				}
			})
			.setNegativeButton("No", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int id) {
					dialog.cancel();
				}
			});
			AlertDialog stopalert = exitbuilder.create();
			stopalert.show();
		}
		
		public void askForRate(JSONObject prms) {
			AlertDialog.Builder exitbuilder = new AlertDialog.Builder(this);
			exitbuilder.setTitle("Rate 2 Planes")
			.setMessage(com.honeycomb.cocos2dx.R.string.Rate)
			.setCancelable(false)
			.setPositiveButton("Rate It Now", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int id) {
					rateButtonClicked(getDict());
				}
			})
			.setNegativeButton("No,Thanks", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int id) {
					dialog.cancel();
					AndroidNDKHelper.SendMessageWithParameters("rated", getDict());
				}
			});
			AlertDialog stopalert = exitbuilder.create();
			stopalert.show();
		}
		
		public void rateButtonClicked(JSONObject prms){
			Uri uri;
			if(isGooglePlay){
				uri = Uri.parse("market://details?id=" + getPackageName());
				
			}else{
				uri = Uri.parse("amzn://apps/android?p=" + getPackageName());
			}
			Intent myAppLinkToMarket = new Intent(Intent.ACTION_VIEW, uri);
			try {
				startActivity(myAppLinkToMarket);
				AndroidNDKHelper.SendMessageWithParameters("rated", getDict());
			} catch (ActivityNotFoundException e) {
				Toast.makeText(this, " unable to find market app", Toast.LENGTH_LONG).show();
			}
		}
		
		public void showMoreApps(JSONObject prms){
//			chartBoost.showMoreApps();
		}
		public void setAdsFreeVersion(boolean isEnabled) {
			Editor editor = gamePrefrence.edit();
			editor.putBoolean(REMOVE_ADDS, isEnabled);
			editor.commit();
			removeAd();
			AndroidNDKHelper.SendMessageWithParameters("purchasedSuccessful", getDict());
		}
		
		public boolean isAdsFreeVersion(){
			return gamePrefrence.getBoolean(REMOVE_ADDS, false);
		}
	
}
