package cn.ac.ict.restful;

import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.util.Base64;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

import javax.net.ssl.HttpsURLConnection;

public class MainActivity extends AppCompatActivity
        implements View.OnClickListener{

    //ToDO: better support sync communication with Baidu server, especially for the network communication
    // use another interface SyncTask to communicate with Baidu server

    //ADD recorder control view
    ImageButton mBtnRecord;
    ImageButton mBtnStop;
    //MediaRecorder mMediaRecorder;
    AudioRecord mAudioRecord;
    boolean isRecording=false;
    Thread recordingThread;

    private static final int RECORDER_SOURCE= MediaRecorder.AudioSource.MIC;
    private static final int RECORDER_SAMPLERATE=8000;
    private static final int RECORDER_CHANNELS= AudioFormat.CHANNEL_IN_MONO;
    private static final int RECORDER_AUDIO_ENCODING= AudioFormat.ENCODING_PCM_16BIT;
    private static final String AUDIO_NAME="/8k16bitMono.pcm";

    // want to play 2048 (2K) since 2 bytes we use only 1024
    private int BufferElements2Rec = 1024;
    // 2 bytes in 16bit format
    private int BytesPerElement = 2;


    private static Context mContext;
    private static final String API_KEY="YGyI3APWnLGSiIFUWEnhBEoC";
    private static final String SECRET_KEY="fc4d81ef45486b17da48d6d2e81b65d5";
    private StringBuilder mResponseStr;
    private JSONObject mVoicePackageJsonObject;
    private StringBuilder mVoiceStr;

    TextView mTextViewResponse=null;
    Button mBtnAccess=null;
    Button mBtnPaeseVoice=null;
    //HttpClient mHttpClient;
    URL url;
    //HttpsURLConnection urlConnection=null;
    HttpURLConnection urlConnection=null;
    Handler handler=new Handler(){
        public void handleMessage(android.os.Message msg) {
            if (msg.what==0x123) {
                mTextViewResponse.append(msg.obj.toString()+"\n");
            }
            if(msg.what==0x124){
                mTextViewResponse.append(msg.obj.toString()+"\n");
            }
        }
    };

    //Conversion of short to byte
    private byte[] short2Byte(short[] data){
        int shortArraySize=data.length;
        byte[] bytes = new byte[shortArraySize * 2];
        for (int i=0;i<shortArraySize;++i){
            bytes[i * 2] = (byte) (data[i] & 0x00FF);
            bytes[(i * 2) + 1] = (byte) (data[i] >> 8);
            data[i] = 0;
        }
        return bytes;
    }

    //start recording in sync method and write audio data to file
    private void startRecording(){
        mAudioRecord=new AudioRecord(
                RECORDER_SOURCE,
                RECORDER_SAMPLERATE,
                RECORDER_CHANNELS,
                RECORDER_AUDIO_ENCODING,
                BufferElements2Rec*BytesPerElement
        );

        mAudioRecord.startRecording();
        isRecording=true;
        recordingThread=new Thread(new Runnable() {
            @Override
            public void run() {
                String filePath= Environment.getExternalStorageDirectory().getPath();
                short data[]=new short[BufferElements2Rec];

                FileOutputStream fileOutputStream=null;
                try {
                    fileOutputStream=new FileOutputStream(filePath+AUDIO_NAME);

                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
                while(isRecording){
                    // gets the voice output from microphone to byte format
                    mAudioRecord.read(data,0,BufferElements2Rec);
                    try {
                        // writes the data to file from buffer stores the voice buffer
                        byte audioData[]=short2Byte(data);
                        fileOutputStream.write(audioData,0,BufferElements2Rec * BytesPerElement);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }

                //close the file
                try {
                    fileOutputStream.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
        recordingThread.start();
    }

    //stop recording and release resourses
    public void stopRecording(){
        if(null!=mAudioRecord){
            isRecording=false;
            mAudioRecord.stop();
            mAudioRecord.release();
            mAudioRecord=null;
            recordingThread=null;
        }
    }

    @Override
    protected void onDestroy() {
        if(null!=mAudioRecord){
            isRecording=false;
            mAudioRecord.stop();
            mAudioRecord.release();
            mAudioRecord=null;
            recordingThread=null;
        }
        super.onDestroy();
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.record:
                if(!Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)){
                    Toast.makeText(MainActivity.this,"SD card doesn't exist!\n",Toast.LENGTH_LONG).show();
                    return;
                }
                startRecording();
                break;
            case R.id.stop:
                stopRecording();
                Toast.makeText(MainActivity.this,
                        "audio file have been writen to: "+Environment.getExternalStorageDirectory().getPath(),
                        Toast.LENGTH_LONG).show();
                break;
        }
    }

    //get the size of the voice data
    public long getRawVoiceSize(){
        long len=0;
        //modify to get the audio dynamically from the sd card
        //InputStream voiceInputStream=getResources().openRawResource(R.raw.test);
        try {
            //openFileInput doesn't accept path separators
            //InputStream voiceInputStream=openFileInput(Environment.getExternalStorageDirectory().getPath()+AUDIO_NAME);
            InputStream voiceInputStream=new FileInputStream(new File(Environment.getExternalStorageDirectory().getPath()+AUDIO_NAME));
            len= voiceInputStream.available();
            voiceInputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        //len=getVoiceStringFromRaw().length();
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
            //return mVoicePackageJsonObject.length();
            return mVoicePackageJsonObject.toString().length();
        else
            return -1;
    }

    //parse the JSON package to get the voice string
    public String[] getParsedVoiceStr(){
        String[] result={};
        try {
            JSONObject jsonObject=new JSONObject(mVoiceStr.toString());
            JSONArray resultArray=jsonObject.getJSONArray("result");
            if(resultArray.length()>0){
                result=new String[resultArray.length()];
                for(int i=0;i<resultArray.length();++i){
                    result[i]=resultArray.getString(i);
                }
            }

        } catch (JSONException e) {
            e.printStackTrace();
        }
        return result;
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

    //get the audio file from res/raw dir
    public String getVoiceStringFromRaw(){
        //String result="";
        //modify to get the audio data dynamically
        //InputStream voiceInputStream=getResources().openRawResource(R.raw.test);
        StringBuilder result=new StringBuilder();
        try {
            //InputStream voiceInputStream=openFileInput(Environment.getExternalStorageDirectory().getPath()+AUDIO_NAME);
            InputStream voiceInputStream=new FileInputStream(new File(Environment.getExternalStorageDirectory().getPath()+AUDIO_NAME));
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
            voiceInputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return result.toString();
    }

    //get Base64 encoded data string of the voice data
    public String getVoiceBase64Encode(){
        InputStream voiceInputStream=getResources().openRawResource(R.raw.test);
        byte[] buffer;
        //Base64InputStream base64InputStream=new Base64InputStream(voiceInputStream,Base64.DEFAULT);
        try {
            int length=voiceInputStream.available();
            buffer=new byte[length];
            voiceInputStream.read(buffer,0,length);

            voiceInputStream.close();
            //it is necessary to set the flag to NO_WRAP, otherwise Baidu's server will response you with a error msg "json param speech error", such a fucking requirement!
            return Base64.encodeToString(buffer,Base64.	NO_WRAP);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return "";
        //return Base64.encodeToString(getVoiceStringFromRaw().getBytes(),Base64.DEFAULT);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mResponseStr=new StringBuilder();
        mVoicePackageJsonObject=new JSONObject();
        mVoiceStr=new StringBuilder();
        //mHttpClient=new DefaultHttpClient();

        MainActivity.mContext=getApplicationContext();
        mTextViewResponse= (TextView) findViewById(R.id.txtview_response);
        mBtnAccess= (Button) findViewById(R.id.btn_access);
        mBtnPaeseVoice= (Button) findViewById(R.id.btn_parse);

        mBtnRecord= (ImageButton) findViewById(R.id.record);
        mBtnStop= (ImageButton) findViewById(R.id.stop);

        mBtnRecord.setOnClickListener(this);
        mBtnStop.setOnClickListener(this);

        mBtnAccess.setOnClickListener(new BtnAccessListener());
        mBtnPaeseVoice.setOnClickListener(new BtnParseVoiceListener());

    }
    class BtnParseVoiceListener implements View.OnClickListener{
        @Override
        public void onClick(View v) {
            //TODO:add parsing voice
//            Toast.makeText(MainActivity.this,
//                    "++++\n"+getAccessToken()+"\n raw voice size: "+getRawVoiceSize()+"\n json package size: "+getVoiceJsonPackageSize(),
//                    Toast.LENGTH_LONG).show();

            new Thread(){
                @Override
                public void run() {
                    //super.run();
                    try {
                        url=new URL("http://vop.baidu.com/server_api");
                        //urlConnection= (HttpsURLConnection) url.openConnection();
                        urlConnection= (HttpURLConnection) url.openConnection();
                        urlConnection.setDoOutput(true);
                        //http header
                        urlConnection.setRequestProperty("Content-Type", "application/json");
                        urlConnection.setRequestProperty("Accept-Charset","utf-8");
                        //response data in json-formated
                        urlConnection.setRequestProperty("Accept","application/json");
                        urlConnection.setRequestProperty("Content-Length",""+getVoiceJsonPackageSize());
                        urlConnection.setReadTimeout(30000);//30s time out,in milliseconds
                        urlConnection.setConnectTimeout(15000);
                        urlConnection.setRequestMethod("POST");

                        urlConnection.connect();

                        //write body
                        OutputStream outputStream=urlConnection.getOutputStream();
                        BufferedWriter writer=new BufferedWriter(new OutputStreamWriter(outputStream,"UTF-8"));
                        writer.write(getVoiceJsonPackageStr());
                        writer.flush();
                        writer.close();
                        outputStream.close();

                        //get the response
                        BufferedReader bufferedReader=new BufferedReader(new InputStreamReader(urlConnection.getInputStream(),"UTF-8"));
                        String line=null;
                        //StringBuilder stringBuilder=new StringBuilder();
                        while ((line=bufferedReader.readLine())!=null){
                            //stringBuilder.append(line);
                            mVoiceStr.append(line);
                            Message msg=new Message();
                            msg.what=0x124;
                            msg.obj=line;
                            handler.sendMessage(msg);
                        }
                        bufferedReader.close();
                        //String responseStr=stringBuilder.toString();


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

            String []voiceStr=getParsedVoiceStr();
            if(voiceStr.length!=0){
                Toast.makeText(MainActivity.this,
                        "voice content: "+voiceStr[0],
                        Toast.LENGTH_LONG).show();
            }

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

                        //urlConnection= (HttpsURLConnection) url.openConnection();
                        urlConnection= (HttpURLConnection) url.openConnection();
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
                        reader.close();
                        inputStream.close();

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
