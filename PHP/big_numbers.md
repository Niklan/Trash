# Big numbers formatter

This function makes ease to format big numbers.

~~~php
/**
 * Shortiner for big numbers. Translate numbers like 1000 to 1k, 1 000 000 to 1M.
 */
function format_big_number($number) {
  $tokens = array(
    1000000 => 'M',
    1000 => 'K',
    1 => ''
  );

  foreach ($tokens as $unit => $text) {
    if ($number < $unit) {
      continue;
    }
    return floatval(number_format($number / $unit, 1)) . $text;
  }
}
~~~


# Example
~~~php
echo format_big_number(100); // 100
echo format_big_number(1000); // 1K
echo format_big_number(20500); // 20.5K
echo format_big_number(1500000); // 1.5M
~~~
