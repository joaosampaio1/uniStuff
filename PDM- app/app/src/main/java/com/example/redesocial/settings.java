package com.example.redesocial;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class settings extends AppCompatActivity {

    private EditText Email;
    private EditText Password;
    private Button Updater;
    private EditText Name;
    database myDb;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        Email = findViewById(R.id.emailUpdate);
        Password = findViewById(R.id.passwordUpdate);
        Name = findViewById(R.id.nameUpdate);
        Updater = findViewById(R.id.updater);
        myDb = new database(this);
        UpdateData();
    }

    public void UpdateData() {
        Updater.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = getIntent();
                Bundle b = intent.getExtras();
                String Id = b.getString("Id");
                boolean isUpdated = myDb.updateData(Id,Name.getText().toString(), Email.getText().toString(), Password.getText().toString());
                if (isUpdated == true) {
                    finish();
                }
                else {
                    Toast toast = Toast.makeText(getApplicationContext(),"Error",Toast.LENGTH_SHORT);
                    toast.show();

               }
            }
        });
    }

}
