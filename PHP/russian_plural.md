# Russian Plural.

This is plural function for Russian words.

~~~php
/**
 * Plural function for Russian words.
 */
function russian_plural($number, $endingArray) {
  $number = abs($number) % 100;
  if ($number >= 11 && $number <= 19) {
    $ending = $endingArray[2];
  }
  else {
    $i = $number % 10;
    switch ($i) {
      case (0):
        $ending = $endingArray[2];
        break;
      case (1):
        $ending = $endingArray[0];
        break;
      case (2):
      case (3):
      case (4):
        $ending = $endingArray[1];
        break;
      default:
        $ending = $endingArray[2];
    }
  }
  return $ending;
}

~~~

## Example

~~~php
/**
 * @example
 */
$endings = [
  'яблоко',
  'яблока',
  'яблок',
];
print '1 ' . russian_plural(1, $endings); // 1 яблоко
print '2 ' . russian_plural(2, $endings); // 2 яблока
print '5 ' . russian_plural(5, $endings); // 5 яблок
~~~

