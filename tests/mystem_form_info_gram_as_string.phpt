--TEST--
Check form_info() with gram info as string
--SKIPIF--
<?php if (!extension_loaded("mystem")) print "skip"; ?>
--FILE--
<?php
var_dump(Mystem\form_info("креветка", true));
?>
--EXPECT--
array(1) {
  [0]=>
  array(7) {
    ["lemma"]=>
    string(16) "креветка"
    ["form"]=>
    string(16) "креветка"
    ["quality"]=>
    int(0)
    ["stem_gram"]=>
    array(2) {
      [0]=>
      string(11) "Substantive"
      [1]=>
      string(8) "Feminine"
    }
    ["flex_gram"]=>
    array(2) {
      [0]=>
      array(3) {
        [0]=>
        string(10) "Nominative"
        [1]=>
        string(8) "Singular"
        [2]=>
        string(8) "Animated"
      }
      [1]=>
      array(3) {
        [0]=>
        string(10) "Nominative"
        [1]=>
        string(8) "Singular"
        [2]=>
        string(10) "Inanimated"
      }
    }
    ["flex_len"]=>
    int(2)
    ["rule_id"]=>
    int(2179)
  }
}
