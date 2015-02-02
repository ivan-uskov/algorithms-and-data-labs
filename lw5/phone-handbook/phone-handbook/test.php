<?php

    $str = "";
	for ($i = 0; $i < 100; ++$i)
	{
		$str .= $i . " ololo" . $i . "\n";
	}
	file_put_contents("handbook", $str);