package com.example.redesocial;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class register extends AppCompatActivity {

    private EditText Email;
    private EditText Password;
    private Button Register;
    private EditText Name;
    private database myDb;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);

        Email =  findViewById(R.id.emailRegister);
        Password = findViewById(R.id.passwordRegister);
        Name = findViewById(R.id.nameRegister);
        Register =  findViewById(R.id.register);
        myDb = new database(this);
        AddData();
    }

    public void AddData() {
        Register.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                boolean isInserted = myDb.insertData(Name.getText().toString(), Email.getText().toString(), Password.getText().toString());
                if (isInserted == true) {
                    Toast toast = Toast.makeText(getApplicationContext(), "Registado", Toast.LENGTH_SHORT);
                    toast.show();
                    finish();
                }
                else {
                    Toast toast = Toast.makeText(getApplicationContext(),"Erro",Toast.LENGTH_SHORT);
                    toast.show();
                }
            }
        });
    }

}
