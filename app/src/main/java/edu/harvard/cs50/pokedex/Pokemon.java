package edu.harvard.cs50.pokedex;

public class Pokemon {
    private String name;
    private String url;

    Pokemon(String name, String url)
    {
        this.url = url;
        this.name = name;
    }

    Pokemon(Pokemon other)
    {
        this.url = other.getUrl();
        this.name = other.getName();
    }

    public String getName()
    {
        return this.name;
    }
    public String getUrl()
    {
        return this.url;
    }

    public int compareTo(Pokemon other) {
        return this.name.compareTo(other.getName());
    }
}
