package com.paker.androidchatclient;

import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.util.ArrayList;

/**
 * Created by paker on 11/04/15.
 */
public class ChatFragment extends Fragment {

    View rootView;
    TextView textView;
    EditText editText;
    Button enviar;
    String history = "";

    public native void conectar();

    public native boolean sendMsg(String nick, String str);

    public ChatFragment() {
        System.loadLibrary("ChatClient");
    }

    public void onConnect() {
        getActivity().runOnUiThread(new Runnable() {
            public void run() {
                String str = "Conectado!\n";
                textView.append(str);
                history += str;
            }
        });
    }

    public void onDisconnect() {
        getActivity().runOnUiThread(new Runnable() {
            public void run() {
                String str = "Desonectado!\n";
                textView.append(str);
                history += str;
            }
        });
    }

    public void recvMsg(final String _str) {
        getActivity().runOnUiThread(new Runnable() {
            public void run() {
                String str = _str + "\n";
                textView.append(str);
                history += str;
            }
        });
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setRetainInstance(true);

        conectar();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        if (savedInstanceState == null) {
            rootView = inflater.inflate(R.layout.fragment_chat, container, false);
            textView = (TextView) rootView.findViewById(R.id.textView);
            editText = (EditText) rootView.findViewById(R.id.editText);
            enviar = (Button) rootView.findViewById(R.id.enviar);

            enviar.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    String str = editText.getText().toString();
                    editText.setText("");
                    Log.i("sendMsg", sendMsg("Coala", str) + ": \"" + str + "\"");
                }
            });

            final FragmentActivity activity = getActivity();
            textView.setOnTouchListener(new View.OnTouchListener() {
                @Override
                public boolean onTouch(View v, MotionEvent event) {
                    InputMethodManager imm = (InputMethodManager) activity.getSystemService(
                            Context.INPUT_METHOD_SERVICE);
                    imm.hideSoftInputFromWindow(editText.getWindowToken(), 0);
                    return true;
                }
            });
        }
        return rootView;
    }
}