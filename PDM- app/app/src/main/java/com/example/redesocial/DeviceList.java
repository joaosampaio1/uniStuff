package com.example.redesocial;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;

import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.UUID;


public class DeviceList extends AppCompatActivity {

    BluetoothAdapter mBluetoothAdapter;
    public ArrayList<BluetoothDevice> mBTDevices = new ArrayList<>();
    private Button Search;
    private LinearLayout Layout;
    BluetoothConnection mBluetoothConnection;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_device_list);
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        makeDiscoverable();
        Search = findViewById(R.id.search);

        Search.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.M)
            @Override
            public void onClick(View view) {
                searchDevices();
            }
        });
    }
    private BroadcastReceiver mBroadcastReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            if (action.equals(BluetoothDevice.ACTION_FOUND)){
                BluetoothDevice device = intent.getParcelableExtra (BluetoothDevice.EXTRA_DEVICE);
                mBTDevices.add(device);
                checkPair();
            }
        }
    };

    @RequiresApi(api = Build.VERSION_CODES.M)
    private void searchDevices() {
        if (mBluetoothAdapter.isDiscovering()) {
            mBluetoothAdapter.cancelDiscovery();
        }
        mBTDevices.clear();
        checkBTPermissions();
        mBluetoothAdapter.startDiscovery();
        IntentFilter BTIntent = new IntentFilter(BluetoothDevice.ACTION_FOUND);
        registerReceiver(mBroadcastReceiver, BTIntent);


    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    private void checkBTPermissions() {
        if(Build.VERSION.SDK_INT > Build.VERSION_CODES.LOLLIPOP) {
            int permissionCheck = this.checkSelfPermission("Manifest.permission.ACCESS_FINE_LOCATION");
            permissionCheck += this.checkSelfPermission("Manifest.permission.ACCESS_COARSE_LOCATION");
            if (permissionCheck != 0) {

                this.requestPermissions(new String[]{Manifest.permission.ACCESS_FINE_LOCATION, Manifest.permission.ACCESS_COARSE_LOCATION}, 1001); //Any number
            }
        }
    }

    private void makeDiscoverable() {
        Intent makeDisc = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
        makeDisc.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION,120);
        startActivity(makeDisc);

    }

    private void checkPair() {
        int size = mBTDevices.size();
        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT);
        Layout = findViewById(R.id.linear);
        Layout.removeAllViews();
        for (int i=0; i<size; i++) {
            BluetoothDevice device = mBTDevices.get(i);
            if (device != null) {
                if (device.getName() != null) {
                    Button btn = new Button(this);
                    btn.setId(i);
                    btn.setBackgroundResource(R.color.orangeLogo);
                    btn.setTextColor(getResources().getColor(R.color.blueLogo));
                    final int id_ = btn.getId();
                    final BluetoothDevice device_ = device;
                    btn.setText(device.getName());
                    Layout.addView(btn, params);
                    btn.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View view) {
                            mBluetoothAdapter.cancelDiscovery();
                            Intent goDeviceList = new Intent(DeviceList.this, chat.class);
                            goDeviceList.putExtra("mBTDevice", mBTDevices.get(id_));
                            Intent intent = getIntent();
                            Bundle b = intent.getExtras();
                            goDeviceList.putExtra("Id", b.getString("Id"));
                            if (device_.getBondState() == BluetoothDevice.BOND_BONDED) {
                                startActivity(goDeviceList);
                                finish();
                            }
                            else {
                                mBTDevices.get(id_).createBond();
                                if (device_.getBondState() == BluetoothDevice.BOND_BONDED) {
                                    startActivity(goDeviceList);
                                    finish();
                                }
                            }
                        }
                    });
                }
            }
        }
    }

    @Override
    protected void onDestroy() {
        unregisterReceiver(mBroadcastReceiver);
        super.onDestroy();
    }
}
