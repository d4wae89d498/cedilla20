<?php 

$i = 0;
while ($i <= 126)
{
    ?>

#define CPP_EACH_<?=$i?>(replacement<?php 
    $y = 1;
    while ($y <= $i)
    {
        echo ", A$y";
        if (!($y % 10))
            echo "\\" . PHP_EOL;
        $y += 1;
    }
    echo ")";
    if ($y !== 1)
        echo "\\" . PHP_EOL;
    $y = 1;
    while ($y <= $i)
    {
        echo "replacement(A$y) ";
        if (!($y % 3) && ($y != $i))
            echo "\\" . PHP_EOL;
        $y += 1;
    }
    $i += 1;
}