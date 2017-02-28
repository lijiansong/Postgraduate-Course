package cn.ac.ict.restful;

import android.content.Context;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.util.Base64;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;

import javax.net.ssl.HttpsURLConnection;

public class MainActivity extends AppCompatActivity {


    private static Context mContext;
    private static final String API_KEY="YGyI3APWnLGSiIFUWEnhBEoC";
    private static final String SECRET_KEY="fc4d81ef45486b17da48d6d2e81b65d5";
    private StringBuilder mResponseStr;
    private JSONObject mVoicePackageJsonObject;

    TextView mTextViewResponse=null;
    Button mBtnAccess=null;
    Button mBtnPaeseVoice=null;
    //HttpClient mHttpClient;
    URL url;
    HttpsURLConnection urlConnection=null;
    Handler handler=new Handler(){
        public void handleMessage(android.os.Message msg) {
            if (msg.what==0x123) {
                mTextViewResponse.append(msg.obj.toString()+"\n");
            }
        }
    };


    //get the audio file from res/raw dir
    public String getVoiceStringFromRaw(){
        //String result="";
        InputStream voiceInputStream=getResources().openRawResource(R.raw.test);
        StringBuilder result=new StringBuilder();
        try {
            //get the bytes of the file
//            int length=inputStream.available();
//            byte[] buffer=new byte[length];
//            inputStream.read(buffer);

            //convert inputstream to string
            BufferedReader bufferedReader=new BufferedReader(new InputStreamReader(voiceInputStream));
            String line=bufferedReader.readLine();
            while(line!=null){
                result.append(line);
                line=bufferedReader.readLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return result.toString();
    }

    //get the size of the voice data
    public long getRawVoiceSize(){
        long len=0;
        InputStream voiceInputStream=getResources().openRawResource(R.raw.test);
        try {
            len= voiceInputStream.available();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return len;
    }

    //package the voice data to json format,and return the package string
    public String getVoiceJsonPackageStr(){
        //String jsonStr="";
        //JSONObject voiceJsonObject=new JSONObject();
        try {
            mVoicePackageJsonObject.put("format","pcm").
                    put("rate",8000).
                    put("channel",1).
                    put("token",getAccessToken()).
                    put("cuid",getMacAddress(getAppContext())).
                    put("speech",getVoiceBase64Encode()).
                    put("len",getRawVoiceSize());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return mVoicePackageJsonObject.toString();
    }

    //get the voice json package size
    public long getVoiceJsonPackageSize(){
        if(mVoicePackageJsonObject!=null)
            return mVoicePackageJsonObject.toString().length();
        else
            return -1;
    }



    //get the mac address of the mobile end
    public String getMacAddress(Context mContext){
        String macStr="";
        WifiManager wifiManager=(WifiManager) mContext.getSystemService(Context.WIFI_SERVICE);
        WifiInfo wifiInfo=wifiManager.getConnectionInfo();
        if (wifiInfo.getMacAddress()!=null){
            macStr=wifiInfo.getMacAddress();
        }
        return macStr;
    }
    //get the context of the app
    public static Context getAppContext(){
        return MainActivity.mContext;
    }

    //parse the access_token from Baidu server
    public String getAccessToken() {
        String accessTokenStr="";
        if(mResponseStr!=null){
            JSONObject jsonObject= null;
            try {
                jsonObject = new JSONObject(getServerResponseStr());
                accessTokenStr=jsonObject.getString("access_token");
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }
        return accessTokenStr;
    }


    //get the response string of Baidu Server
    public String getServerResponseStr(){
        return mResponseStr.toString();
    }

    //get Base64 encoded data string of the voice data
    public String getVoiceBase64Encode(){
        return Base64.encodeToString(getVoiceStringFromRaw().getBytes(),Base64.DEFAULT);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mResponseStr=new StringBuilder();
        mVoicePackageJsonObject=new JSONObject();
        //mHttpClient=new DefaultHttpClient();

        MainActivity.mContext=getApplicationContext();
        mTextViewResponse= (TextView) findViewById(R.id.txtview_response);
        mBtnAccess= (Button) findViewById(R.id.btn_access);
        mBtnPaeseVoice= (Button) findViewById(R.id.btn_parse);

        mBtnAccess.setOnClickListener(new BtnAccessListener());
        mBtnPaeseVoice.setOnClickListener(new BtnParseVoiceListener());

    }
    class BtnParseVoiceListener implements View.OnClickListener{
        @Override
        public void onClick(View v) {
            //TODO:add parsing voice
            Toast.makeText(MainActivity.this,
                    "++++\n"+getAccessToken(),
                    Toast.LENGTH_LONG).show();
        }
    }
    class BtnAccessListener implements View.OnClickListener{
        @Override
        public void onClick(View v) {
            mTextViewResponse.setText("");
            //mTextViewResponse.setText(Base64.encodeToString(getVoiceStringFromRaw().getBytes(),Base64.DEFAULT));
            mTextViewResponse.append(getMacAddress(getAppContext()).toString()+"\n");
            //getServerResponseStr();
            new Thread(){
                public void run(){
                    try {
                        url=new URL("https://openapi.baidu.com/oauth/2.0/token?grant_type=client_credentials&client_id="
                                +API_KEY+
                                "&client_secret="+
                                SECRET_KEY);

                        urlConnection= (HttpsURLConnection) url.openConnection();
                        urlConnection.setRequestMethod("POST");
                        urlConnection.connect();

                        int statusCode=urlConnection.getResponseCode();
                        if(statusCode!=HttpsURLConnection.HTTP_ACCEPTED){
                            //onCreateDialog().dismiss();
                            //mTextViewResponse.append("Error!\nFailed to connect to Baidu server!\n\n");
                            //return null;
                        }
                        InputStream inputStream=new BufferedInputStream(urlConnection.getInputStream());

                        BufferedReader reader=new BufferedReader(new InputStreamReader(inputStream));
                        //StringBuilder responseText=new StringBuilder();

                        String line=null;
                        while ((line=reader.readLine())!=null){
                            mResponseStr.append(line);
                            Message msg=new Message();
                            msg.what=0x123;
                            msg.obj=line;
                            handler.sendMessage(msg);
                        }


                    } catch (MalformedURLException e) {
                        e.printStackTrace();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    finally {
                        urlConnection.disconnect();
                    }
                }
            }.start();
            //mTextViewResponse.append("++++++++++++++++++\n\n\n"+getServerResponseStr());
        }
    }
}
