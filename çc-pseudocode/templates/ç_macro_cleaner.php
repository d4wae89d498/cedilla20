<?php

const macro_prefix = "cedilla_macro_";

$i = 0;
while ($i < 42000)
{
    echo "#undef " . macro_prefix . $i . PHP_EOL;
    $i += 1;
}