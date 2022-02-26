package com.example.redesocial;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    BluetoothAdapter mBluetoothAdapter;
    private Button Chat;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setTitle("QuaranLive");

        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        Chat = findViewById(R.id.goChat);
        Chat.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent enableBT = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivity(enableBT);
                Intent intent = getIntent();
                Bundle b = intent.getExtras();
                Intent goDeviceList = new Intent(MainActivity.this, DeviceList.class);
                goDeviceList.putExtra("Id", b.getString("Id"));
                startActivity(goDeviceList);
            }
        });
    }
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.mainmenu, menu);
        return true;
    }

   /* @Override
    protected void onDestroy() {
        super.onDestroy();
        unregisterReceiver(mBroadcastReciever1);
    }*/

    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        switch(item.getItemId()) {
            case R.id.settings:
                Intent intent = getIntent();
                Bundle b = intent.getExtras();
                Intent goSettings = new Intent(MainActivity.this, settings.class);
                goSettings.putExtra("Id", b.getString("Id"));
                startActivity(goSettings);
                return true;
            case R.id.bluetooth:
                enableDisableBt();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    private void enableDisableBt() {
        if(!mBluetoothAdapter.isEnabled()) {
            Intent enableBT = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivity(enableBT);

        }
        if(mBluetoothAdapter.isEnabled()) {
            mBluetoothAdapter.disable();

        }
    }

}
