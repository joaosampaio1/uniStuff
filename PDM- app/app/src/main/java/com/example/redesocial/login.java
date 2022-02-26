package com.example.redesocial;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class login extends AppCompatActivity {

    database myDb;
    private EditText Email;
    private EditText Password;
    private Button Login;
    private Button Register;


    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        Email = findViewById(R.id.emailCheckLogin);
        Password = findViewById(R.id.passwordLoginCheck);
        Login = findViewById(R.id.loginCheck);
        Register = findViewById(R.id.register);
        myDb = new database(this);



        Register.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(login.this, register.class);
                startActivity(intent);
            }
        });

        Login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                validate(Email.getText().toString(), Password.getText().toString());
            }
        });
    }

    private void validate(String email, String password) {
        Cursor res=myDb.getPassword(email);
        Toast toast = Toast.makeText(getApplicationContext(),"Credenciais erradas",Toast.LENGTH_SHORT);
        if (res.moveToFirst()==false) {
            toast.show();
            return ;
        }
        String passwordTable = res.getString(2);
        if (password.equals(passwordTable)) {
            Intent intent = new Intent(login.this, MainActivity.class);
            intent.putExtra("Id", res.getString(0));
            startActivity(intent);
            finish();
        }
        else {
            toast.show();
        }
    }
}
