package com.example.redesocial;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.util.Log;
import android.widget.Toast;

import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.Charset;
import java.util.UUID;

public class BluetoothConnection {
    private static final String Tag = "BluetootheConnectionSer";
    private static final String appName = "MYAPP";
    private static final UUID MY_UUID_INSECURE =
            UUID.fromString("8ce255c0-200a-11e0-ac64-0800200c9a66");
    private final BluetoothAdapter mBluetoothAdapter;
    private AcceptThread mInsecureAcceptThread;
    private ConnectThread mConnectThread;
    private BluetoothDevice mmDevice;
    private UUID deviceUUID;
    private database myDb;
    Context mContext;
    private ConnectedThread mConnectedThread;
    private String id;

    public BluetoothConnection(Context context, String id){
        mContext = context;
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        start();
        this.id = id;
    }

    public class AcceptThread extends Thread {
        private final BluetoothServerSocket mmServerSocket;
        public AcceptThread() {
            BluetoothServerSocket tmp = null;
            Log.d(Tag, "ACCEPTTHREAD");
            try {
                tmp = mBluetoothAdapter.listenUsingInsecureRfcommWithServiceRecord(appName, MY_UUID_INSECURE);
            }
            catch(IOException e) {}
            mmServerSocket = tmp;
        }


        public void run() {
            Log.d(Tag, "ACCEPTTHREADRUN");
            BluetoothSocket socket = null;
            try {
                socket = mmServerSocket.accept();
            } catch (IOException e) {
            }
            if (socket != null) {
                connected(socket, mmDevice);
            }
        }
        public void cancel() {
            Log.d(Tag, "ACCEPTTHREADCANCEL");
            try {
                mmServerSocket.close();
            } catch (IOException e) { }
        }
    }

    private class ConnectThread extends Thread {
        private BluetoothSocket mmSocket;

        public ConnectThread(BluetoothDevice device, UUID uuid) {
            mmDevice = device;
            deviceUUID = uuid;
            Log.d(Tag, "CONNECTTHREAD");
        }

        public void run() {
            Log.d(Tag, "CONNECTTHREADRUN");
            BluetoothSocket tmp = null;
            try {
                tmp = mmDevice.createRfcommSocketToServiceRecord(deviceUUID);
            } catch (IOException e) {
            }
            mmSocket = tmp;
            mBluetoothAdapter.cancelDiscovery();
            try {
                mmSocket.connect();
            } catch (IOException e) {
                try {
                    mmSocket.close();
                } catch (IOException eE) {
                }
            }
            connected(mmSocket, mmDevice);
        }

        public void cancel() {
            Log.d(Tag, "CONNECTTHREADCANCEL");
            try {
                mmSocket.close();
            } catch (IOException e) {
            }
        }
    }
    public synchronized void start() {
        Log.d(Tag, "START");
        if (mConnectThread !=null) {
            mConnectThread.cancel();
            mConnectThread = null;
        }
        if (mInsecureAcceptThread == null) {
            mInsecureAcceptThread = new AcceptThread();
            mInsecureAcceptThread.start();
        }
    }
    public void startClient(BluetoothDevice device, UUID uuid){
        Log.d(Tag, "STARTCLIENT");
        mConnectThread = new ConnectThread(device, uuid);
        mConnectThread.start();
    }

    private class ConnectedThread extends Thread {
        private final BluetoothSocket mmSocket;
        private final InputStream mmInStream;
        private final OutputStream mmOutStream;

        public ConnectedThread(BluetoothSocket socket) {
            Log.d(Tag, "CONNECTEDTHREAD");
            mmSocket = socket;
            InputStream tmpIn = null;
            OutputStream tmpOut = null;
            try {
            }
            catch (NullPointerException e) {
            }
            try {
                tmpIn = mmSocket.getInputStream();
                tmpOut = mmSocket.getOutputStream();

            } catch (IOException E) {
            }
            mmInStream = tmpIn;
            mmOutStream = tmpOut;

        }
        public void run() {
            Log.d(Tag, "CONNECTEDTHREADRUN");
            byte[] buffer = new byte[1024];
            myDb = new database(mContext);
            int bytes;
            while (true) {
                try {
                    bytes = mmInStream.read(buffer);
                    String incomingMessage = new String(buffer, 0, bytes);

                    Intent intent = new Intent("incomingMessage");
                    intent.putExtra("theMessage", incomingMessage);
                    LocalBroadcastManager.getInstance(mContext).sendBroadcast(intent);
                    Log.d(Tag, "InputStream: " + incomingMessage);
                } catch (IOException e) {
                    break;
                }
            }
        }
        public void cancel() {
            Log.d(Tag, "CONNECTEDTHREADCANCEL");
            try {
                mmSocket.close();
            } catch (IOException e) {
            }
        }
        public void write(byte[] bytes) {
            String text = new String(bytes, Charset.defaultCharset());
            Log.d(Tag, "write: Writing to outputstream: " + text);
            Log.d(Tag, "CONNECTEDTHREADWRITE");
            try{
                mmOutStream.write(bytes);
            }
            catch(IOException E){}
        }
    }
    private void connected(BluetoothSocket mmSocket, BluetoothDevice mmDevice) {
        Log.d(Tag, "CONNECTED");
        mConnectedThread = new ConnectedThread(mmSocket);
        mConnectedThread.start();
    }
    public void write(byte[] out) {
        Log.d(Tag, "WRITE");
        mConnectedThread.write(out);
    }
}

    //Cursor res = myDb.getCursor(id);
    //String name = res.getString(1));