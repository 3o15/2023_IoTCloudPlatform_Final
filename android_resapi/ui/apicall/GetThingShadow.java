package com.example.android_resapi.ui.apicall;

import android.app.Activity;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;
import org.json.JSONException;
import org.json.JSONObject;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.HashMap;
import java.util.Map;

import com.example.android_resapi.R;
import com.example.android_resapi.httpconnection.GetRequest;

public class GetThingShadow extends GetRequest {
    final static String TAG = "AndroidAPITest";
    String urlStr;
    public GetThingShadow(Activity activity, String urlStr) {
        super(activity);
        this.urlStr = urlStr;
    }

    @Override
    protected void onPreExecute() {
        try {
            Log.e(TAG, urlStr);
            url = new URL(urlStr);

        } catch (MalformedURLException e) {
            Toast.makeText(activity,"URL is invalid:"+urlStr, Toast.LENGTH_SHORT).show();
            e.printStackTrace();
            activity.finish();
        }
    }

    @Override
    protected void onPostExecute(String jsonString) {
        if (jsonString == null)
            return;
        Map<String, String> state = getStateFromJSONString(jsonString);
        TextView reported_weightTV = activity.findViewById(R.id.reported_weight);
        TextView reported_sentence1TV = activity.findViewById(R.id.reported_sentence1);
        TextView reported_airTV = activity.findViewById(R.id.reported_air);
        TextView reported_ledTV = activity.findViewById(R.id.reported_led);
        reported_weightTV.setText(state.get("reported_weight"));
        reported_sentence1TV.setText(state.get("reported_msg1"));
        reported_airTV.setText(state.get("reported_air"));
        reported_ledTV.setText(state.get("reported_LED"));

        TextView desired_weightTV = activity.findViewById(R.id.desired_weight);
        TextView desired_sentence1TV = activity.findViewById(R.id.desired_sentence1);
        TextView desired_airTV = activity.findViewById(R.id.desired_air);
        TextView desired_ledTV = activity.findViewById(R.id.desired_led);
        desired_weightTV.setText(state.get("desired_weight"));
        desired_sentence1TV.setText(state.get("desired_msg1"));
        desired_airTV.setText(state.get("desired_air"));
        desired_ledTV.setText(state.get("desired_LED"));
    }

    protected Map<String, String> getStateFromJSONString(String jsonString) {
        Map<String, String> output = new HashMap<>();
        try {
            // 처음 double-quote와 마지막 double-quote 제거
            jsonString = jsonString.substring(1,jsonString.length()-1);
            // \\\" 를 \"로 치환
            jsonString = jsonString.replace("\\\"","\"");
            Log.i(TAG, "jsonString="+jsonString);
            JSONObject root = new JSONObject(jsonString);
            JSONObject state = root.getJSONObject("state");
            JSONObject reported = state.getJSONObject("reported");
            String ledValue = reported.getString("LED");
            String weightValue = reported.getString("weight");
            String airValue = reported.getString("air");
            String msg1Value = reported.getString("msg1");
            output.put("reported_LED",ledValue);
            output.put("reported_weight", weightValue);
            output.put("reported_air", airValue);
            output.put("reported_msg1",msg1Value);

            JSONObject desired = state.getJSONObject("desired");
            String desired_ledValue = desired.getString("LED");
            String desired_airValue = desired.getString("ToiletPad");
            String desired_weightValue = desired.getString("Weight");
            String desired_msg1Value = desired.getString("msg1");
            output.put("desired_LED",desired_ledValue);
            output.put("desired_air", desired_airValue);
            output.put("desired_weightValue", desired_weightValue);
            output.put("desired_msg1",desired_msg1Value);

        } catch (JSONException e) {
            Log.e(TAG, "Exception in processing JSONString.", e);
            e.printStackTrace();
        }
        return output;
    }
}
