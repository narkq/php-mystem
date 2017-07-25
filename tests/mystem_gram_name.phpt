--TEST--
Check gram_name()
--SKIPIF--
<?php if (!extension_loaded("mystem")) print "skip"; ?>
--FILE--
<?php
var_dump(Mystem\gram_name(172));
var_dump(Mystem\gram_name(428));
var_dump(Mystem\gram_name(-84));
?>
--EXPECT--
string(8) "Locative"
string(7) "Invalid"
string(7) "Invalid"
