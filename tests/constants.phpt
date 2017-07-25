--TEST--
Check constants
--SKIPIF--
<?php if (!extension_loaded("mystem")) print "skip"; ?>
--FILE--
<?php
var_dump(Mystem\GramInfo\Before);
?>
--EXPECT--
int(126)
