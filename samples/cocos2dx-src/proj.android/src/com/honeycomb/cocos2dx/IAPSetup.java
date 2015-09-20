package com.honeycomb.cocos2dx;

import com.example.android.trivialdrivesample.util.IabHelper;
import com.example.android.trivialdrivesample.util.IabHelper.OnConsumeFinishedListener;
import com.example.android.trivialdrivesample.util.IabHelper.OnIabPurchaseFinishedListener;
import com.example.android.trivialdrivesample.util.IabHelper.OnIabSetupFinishedListener;
import com.example.android.trivialdrivesample.util.IabHelper.QueryInventoryFinishedListener;
import com.example.android.trivialdrivesample.util.IabResult;
import com.example.android.trivialdrivesample.util.Inventory;
import com.example.android.trivialdrivesample.util.Purchase;

import android.app.AlertDialog;
import android.util.Log;




public class IAPSetup implements OnIabSetupFinishedListener, OnIabPurchaseFinishedListener, QueryInventoryFinishedListener, OnConsumeFinishedListener{
	public IabHelper mIABHelper;
	Soccer activity;
	
	public IAPSetup() {
		activity = (Soccer) Soccer.getContext();
		loadIAP();
	}

	private void loadIAP() {
		//need to update KEY
		String base64EncodedPublicKey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAhJmfjo26s65jc2KYdfLUXMDcqngvhG6ylCgF+lX051fFjzC4FLCgxPG4Aqnuu0RJNYw0n952JOyr+T2aQrzXHbrsH7YD4ySXUCNBnFPxw/3y4W6OCIKubrwpLB301bRMmyPt7FBzTlX2IWBAzNFMO5NR/h+9QHYxCxImx1O1Bue1M6A3Aob+y6okDRPGw427oanD6Ds82KGSymw1LbnFehcNW3qhy0JJnqihazRAdWFmY48WNAjcGcnb3onQkT7+sxFfGasFwvYLT6GjSVson3htVDbwukQ/eux8IFf+S8Ky+L3TmrNZzLYCVd3GgSnRmhIPo0vC7c0fVsCbe5SIgQIDAQAB";
		mIABHelper = new IabHelper(activity, base64EncodedPublicKey);
		mIABHelper.enableDebugLogging(true);
		mIABHelper.startSetup(this);
		
	}

	void complain(final String message) {
        activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
		        alert("Error: " + message);
			}
		});
    }
	
	void alert(String message) {
        AlertDialog.Builder bld = new AlertDialog.Builder(activity);
        bld.setMessage(message);
        bld.setNeutralButton("OK", null);
        bld.create().show();
    }
	
	@Override
	public void onIabSetupFinished(IabResult result) {
		Log.v("pankaj", "112222");
		if (!result.isSuccess()) {
			Log.v("pankaj", "ldkl;dk;dk;dl");
			activity.isBillingSupported = false;
			return;
		}
		mIABHelper.queryInventoryAsync(this);
	}
	
	// Callback method when purchase is finished
	@Override
	public void onIabPurchaseFinished(IabResult result, Purchase purchaseInfo) {
		
		if (result.isFailure()) {
			complain("Error purchasing: " + result);
			return;
		}
		if (purchaseInfo.getSku().equalsIgnoreCase(Soccer.REMOVE_ADDS_SKU)) {
		
			mIABHelper.consumeAsync(purchaseInfo, this);
		}
	}

	// HoneycombListener that's called when we finish querying the items we own
	@Override
	public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
		if (result.isFailure()) {
//			complain("Failed to query inventory: " + result);
			return;
		}
		if(inventory.hasPurchase(Soccer.REMOVE_ADDS_SKU)){
			mIABHelper.consumeAsync(inventory.getPurchase(Soccer.REMOVE_ADDS_SKU), this);
		}	
	}
	@Override
	public void onConsumeFinished(Purchase purchase, IabResult result) {
		if (result.isSuccess()) {
			Log.v("pankaj", "pankaj12");
			activity.setAdsFreeVersion(true);
		}else {
//			complain("Error while consuming: " + result);
		}
	}

	
	// Called when consumption is complete
	
}
