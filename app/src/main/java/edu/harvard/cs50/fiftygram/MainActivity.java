package edu.harvard.cs50.fiftygram;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.os.ParcelFileDescriptor;
import android.provider.MediaStore;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;

import com.bumptech.glide.Glide;
import com.bumptech.glide.load.Transformation;
import com.bumptech.glide.request.RequestOptions;

import java.io.FileDescriptor;
import java.io.FileNotFoundException;
import java.io.IOException;

import jp.wasabeef.glide.transformations.gpu.*;

public class MainActivity extends AppCompatActivity implements ActivityCompat.OnRequestPermissionsResultCallback {
    private ImageView imageView;
    private Bitmap image;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        imageView = findViewById(R.id.image_view);
        requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 1);
    }

    public void choosePhoto(View view) {
        Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        intent.setType("image/*");
        startActivityForResult(intent, 1);

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (resultCode == Activity.RESULT_OK && data != null)
        {
            Uri uri = data.getData();
            try {
                ParcelFileDescriptor file = getContentResolver().openFileDescriptor(uri, "r");
                FileDescriptor fileDescriptor = file.getFileDescriptor();
                image = BitmapFactory.decodeFileDescriptor(fileDescriptor);
                file.close();
                imageView.setImageBitmap(image);

            }

            catch (IOException e)
            {
                Log.e("CS500","Error opening file",e);
            }

        }
    }

    public void apply(Transformation<Bitmap> filter)
    {
        Glide.with
                (this).
                load(image).
                apply(RequestOptions.bitmapTransform(filter)).into(imageView);
    }

    public void applySepia(View view)
    {
        apply(new SepiaFilterTransformation());
    }

    public void applySketch(View view)
    {
        apply(new SketchFilterTransformation());
    }

    public void applyPixelation(View view)
    {
        apply(new PixelationFilterTransformation());
    }

    public void applyToon(View view)
    {
        apply(new ToonFilterTransformation());
    }

    public void saveImage(View view)
    {
        Bitmap temp = ((BitmapDrawable) imageView.getDrawable()).getBitmap();
        MediaStore.Images.Media.insertImage(getContentResolver(),temp,"Filter","Image of filter");
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }


}