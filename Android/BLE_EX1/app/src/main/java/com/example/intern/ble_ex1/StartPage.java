package com.example.intern.ble_ex1;

import android.Manifest;
import android.annotation.TargetApi;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.util.Log;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class StartPage extends AppCompatActivity
{
    private final static String TAG = BluetoothLeService.class.getSimpleName();
    final private int REQUEST_CODE_ASK_MULTIPLE_PERMISSIONS = 124;
    private List<String> ble_array_list = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.ble_connect);

        if (Build.VERSION.SDK_INT >= 23)
        {
            // Marshmallow+ Permission APIs
            askforPermission();
        }

        //Connect U.I Elements
        Button  connect_Ble_Button = (Button) findViewById(R.id.ConnectBleBtn);
        Button start_Scan_Button = (Button) findViewById(R.id.startScanBtn);
        Button stop_Scan_Button = (Button) findViewById(R.id.stopScanBtn);
        ListView bleList = (ListView) findViewById(R.id.listview_ble_scan);

        ArrayAdapter<String> arrayAdapter = new ArrayAdapter<String>(StartPage.this, android.R.layout.simple_expandable_list_item_1, ble_array_list);

        buttonClicked(start_Scan_Button, stop_Scan_Button, connect_Ble_Button, bleList, arrayAdapter);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item)
    {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings)
        {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    private void buttonClicked(Button start_Scan_Button, Button stop_Scan_Button, Button connect_Ble_Button, final ListView bleList, final ArrayAdapter arrayAdapter)
    {
        start_Scan_Button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                Log.w(TAG, "Starting Scanning");
//                Intent intent = new Intent(StartPage.this, DeviceScanActivity.class);
//                startActivity(intent);
                ble_array_list.add("Foo");
                ble_array_list.add("Bar");
                ble_array_list.add("Carl!");
                bleList.setAdapter(arrayAdapter);

//                startGraph(temp_Notification, uv_Notification, resp_Notification);
            }
        });
        stop_Scan_Button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                //stopGraph(temp_Notification, uv_Notification, resp_Notification);
            }
        });
        connect_Ble_Button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                Intent intent = new Intent(StartPage.this, MainActivity.class);
                startActivity(intent);
                //saveGraph(temp_Notification, uv_Notification, resp_Notification);
            }
        });
    }
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults)
    {
        switch (requestCode)
        {
            case REQUEST_CODE_ASK_MULTIPLE_PERMISSIONS:
                {
                Map<String, Integer> perms = new HashMap<String, Integer>();
                // Initial
                perms.put(Manifest.permission.ACCESS_FINE_LOCATION, PackageManager.PERMISSION_GRANTED);


                // Fill with results
                for (int i = 0; i < permissions.length; i++)
                    perms.put(permissions[i], grantResults[i]);

                // Check for ACCESS_FINE_LOCATION
                if (perms.get(Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED)
                {
                    // All Permissions Granted

                    // Permission Denied
                    Toast.makeText(StartPage.this, "All Permission GRANTED !! Thank You :)", Toast.LENGTH_SHORT).show();


                }
                else
                {
                    // Permission Denied
                    Toast.makeText(StartPage.this, "One or More Permissions are DENIED Exiting App :(", Toast.LENGTH_SHORT).show();
                    finish();
                }
            }
            break;
            default:
                super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        }
    }


    @TargetApi(Build.VERSION_CODES.M)
    private void askforPermission()
    {
        List<String> permissionsNeeded = new ArrayList<String>();

        final List<String> permissionsList = new ArrayList<String>();
        if (!addPermission(permissionsList, Manifest.permission.ACCESS_FINE_LOCATION))
            permissionsNeeded.add("Show Location");

        if (permissionsList.size() > 0)
        {
            if (permissionsNeeded.size() > 0)
            {

                // Need Rationale
                String message = "App need access to " + permissionsNeeded.get(0);

                for (int i = 1; i < permissionsNeeded.size(); i++)
                    message = message + ", " + permissionsNeeded.get(i);

                showMessageOKCancel(message, new DialogInterface.OnClickListener()
                {
                            @Override
                            public void onClick(DialogInterface dialog, int which)
                            {
                                requestPermissions(permissionsList.toArray(new String[permissionsList.size()]), REQUEST_CODE_ASK_MULTIPLE_PERMISSIONS);
                            }
                        });
                return;
            }
            requestPermissions(permissionsList.toArray(new String[permissionsList.size()]), REQUEST_CODE_ASK_MULTIPLE_PERMISSIONS);
            return;
        }

        Toast.makeText(StartPage.this, "No new Permission Required- Launching App .You are Awesome!!", Toast.LENGTH_SHORT).show();
    }

    private void showMessageOKCancel(String message, DialogInterface.OnClickListener okListener)
    {
        new AlertDialog.Builder(StartPage.this)
                .setMessage(message)
                .setPositiveButton("OK", okListener)
                .setNegativeButton("Cancel", null)
                .create()
                .show();
    }

    @TargetApi(Build.VERSION_CODES.M)
    private boolean addPermission(List<String> permissionsList, String permission)
    {

        if (checkSelfPermission(permission) != PackageManager.PERMISSION_GRANTED)
        {
            permissionsList.add(permission);
            // Check for Rationale Option
            if (!shouldShowRequestPermissionRationale(permission))
                return false;
        }
        return true;
    }
}