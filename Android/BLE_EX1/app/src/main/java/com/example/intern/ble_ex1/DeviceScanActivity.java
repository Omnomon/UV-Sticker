/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.example.intern.ble_ex1;

import android.app.Activity;
import android.app.ListActivity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

import static android.content.ContentValues.TAG;

/**
 * Activity for scanning and displaying available Bluetooth LE devices.
 */
public class DeviceScanActivity extends ListActivity
{
    private LeDeviceListAdapter mLeDeviceListAdapter;

    private List<String> ble_array_list = new ArrayList<>();
    private ArrayAdapter<String> arrayAdapter;

    private BluetoothAdapter mBluetoothAdapter;
    private boolean mScanning;
    private Handler mHandler;

    private boolean enableScanning;
    private boolean currentScanning;

    private ListView bleList;

    private static final int REQUEST_ENABLE_BT = 1;

    // Stops scanning after 10 seconds.
    private static final long SCAN_PERIOD = 10000;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        mHandler = new Handler();

        enableScanning = false;     // Boolean used to only scan when button has been pressed
        currentScanning = false;    // Boolean used to determine if scanning is in progress

        setContentView(R.layout.ble_connect);

        Log.w(TAG, "DeviceScanActivity: onCreate");

        //Connect U.I Elements
        Button  connect_Ble_Button = (Button) findViewById(R.id.ConnectBleBtn);     //Connect to BLE Device
        Button start_Scan_Button = (Button) findViewById(R.id.startScanBtn);        //Start BLE Scan
        Button stop_Scan_Button = (Button) findViewById(R.id.stopScanBtn);          //Stop BLE Scan
        bleList = getListView();
        bleList.setAdapter(new LeDeviceListAdapter());

        mLeDeviceListAdapter = new LeDeviceListAdapter();
        setListAdapter(mLeDeviceListAdapter);        // Initializes list view adapter.

        arrayAdapter = new ArrayAdapter<String>(DeviceScanActivity.this, android.R.layout.simple_expandable_list_item_1, ble_array_list);

        checkBLE();     // Check if the function has BLE functionality
        initialize_bluetooth_adapter(); // Initialize Bluetooth Adapter
        enable_bluetooth(); // Enable Bluetooth
        checkBluetooth();   // Check if Bluetooth has been enabled

        buttonClicked(start_Scan_Button, stop_Scan_Button, connect_Ble_Button);     //Enable Button Click Listener
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        enable_bluetooth();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        Log.v(TAG, "DeviceScanActivity: onActivityResult");

