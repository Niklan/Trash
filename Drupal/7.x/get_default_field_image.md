# Getting default image for image field.

~~~php
$info = field_info_instance('ENTITY_TYPE', 'FIELD_NAME', 'BUNDLE');
if (!empty($info) && $info['settings']['default_image'] > 0) {
  $default_fid = $info['settings']['default_image'];
  $default_file = file_load($default_fid);
  // $default_file->uri
}
~~~

