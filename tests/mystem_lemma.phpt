--TEST--
Check lemma()
--SKIPIF--
<?php if (!extension_loaded("mystem")) print "skip"; ?>
--FILE--
<?php
var_dump(Mystem\lemma("скорбящий"));
?>
--EXPECT--
array(1) {
  [0]=>
  string(16) "скорбеть"
}
