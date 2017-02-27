package cn.ac.ict.restful;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;

import javax.net.ssl.HttpsURLConnection;

public class MainActivity extends AppCompatActivity {

    private static final String API_KEY="YGyI3APWnLGSiIFUWEnhBEoC";
    private static final String SECRET_KEY="fc4d81ef45486b17da48d6d2e81b65d5";
    TextView mTextViewResponse=null;
    Button mBtnAccess=null;
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

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //mHttpClient=new DefaultHttpClient();

        mTextViewResponse= (TextView) findViewById(R.id.txtview_response);
        mBtnAccess= (Button) findViewById(R.id.btn_access);
        mBtnAccess.setOnClickListener(new BtnAccessListener());
    }
    class BtnAccessListener implements View.OnClickListener{
        @Override
        public void onClick(View v) {
            mTextViewResponse.setText("");
            new Thread(){
                public void run(){
//                    HttpPost post=new HttpPost("https://openapi.baidu.com/oauth/2.0/token?grant_type=client_credentials&client_id="
//                            +API_KEY+"&client_secret="+SECRET_KEY);
//                    try {
//                        HttpResponse serverResponse=mHttpClient.execute(post);
//                        HttpEntity entity=serverResponse.getEntity();
//                        if (entity!=null){
//                            //get server response
//                            BufferedReader bufferedReader=new BufferedReader(
//                                    new InputStreamReader(entity.getContent())
//                            );
//                            String line=null;
//                            while((line=bufferedReader.readLine())!=null)
//                            {
//                                Message msg=new Message();
//                                msg.what=0x123;
//                                msg.obj=line;
//                                handler.sendMessage(msg);
//                            }
//                        }
//
//                    } catch (IOException e) {
//                        e.printStackTrace();
//                    }

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
                            //mTextViewResponse.setText("Error!\nFailed to connect to Baidu server!\n\n");
                        }
                        InputStream inputStream=new BufferedInputStream(urlConnection.getInputStream());

                        BufferedReader reader=new BufferedReader(new InputStreamReader(inputStream));
                        StringBuilder responseText=new StringBuilder();
                        String line=null;
                        while ((line=reader.readLine())!=null){
                            responseText.append(line).append('\n');
                            Message msg=new Message();
                            msg.what=0x123;
                            msg.obj=line;
                            handler.sendMessage(msg);
                        }
                        //mTextViewResponse.setText(responseText.toString());

                    } catch (MalformedURLException e) {
                        e.printStackTrace();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }.start();
        }
    }
}
