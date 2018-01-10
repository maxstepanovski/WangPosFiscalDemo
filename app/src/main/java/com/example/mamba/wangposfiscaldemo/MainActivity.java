package com.example.mamba.wangposfiscaldemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private Button testFiscalChip;

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        testFiscalChip = findViewById(R.id.test_fiscal_chip_button);
        testFiscalChip.setOnClickListener(view -> {
            stringFromJNI();
        });
        // Example of a call to a native method
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public static void main(String[] args){
        String test = "1111";
        Log.d("happy", String.valueOf(test.hashCode()));
    }
}
