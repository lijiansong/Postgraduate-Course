package cn.ac.ict.audiotest;

import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.ImageButton;
import android.widget.Toast;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class MainActivity extends AppCompatActivity
        implements View.OnClickListener {

    ImageButton mBtnRecord;
    ImageButton mBtnStop;

    //MediaRecorder mMediaRecorder;
    AudioRecord mAudioRecord;
    boolean isRecording=false;
    Thread recordingThread;

    private static final int RECORDER_SOURCE= MediaRecorder.AudioSource.MIC;
    private static final int RECORDER_SAMPLERATE=8000;
    private static final int RECORDER_CHANNELS=AudioFormat.CHANNEL_IN_MONO;
    private static final int RECORDER_AUDIO_ENCODING= AudioFormat.ENCODING_PCM_16BIT;

    // want to play 2048 (2K) since 2 bytes we use only 1024
    private int BufferElements2Rec = 1024;
    // 2 bytes in 16bit format
    private int BytesPerElement = 2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mBtnRecord= (ImageButton) findViewById(R.id.record);
        mBtnStop= (ImageButton) findViewById(R.id.stop);

        mBtnRecord.setOnClickListener(this);
        mBtnStop.setOnClickListener(this);

        //mAudioRecord.startRecording();
    }

//    int bufferSizeInBytes=AudioRecord.getMinBufferSize(
//            RECORDER_SAMPLERATE,
//            RECORDER_CHANNELS,
//            RECORDER_AUDIO_ENCODING
//    );
//    byte mData[]=new byte[bufferSizeInBytes];

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
                String filePath=Environment.getExternalStorageDirectory().getPath();
                short data[]=new short[BufferElements2Rec];

                FileOutputStream fileOutputStream=null;
                try {
                    fileOutputStream=new FileOutputStream(filePath+"/8k16bitMono.pcm");

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
                Toast.makeText(MainActivity.this,"audio file have been writen to: "+Environment.getExternalStorageDirectory().getPath(),Toast.LENGTH_LONG).show();
                break;
        }
    }
}
