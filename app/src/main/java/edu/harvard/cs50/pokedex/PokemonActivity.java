package edu.harvard.cs50.pokedex;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.SystemClock;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonArrayRequest;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.net.URL;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;

public class PokemonActivity extends AppCompatActivity {
    private TextView nameTextView;
    private TextView numberTextView;
    private TextView type1TextView;
    private TextView type2TextView;
    private String url;
    private RequestQueue requestQueue;
    protected ImageView imageView;
    protected Button button;
    private Boolean caught = false;
    private TextView catch_state;
    private SharedPreferences sharedPreferences;
    private TextView description;
    private String desc_url = "";
    public static int id_poke=0;
    private TextView ability1;
    private TextView ability2;
    private TextView weight;
    private int ChangedWeight;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pokemon);
        sharedPreferences = getPreferences(Context.MODE_PRIVATE);
        url = getIntent().getStringExtra("url");
        requestQueue = Volley.newRequestQueue(getApplicationContext());
        nameTextView = findViewById(R.id.pokemon_name);
        numberTextView = findViewById(R.id.pokemon_number);
        type1TextView = findViewById(R.id.pokemon_type1);
        type2TextView = findViewById(R.id.pokemon_type2);
        imageView = findViewById(R.id.image_poke);
        button = findViewById(R.id.button_catch);
        catch_state = findViewById(R.id.catch_state);
        description = findViewById(R.id.description);
        ability1 = findViewById(R.id.ability1);
        ability2 = findViewById(R.id.ability2);
        weight = findViewById(R.id.weight);

        load();
    }
    public void toggleCatch(View view) {
        SharedPreferences.Editor editor = sharedPreferences.edit();
        if(!this.caught)
        {
            this.caught = true;
            this.button.setText("Realese");
            this.catch_state.setText("Catched!");
        }
        else
        {
            this.caught = false;
            this.button.setText("Catch");
            this.catch_state.setText("Not Catched!");
        }
        editor.clear();
        editor.putBoolean(this.nameTextView.getText().toString(),caught).apply();
        //Log.d("CS500","Caught is now " + this.caught);
        //Log.d("CS500",""+sharedPreferences.getBoolean(this.nameTextView.getText().toString(),false));


    }
    public Boolean getCaught()
    {
        return this.caught;
    }
    public void load()
    {
        Log.d("CS500","ON LOAD");
        type1TextView.setText("");
        type2TextView.setText("");

        final JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                try {
                    Log.d("CS500","HERE");
                    id_poke = response.getInt("id");
                    desc_url = "https://pokeapi.co/api/v2/pokemon-species/" + id_poke + "/";
                    Log.d("CS500","Final url is : " + desc_url);
                    final JsonObjectRequest requestDesc = new JsonObjectRequest(Request.Method.GET, desc_url, null, new Response.Listener<JSONObject>() {
                        @Override
                        public void onResponse(JSONObject response) {
                            try {
                                Log.d("CS500","response is " + response.toString());
                                JSONArray flavorText = response.getJSONArray("flavor_text_entries");
                                for (int i = 0; i < flavorText.length(); i++) {

                                    JSONObject descriptionJ = flavorText.getJSONObject(i);

                                    String lang = descriptionJ.getJSONObject("language").getString("name");

                                    if(lang.equals("en")){
                                        String text = descriptionJ.getString("flavor_text");
                                        description.setText(text);
                                        break;
                                    }

                                }



                            } catch (JSONException e) {
                                Log.e("CS500", "pokemon json Error", e);
                            }


                        }
                    }, new Response.ErrorListener() {
                        @Override
                        public void onErrorResponse(VolleyError error) {
                            Log.e("CS500","FlavorText List Error");
                        }
                    });

                    requestQueue.add(requestDesc);

                    nameTextView.setText(response.getString("name"));
                    numberTextView.setText(String.format("#%03d",response.getInt("id")));
                    JSONArray abilities = response.getJSONArray("abilities");
                    String ab1 = "";
                    String ab2 = "";


                    JSONObject ab11 = abilities.getJSONObject(0).getJSONObject("ability");
                    JSONObject ab21 = abilities.getJSONObject(1).getJSONObject("ability");
                    Log.d("CS500","ab11 is: " +ab11);
                    Log.d("CS500","ab21 is: " +ab21);
                    ab1 = ab11.getString("name");
                    ab2 = ab21.getString("name");
                    ability1.setText("#1: " + ab1);
                    ability2.setText("#2: " + ab2);



                    Log.d("CS500","ID is: " + id_poke);
                    String image_url = response.getJSONObject("sprites").getJSONObject("other").getJSONObject("official-artwork").getString("front_default");
                    Log.d("CS500","Url for iamge is " + image_url);
                    new DownloadSpriteTask().execute(image_url);
                    JSONArray typeEntries = response.getJSONArray("types");
                    for(int i = 0 ; i < typeEntries.length() ; i++)
                    {
                        JSONObject typeEntry = typeEntries.getJSONObject(i);
                        int slot = typeEntry.getInt("slot");
                        String type = typeEntry.getJSONObject("type").getString("name");
                        if (slot == 1)
                        {
                            type1TextView.setText(type);
                        }
                        else if (slot == 2)
                        {
                            type2TextView.setText(type);
                        }
                    }

                    caught = sharedPreferences.getBoolean(response.getString("name"),false);
                    if (caught)
                    {
                        caught = true;
                        button.setText("Realese");
                        catch_state.setText("Catched!");
                    }
                    else
                    {
                        caught = false;
                        button.setText("Catch");
                        catch_state.setText("Not Catched!");
                    }
                    ChangedWeight = sharedPreferences.getInt(response.getString("name")+"w",-1);
                    if (ChangedWeight != -1)
                    {
                        weight.setText("Weight: " + ChangedWeight);
                    }
                    else{
                        weight.setText("Weight: " + response.getString("weight"));
                    }



                }
                catch (JSONException e) {
                    Log.e("CS500", "pokemon json Error", e);
                }




            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("CS500","Pokemon details Error");
            }
        });

        requestQueue.add(request);

    }


    public void feed(View view)
    {
        SharedPreferences.Editor editor = sharedPreferences.edit();
        int currWeight = Integer.parseInt(weight.getText().toString().substring(7).trim());
        if(currWeight <= 950)
        {
            currWeight += 50;
        }
        else
        {
            currWeight = 1000;
        }
        String text = String.format("Weight: %d",currWeight);
        editor.clear();
        editor.putInt(this.nameTextView.getText().toString()+"w",currWeight).apply();
        weight.setText(text);
    }

    public void starve(View view)
    {
        SharedPreferences.Editor editor = sharedPreferences.edit();
        int currWeight = Integer.parseInt(weight.getText().toString().substring(7).trim());
        if(currWeight >= 50)
        {
            currWeight -= 50;
        }
        else
        {
            currWeight = 0;
        }

        String text = String.format("Weight: %d",currWeight);
        editor.clear();
        editor.putInt(this.nameTextView.getText().toString()+"w",currWeight).apply();
        weight.setText(text);

    }






    private class DownloadSpriteTask extends AsyncTask<String, Void, Bitmap> {

        @Override
        protected Bitmap doInBackground(String... strings) {
            try {
                URL url = new URL(strings[0]);
                Log.d("CS500","finished loading Bitmap");
                return BitmapFactory.decodeStream(url.openStream());
            }
            catch ( IOException e) {
                Log.e("cs50", "Download sprite error", e);
                return null;
            }
        }

        @Override
        protected void onPostExecute(Bitmap bitmap) {
            imageView.setImageBitmap(bitmap);

        }
    }
}