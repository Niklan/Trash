This is example of how to move or rename Drupal 7 field.

For example we need rename `field_image` to `field_photo`.

## Make backup

Just do it, srsly.

## Drush clone

```
drush field-clone field_image field_photo
```

## Move data from another

```
INSERT field_data_field_photo SELECT * FROM field_data_field_image; 
INSERT field_revision_field_photo SELECT * FROM field_revision_field_image; 
```

## Test it

Test it, and if it's o'kay, just remove old field.