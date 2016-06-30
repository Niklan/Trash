# Drupal Commerce - how to hide decimals in price

F.e. you have 12 345,00 руб, after this, you will have 12 345 руб. This method is not require to update prices on site, not used in calculating, if decimals exist, they will go to order total, this is just visual fix.

~~~php
/**
 * hook_commerce_currency_info_alter
 */
function MODULENAME_commerce_currency_info_alter(&$currencies){
  // Don't forget to change RUB to your currency in ISO 4217 format as 
  // drupal commerce do it. https://ru.wikipedia.org/wiki/ISO_4217
  $currencies['RUB']['format_callback'] = 'MODULENAME_commerce_currency_format';
}

/**
 * Currency format callback
 */
function MODULENAME_commerce_currency_format($amount, $currency, $object = NULL, $convert = TRUE) {
  $price = number_format(commerce_currency_round(abs($amount), $currency), 0, $currency['decimal_separator'], $currency['thousands_separator']);
  
  $replacements = array(
    '@code_before' => $currency['code_placement'] == 'before' ? $currency['code'] : '',
    '@symbol_before' => $currency['symbol_placement'] == 'before' ? $currency['symbol'] : '',
    '@price' => $price,
    '@symbol_after' => $currency['symbol_placement'] == 'after' ? $currency['symbol'] : '',
    '@code_after' => $currency['code_placement'] == 'after' ? $currency['code'] : '',
    '@negative' => $amount < 0 ? '-' : '',
    '@symbol_spacer' => $currency['symbol_spacer'],
    '@code_spacer' => $currency['code_spacer'],
  );

  return trim(t('@code_before@code_spacer@negative@symbol_before@price@symbol_spacer@symbol_after@code_spacer@code_after', $replacements));
}
~~~
