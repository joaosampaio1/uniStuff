package com.example.redesocial;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class database extends SQLiteOpenHelper {

    private static final String PROFILE = "profile.db";
    private static final String TABLE_PROFILE = "profile_table";
    private static final String COL0 = "ID";
    private static final String COL1 = "NAME";
    private static final String COL2 = "PASSWORD";
    private static final String COL3 = "EMAIL";


    public database(Context context) {
        super(context, PROFILE, null, 1);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {


        db.execSQL("create table " + TABLE_PROFILE +" (ID INTEGER PRIMARY KEY AUTOINCREMENT,NAME TEXT NOT NULL ,PASSWORD TEXT NOT NULL,EMAIL TEXT UNIQUE NOT NULL)");
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS "+ TABLE_PROFILE);
        onCreate(db);
    }

    public boolean insertData(String name, String email, String password) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues contentvalues = new ContentValues();
        contentvalues.put(COL1, name);
        contentvalues.put(COL2, password);
        contentvalues.put(COL3, email);
        long result = db.insert(TABLE_PROFILE, null, contentvalues);
        if(result == -1) return false;
        else return true;
    }

    public Cursor getPassword(String email) {
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor res = db.rawQuery("select * from "+TABLE_PROFILE+" where "+COL3+" = '"+email+ "'",null);
        if(res.getCount() != 0) res.moveToNext();
        return res;
    }

    public Cursor getCursor(String id) {
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor res = db.rawQuery("select * from "+TABLE_PROFILE+" where "+COL0+" = '"+id+ "'",null);
        if(res.getCount() != 0) res.moveToNext();
        return res;
    }

    public boolean updateData(String id, String name, String email, String password) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues contentvalues = new ContentValues();
        contentvalues.put(COL0, id);
        contentvalues.put(COL1, name);
        contentvalues.put(COL2, password);
        contentvalues.put(COL3, email);
        db.update(TABLE_PROFILE, contentvalues, "ID = ?",new String[] {id });
        return true;
    }

}
