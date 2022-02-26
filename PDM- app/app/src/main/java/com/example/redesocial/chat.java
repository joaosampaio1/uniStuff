package com.example.redesocial;

import androidx.appcompat.app.AppCompatActivity;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.database.Cursor;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.nio.charset.Charset;
import java.util.UUID;

public class chat extends AppCompatActivity {
    private EditText Message;
    private Button Send;
    private LinearLayout MessageLog;
    private static final UUID MY_UUID_INSECURE =
            UUID.fromString("8ce255c0-200a-11e0-ac64-0800200c9a66");
    BluetoothConnection mBluetoothConnection;
    BluetoothDevice mBTDevice;
    private static final String Tag = "BluetootheConnectionSer";
    private String Id;
    private String UserName;
    private database myDb;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chat);
        Message = findViewById(R.id.messageToSend);
        Send = findViewById(R.id.send);
        Intent intent = getIntent();
        Bundle b = intent.getExtras();
        MessageLog = findViewById(R.id.layout);
        LocalBroadcastManager.getInstance(this).registerReceiver(mReceiver, new IntentFilter("incomingMessage"));
        mBluetoothConnection = new BluetoothConnection(chat.this, b.getString("Id"));
        mBTDevice = getIntent().getExtras().getParcelable("mBTDevice");
        connection();
        Id = b.getString("Id");
        myDb = new database(this);
        Cursor res = myDb.getCursor(Id);
        UserName = res.getString(1);


        Send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String str = UserName;
                str = str.concat(":\n" +Message.getText().toString() + "\n");
                byte[] bytes = str.getBytes(Charset.defaultCharset());
                mBluetoothConnection.write(bytes);
                if (Message.getText().toString().equals("") == false) {
                    TextView txt = getTextView();
                    txt.setText(UserName + ":\n" + Message.getText().toString() + "\n");
                    MessageLog.addView(txt);
                    Message.setText("");
                }
            }
        });


    }


    public void startBTConnection(BluetoothDevice device, UUID uuid){
        mBluetoothConnection.startClient(device, uuid);
    }

    public void connection() {
        startBTConnection(mBTDevice,MY_UUID_INSECURE);
    }

    BroadcastReceiver mReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String text = intent.getStringExtra("theMessage");

            TextView txt = getTextView();
            txt.setText(text);
            MessageLog.addView(txt);
        }
    };

    public TextView getTextView() {
        return new TextView(this);
    }

    @Override
    protected void onDestroy() {
        unregisterReceiver(mReceiver);
        super.onDestroy();
    }
}
