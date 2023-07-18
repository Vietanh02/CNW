# Generated by Django 3.1.4 on 2021-01-06 08:14

import autoslug.fields
import ckeditor.fields
from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('posts', '0036_auto_20210106_1334'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='tcforblog',
            name='blog',
        ),
        migrations.CreateModel(
            name='blank_page',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(max_length=70)),
                ('meta_tags', models.CharField(blank=True, max_length=2000)),
                ('meta_desc', models.TextField(blank=True, max_length=2000)),
                ('slug', autoslug.fields.AutoSlugField(editable=True, populate_from='title', unique=True)),
                ('image', models.ImageField(upload_to='media/blog')),
                ('image_alt_name', models.CharField(blank=True, max_length=200)),
                ('desc', ckeditor.fields.RichTextField(blank=True, null=True)),
                ('author', models.CharField(default='admin', max_length=20)),
                ('date', models.DateTimeField(auto_now_add=True)),
                ('hit', models.PositiveIntegerField(default=0)),
                ('category', models.ForeignKey(default=1, on_delete=django.db.models.deletion.CASCADE, related_name='blank', to='posts.category')),
            ],
        ),
        migrations.AddField(
            model_name='tcforblog',
            name='blank_page',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, related_name='tc_blank_page', to='posts.blank_page'),
        ),
    ]
