package com.example.bdsr_restful;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;


public class MainActivity extends Activity {
	private static final String apiKey="YGyI3APWnLGSiIFUWEnhBEoC";
	private static final String secretKey="fc4d81ef45486b17da48d6d2e81b65d5";
	TextView txtViewResponse;
	Button btnAccess;
	HttpClient httpClient;
	
	Handler handler=new Handler(){
		public void handleMessage(android.os.Message msg) {
			if (msg.what==0x123) {
				txtViewResponse.append(msg.obj.toString()+"\n");
			}
		};
	};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        httpClient=new DefaultHttpClient();
        
        txtViewResponse=(TextView) findViewById(R.id.txtView_response);
        btnAccess=(Button) findViewById(R.id.btn_access);
        btnAccess.setOnClickListener(new BtnAccessListener());
        
        
    }
    class BtnAccessListener implements OnClickListener{
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			txtViewResponse.setText("");
			new Thread(){
				public void run() {
					HttpPost post=new HttpPost("https://openapi.baidu.com/oauth/2.0/token?grant_type=client_credentials&client_id="+apiKey+"&client_secret="+secretKey);
					try {
						HttpResponse serverResponse= httpClient.execute(post);
						HttpEntity entity = serverResponse.getEntity();
						if (entity != null)
						{
							// 读取服务器响应
							BufferedReader br = new BufferedReader(
								new InputStreamReader(entity.getContent()));
							String line = null;
							
							while ((line = br.readLine()) != null)
							{
								Message msg = new Message();
								msg.what = 0x123;
								msg.obj = line;
								handler.sendMessage(msg);
							}
						}
						//String msg=EntityUtils.toString(serverResponse.getEntity());
						//Toast.makeText(MainActivity.this, msg, Toast.LENGTH_LONG).show();
					} catch (ClientProtocolException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
				};
			}.start();
		}
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
