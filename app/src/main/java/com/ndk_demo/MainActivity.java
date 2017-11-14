package com.ndk_demo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Date;
import java.util.Random;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    private int arr[]={1,2,1,2,1};
    public  String key = "key";
    private  int count =10;

    public native static void initIDs();
    public native void method();


    public native String stringFromJNI();

    public native static String getFromC();

    public native String getFromC2(String input);

    public native int getFromC3(int[] arr);


    public native String accessField();

    public native void accessField2();

    public native void accessMethod();

    public  native int accessStaticMethod();

    public native Date accessDateMethod();

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
       // String s = accessField();
        //accessField2();
        //accessMethod();
   //    tv.setText(getFromC2("滴滴滴滴"));

       // initIDs();
       // method();
      // accessStaticMethod();
      //  tv.setText(accessStaticMethod()+"");
        tv.setText(accessDateMethod()+"");
    }


    void showToast(){
        Toast.makeText(this,"hello jni",Toast.LENGTH_LONG).show();
    }

    static int maxNum(int a,int b){
        return a>b?a:b;
    }

}