        // User chose not to enable Bluetooth.
        if (requestCode == REQUEST_ENABLE_BT && resultCode == Activity.RESULT_CANCELED)
        {
            finish();
            return;
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    protected void onPause()
    {
        Log.v(TAG, "DeviceScanActivity: onPause");
        super.onPause();
        stopScan();
//        scanLeDevice(false);
        mLeDeviceListAdapter = new LeDeviceListAdapter();
        setListAdapter(mLeDeviceListAdapter);
        mLeDeviceListAdapter.clear();
    }

    @Override
    protected void onListItemClick(ListView l, View v, int position, long id)
    {
        final BluetoothDevice device = mLeDeviceListAdapter.getDevice(position);
        if(device == null)
        {
            return;
        }
        final Intent intent = new Intent(this, DeviceControlActivity.class);
        intent.putExtra(DeviceControlActivity.EXTRAS_DEVICE_NAME, device.getName());
        intent.putExtra(DeviceControlActivity.EXTRAS_DEVICE_ADDRESS, device.getAddress());
        if(mScanning)
        {
            mBluetoothAdapter.stopLeScan(mLeScanCallback);
            mScanning = false;
        }
        startActivity(intent);
    }

    private void buttonClicked(Button start_Scan_Button, Button stop_Scan_Button, Button connect_Ble_Button)
    {
        start_Scan_Button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                Log.w(TAG, "Scan Button Pressed");
                enableScanning = true;
//                mLeDeviceListAdapter.clear();
//                mLeDeviceListAdapter = new LeDeviceListAdapter();
//                setListAdapter(mLeDeviceListAdapter);
//                scanLeDevice(true);
                startScan();
//                bleList.setAdapter(arrayAdapter);
                mLeDeviceListAdapter = new LeDeviceListAdapter();
                setListAdapter(mLeDeviceListAdapter);
//        startScan();
                scanLeDevice(true);
            }
        });

        stop_Scan_Button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                Log.w(TAG, "Stop Button Pressed");
                enableScanning = false;
                stopScan();
                mLeDeviceListAdapter = new LeDeviceListAdapter();
                setListAdapter(mLeDeviceListAdapter);
                mLeDeviceListAdapter.clear();
            }
        });

        connect_Ble_Button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                Log.w(TAG, "Connect Button Pressed");
                enableScanning = false;
            }
        });
    }

    // This function checks if BLE is enabled on the device
    private void checkBLE()
    {
        Log.v(TAG, "DeviceScanActivity: checkBLE");
        // Use this check to determine whether BLE is supported on the device.  Then you can
        // selectively disable BLE-related features.
        if (!getPackageManager().hasSystemFeature(PackageManager.FEATURE_BLUETOOTH_LE))
        {
            Toast.makeText(this, R.string.ble_not_supported, Toast.LENGTH_SHORT).show();
            finish();
        }
    }

    // This function checks if Bluetooth is enabled on the device
    private void checkBluetooth()
    {
        Log.v(TAG, "DeviceScanActivity: CheckBluetooth");
        // Checks if Bluetooth is supported on the device.
        if (mBluetoothAdapter == null)
        {
            Toast.makeText(this, "Bluetooth is not supported", Toast.LENGTH_SHORT).show();
            finish();
        }
    }

    // Initialize Bluetooth Adapter
    private void initialize_bluetooth_adapter()
    {
        // Initializes Bluetooth adapter.
        Log.w(TAG, "DeviceScanActivity: Initialize Bluetooth Adapter");
        final BluetoothManager bluetoothManager = (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
        mBluetoothAdapter = bluetoothManager.getAdapter();
    }

    // Eanble Bluetooth on Device
    private void enable_bluetooth()
    {
        Log.w(TAG, "DeviceScanActivity: Enable Bluetooth Adapter");
        // Ensures Bluetooth is available on the device and it is enabled. If not,
        // displays a dialog requesting user permission to enable Bluetooth.
        if (mBluetoothAdapter == null || !mBluetoothAdapter.isEnabled())
        {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }
    }

    private void startScan()
    {
        Log.v(TAG, "DeviceScanActivity: startScan");
        if(enableScanning && !currentScanning)
        {
            scanLeDevice(true);
            currentScanning = true;
        }
    }

    private void stopScan()
    {
        Log.v(TAG, "DeviceScanActivity: stopScan");
        if(!enableScanning && currentScanning)
        {
            scanLeDevice(false);
            currentScanning = false;
        }
    }

    private void scanLeDevice(final boolean enable)
    {
        Log.w(TAG, "DeviceScanActivity: ScanLeDevice");
        if(enable)
        {
            Log.w(TAG, "ScanLeDevice: Start Scanning");
            // Stops scanning after a pre-defined scan period.
            mHandler.postDelayed(new Runnable()
            {
                @Override
                public void run()
                {
                    mScanning = false;
                    mBluetoothAdapter.stopLeScan(mLeScanCallback);
                    invalidateOptionsMenu();
                }
            }, SCAN_PERIOD);

            mScanning = true;
            mBluetoothAdapter.startLeScan(mLeScanCallback);
        }
        else
        {
            Log.w(TAG, "ScanLeDevice: Stop Scanning");
            mScanning = false;
            mBluetoothAdapter.stopLeScan(mLeScanCallback);
        }
        invalidateOptionsMenu();
    }

    // Adapter for holding devices found through scanning.
    private class LeDeviceListAdapter extends BaseAdapter
    {
        private ArrayList<BluetoothDevice> mLeDevices;
        private LayoutInflater mInflator;

        public LeDeviceListAdapter()
        {
            super();
            mLeDevices = new ArrayList<BluetoothDevice>();
            mInflator = DeviceScanActivity.this.getLayoutInflater();
        }

        public void addDevice(BluetoothDevice device)
        {
            if(!mLeDevices.contains(device))
            {
                mLeDevices.add(device);
            }
        }

        public BluetoothDevice getDevice(int position)
        {
            return mLeDevices.get(position);
        }

        public void clear()
        {
            mLeDevices.clear();
        }

        @Override
        public int getCount()
        {
            return mLeDevices.size();
        }

        @Override
        public Object getItem(int i)
        {
            return mLeDevices.get(i);
        }

        @Override
        public long getItemId(int i)
        {
            return i;
        }

        @Override
        public View getView(int i, View view, ViewGroup viewGroup)
        {
            ViewHolder viewHolder;
            // General ListView optimization code.
            if (view == null)
            {
                view = mInflator.inflate(R.layout.listitem_device, null);
                viewHolder = new ViewHolder();
                viewHolder.deviceAddress = (TextView) view.findViewById(R.id.device_address);
                viewHolder.deviceName = (TextView) view.findViewById(R.id.device_name);
                view.setTag(viewHolder);
            }
            else
            {
                viewHolder = (ViewHolder) view.getTag();
            }

            BluetoothDevice device = mLeDevices.get(i);
            final String deviceName = device.getName();
            if (deviceName != null && deviceName.length() > 0)
                viewHolder.deviceName.setText(deviceName);
            else
                viewHolder.deviceName.setText(R.string.unknown_device);
            viewHolder.deviceAddress.setText(device.getAddress());

            return view;
        }
    }

    // Device scan callback.
    private BluetoothAdapter.LeScanCallback mLeScanCallback = new BluetoothAdapter.LeScanCallback()
    {
        @Override
        public void onLeScan(final BluetoothDevice device, int rssi, byte[] scanRecord)
        {
            runOnUiThread(new Runnable()
            {
                @Override
                public void run()
                {
                    mLeDeviceListAdapter.addDevice(device);
                    mLeDeviceListAdapter.notifyDataSetChanged();
                }
            });
        }
    };

    static class ViewHolder
    {
        TextView deviceName;
        TextView deviceAddress;
    }
}