--TEST--
Check form_info()
--SKIPIF--
<?php if (!extension_loaded("mystem")) print "skip"; ?>
--FILE--
<?php
var_dump(Mystem\form_info("банке"));
?>
--EXPECT--
array(2) {
  [0]=>
  array(7) {
    ["lemma"]=>
    string(8) "банк"
    ["form"]=>
    string(10) "банке"
    ["quality"]=>
    int(0)
    ["stem_gram"]=>
    array(3) {
      [0]=>
      int(136)
      [1]=>
      int(192)
      [2]=>
      int(202)
    }
    ["flex_gram"]=>
    array(1) {
      [0]=>
      array(2) {
        [0]=>
        int(170)
        [1]=>
        int(174)
      }
    }
    ["flex_len"]=>
    int(1)
    ["rule_id"]=>
    int(30)
  }
  [1]=>
  array(7) {
    ["lemma"]=>
    string(10) "банка"
    ["form"]=>
    string(10) "банке"
    ["quality"]=>
    int(0)
    ["stem_gram"]=>
    array(3) {
      [0]=>
      int(136)
      [1]=>
      int(191)
      [2]=>
      int(202)
    }
    ["flex_gram"]=>
    array(2) {
      [0]=>
      array(2) {
        [0]=>
        int(170)
        [1]=>
        int(174)
      }
      [1]=>
      array(2) {
        [0]=>
        int(167)
        [1]=>
        int(174)
      }
    }
    ["flex_len"]=>
    int(2)
    ["rule_id"]=>
    int(69)
  }
}
