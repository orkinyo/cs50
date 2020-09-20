package edu.harvard.cs50.pokedex;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Filter;
import android.widget.Filterable;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class PokedexAdapter extends RecyclerView.Adapter<PokedexAdapter.PokedexViewHolder> implements Filterable {

    public static class PokedexViewHolder extends RecyclerView.ViewHolder {
        public LinearLayout containerView;
        public TextView textView;

        PokedexViewHolder(View view) {
            super(view);
            this.containerView = view.findViewById(R.id.pokedex_row);
            this.textView = view.findViewById(R.id.pokedex_row_text_view);

            containerView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    Pokemon current = (Pokemon) containerView.getTag();
                    Intent intent = new Intent(v.getContext(), PokemonActivity.class);
                    //intent.putExtra("number",current.getNumber());
                    intent.putExtra("url",current.getUrl());
                    v.getContext().startActivity(intent);

                }
            });

        }
    }





    protected List<Pokemon> pokemon = new ArrayList<>();
    protected List<Pokemon> filtered = new ArrayList<>();
    private RequestQueue requestQueue;

    PokedexAdapter(Context context)
    {
        requestQueue = Volley.newRequestQueue(context);
        Log.d("CS500","creating adapter");
        loadPokemon();
    }

    @Override
    public Filter getFilter() {
        return new PokemonFilter();
    }

    public void loadPokemon()
    {
        Log.d("cs50ADAPTER","started loading");
        String url = "https://pokeapi.co/api/v2/pokemon?limit=1050";
        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                try {
                    JSONArray results = response.getJSONArray("results");
                        for (int i = 0;  i < results.length() ; i++)
                        {
                            JSONObject result = results.getJSONObject(i);
                            pokemon.add(new Pokemon(result.getString("name").substring(0,1).toUpperCase()+result.getString("name").substring(1),result.getString("url")));
                            filtered.add(new Pokemon(result.getString("name").substring(0,1).toUpperCase()+result.getString("name").substring(1),result.getString("url")));
                        }
                        notifyDataSetChanged();
                } catch (JSONException e) {
                    Log.e("cs50", "Json Error", e);
                }


            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("cs50","Pokemon List Error");
            }
        });

        requestQueue.add(request);
        Log.d("cs500","finished loading pokemon");
    }


    @NonNull
    @Override
    public PokedexViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.pokedex_row,parent,false);
        return new PokedexViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull PokedexViewHolder holder, int position) {
        Pokemon current = filtered.get(position);
        holder.textView.setText(current.getName());
        holder.containerView.setTag(current);

    }

    @Override
    public int getItemCount() {
            return filtered.size();
    }

    private class PokemonFilter extends Filter {
    @Override
    protected FilterResults performFiltering(CharSequence constraint) {
        List<Pokemon> filteredPokemon  = new ArrayList<>();
        FilterResults results = new FilterResults();
        if ((constraint == null) || (constraint.length() == 0)) {

            Log.d("CS500","entered all pokemons for some reason");
            filteredPokemon.addAll(pokemon);
        }
        else{
            for(Pokemon name : pokemon)
            {
                if (name.getName().toLowerCase().trim().startsWith(constraint.toString().toLowerCase().trim()))
                {
                    filteredPokemon.add(name);


                }
            }

            Log.d("CS500","Didnt enter all pokemons");

        }

        Log.d("CS500","finished filtering");
        results.values = filteredPokemon;
        results.count = filteredPokemon.size();
        Log.d("CS500",String.format("New len of pokemons: %d",results.count));
        return results;

    }
        @Override
        protected void publishResults(CharSequence constraint, FilterResults results) {
            filtered = (List<Pokemon>) results.values;
            //Log.d("CS500",String.format("Checking on filtered itself, len : %d",filtered.size()));
            notifyDataSetChanged();
        }
    }
}
