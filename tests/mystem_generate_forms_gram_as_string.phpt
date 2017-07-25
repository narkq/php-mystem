--TEST--
Check generate_forms() with gram info as string
--SKIPIF--
<?php if (!extension_loaded("mystem")) print "skip"; ?>
--FILE--
<?php
var_dump(Mystem\generate_forms("Пафнутий", true));
?>
--EXPECT--
array(1) {
  [0]=>
  array(8) {
    ["lemma"]=>
    string(16) "пафнутий"
    ["form"]=>
    string(16) "пафнутий"
    ["quality"]=>
    int(0)
    ["stem_gram"]=>
    array(4) {
      [0]=>
      string(11) "Substantive"
      [1]=>
      string(9) "FirstName"
      [2]=>
      string(9) "Masculine"
      [3]=>
      string(8) "Animated"
    }
    ["flex_gram"]=>
    array(1) {
      [0]=>
      array(2) {
        [0]=>
        string(10) "Nominative"
        [1]=>
        string(8) "Singular"
      }
    }
    ["flex_len"]=>
    int(1)
    ["rule_id"]=>
    int(19)
    ["form_list"]=>
    array(10) {
      [0]=>
      array(3) {
        ["form"]=>
        string(16) "пафнутие"
        ["stem_gram"]=>
        array(4) {
          [0]=>
          string(11) "Substantive"
          [1]=>
          string(9) "FirstName"
          [2]=>
          string(9) "Masculine"
          [3]=>
          string(8) "Animated"
        }
        ["flex_gram"]=>
        array(1) {
          [0]=>
          array(3) {
            [0]=>
            string(8) "Reserved"
            [1]=>
            string(8) "Ablative"
            [2]=>
            string(8) "Singular"
          }
        }
      }
      [1]=>
      array(3) {
        ["form"]=>
        string(18) "пафнутиев"
        ["stem_gram"]=>
        array(4) {
          [0]=>
          string(11) "Substantive"
          [1]=>
          string(9) "FirstName"
          [2]=>
          string(9) "Masculine"
          [3]=>
          string(8) "Animated"
        }
        ["flex_gram"]=>
        array(2) {
          [0]=>
          array(2) {
            [0]=>
            string(10) "Accusative"
            [1]=>
            string(6) "Plural"
          }
          [1]=>
          array(2) {
            [0]=>
            string(8) "Genitive"
            [1]=>
            string(6) "Plural"
          }
        }
      }
      [2]=>
      array(3) {
        ["form"]=>
        string(18) "пафнутием"
        ["stem_gram"]=>
        array(4) {
          [0]=>
          string(11) "Substantive"
          [1]=>
          string(9) "FirstName"
          [2]=>
          string(9) "Masculine"
          [3]=>
          string(8) "Animated"
        }
        ["flex_gram"]=>
        array(1) {
          [0]=>
          array(2) {
            [0]=>
            string(12) "Instrumental"
            [1]=>
            string(8) "Singular"
          }
        }
      }
      [3]=>
      array(3) {
        ["form"]=>
        string(16) "пафнутии"
        ["stem_gram"]=>
        array(4) {
          [0]=>
          string(11) "Substantive"
          [1]=>
          string(9) "FirstName"
          [2]=>
          string(9) "Masculine"
          [3]=>
          string(8) "Animated"
        }
        ["flex_gram"]=>
        array(2) {
          [0]=>
          array(2) {
            [0]=>
            string(8) "Ablative"
            [1]=>
            string(8) "Singular"
          }
          [1]=>
          array(2) {
            [0]=>
            string(10) "Nominative"
            [1]=>
            string(6) "Plural"
          }
        }
      }
      [4]=>
      array(3) {
        ["form"]=>
        string(16) "пафнутий"
        ["stem_gram"]=>
        array(4) {
          [0]=>
          string(11) "Substantive"
          [1]=>
          string(9) "FirstName"
          [2]=>
          string(9) "Masculine"
          [3]=>
          string(8) "Animated"
        }
        ["flex_gram"]=>
        array(1) {
          [0]=>
          array(2) {
            [0]=>
            string(10) "Nominative"
            [1]=>
            string(8) "Singular"
          }
        }
      }
      [5]=>
      array(3) {
        ["form"]=>
        string(16) "пафнутию"
        ["stem_gram"]=>
        array(4) {
          [0]=>
          string(11) "Substantive"
          [1]=>
          string(9) "FirstName"
          [2]=>
          string(9) "Masculine"
          [3]=>
          string(8) "Animated"
        }
        ["flex_gram"]=>
        array(1) {
          [0]=>
          array(2) {
            [0]=>
            string(6) "Dative"
            [1]=>
            string(8) "Singular"
          }
        }
      }
      [6]=>
      array(3) {
        ["form"]=>
        string(16) "пафнутия"
        ["stem_gram"]=>
        array(4) {
          [0]=>
          string(11) "Substantive"
          [1]=>
          string(9) "FirstName"
          [2]=>
          string(9) "Masculine"
          [3]=>
          string(8) "Animated"
        }
        ["flex_gram"]=>
        array(2) {
          [0]=>
          array(2) {
            [0]=>
            string(10) "Accusative"
            [1]=>
            string(8) "Singular"
          }
          [1]=>
          array(2) {
            [0]=>
            string(8) "Genitive"
            [1]=>
            string(8) "Singular"
          }
        }
      }
      [7]=>
      array(3) {
        ["form"]=>
        string(18) "пафнутиям"
        ["stem_gram"]=>
        array(4) {
          [0]=>
          string(11) "Substantive"
          [1]=>
          string(9) "FirstName"
          [2]=>
          string(9) "Masculine"
          [3]=>
          string(8) "Animated"
        }
        ["flex_gram"]=>
        array(1) {
          [0]=>
          array(2) {
            [0]=>
            string(6) "Dative"
            [1]=>
            string(6) "Plural"
          }
        }
      }
      [8]=>
      array(3) {
        ["form"]=>
        string(20) "пафнутиями"
        ["stem_gram"]=>
        array(4) {
          [0]=>
          string(11) "Substantive"
          [1]=>
          string(9) "FirstName"
          [2]=>
          string(9) "Masculine"
          [3]=>
          string(8) "Animated"
        }
        ["flex_gram"]=>
        array(1) {
          [0]=>
          array(2) {
            [0]=>
            string(12) "Instrumental"
            [1]=>
            string(6) "Plural"
          }
        }
      }
      [9]=>
      array(3) {
        ["form"]=>
        string(18) "пафнутиях"
        ["stem_gram"]=>
        array(4) {
          [0]=>
          string(11) "Substantive"
          [1]=>
          string(9) "FirstName"
          [2]=>
          string(9) "Masculine"
          [3]=>
          string(8) "Animated"
        }
        ["flex_gram"]=>
        array(1) {
          [0]=>
          array(2) {
            [0]=>
            string(8) "Ablative"
            [1]=>
            string(6) "Plural"
          }
        }
      }
    }
  }
}
