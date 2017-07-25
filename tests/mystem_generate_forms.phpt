--TEST--
Check generate_forms()
--SKIPIF--
<?php if (!extension_loaded("mystem")) print "skip"; ?>
--FILE--
<?php
var_dump(Mystem\generate_forms("банке"));
?>
--EXPECT--
array(2) {
  [0]=>
  array(8) {
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
    ["form_list"]=>
    array(10) {
      [0]=>
      array(3) {
        ["form"]=>
        string(8) "банк"
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
        array(2) {
          [0]=>
          array(2) {
            [0]=>
            int(168)
            [1]=>
            int(174)
          }
          [1]=>
          array(2) {
            [0]=>
            int(165)
            [1]=>
            int(174)
          }
        }
      }
      [1]=>
      array(3) {
        ["form"]=>
        string(10) "банка"
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
            int(166)
            [1]=>
            int(174)
          }
        }
      }
      [2]=>
      array(3) {
        ["form"]=>
        string(12) "банкам"
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
            int(167)
            [1]=>
            int(175)
          }
        }
      }
      [3]=>
      array(3) {
        ["form"]=>
        string(14) "банками"
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
            int(169)
            [1]=>
            int(175)
          }
        }
      }
      [4]=>
      array(3) {
        ["form"]=>
        string(12) "банках"
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
            int(175)
          }
        }
      }
      [5]=>
      array(3) {
        ["form"]=>
        string(10) "банке"
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
      }
      [6]=>
      array(3) {
        ["form"]=>
        string(10) "банки"
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
        array(2) {
          [0]=>
          array(2) {
            [0]=>
            int(168)
            [1]=>
            int(175)
          }
          [1]=>
          array(2) {
            [0]=>
            int(165)
            [1]=>
            int(175)
          }
        }
      }
      [7]=>
      array(3) {
        ["form"]=>
        string(12) "банков"
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
            int(166)
            [1]=>
            int(175)
          }
        }
      }
      [8]=>
      array(3) {
        ["form"]=>
        string(12) "банком"
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
            int(169)
            [1]=>
            int(174)
          }
        }
      }
      [9]=>
      array(3) {
        ["form"]=>
        string(10) "банку"
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
            int(167)
            [1]=>
            int(174)
          }
        }
      }
    }
  }
  [1]=>
  array(8) {
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
    ["form_list"]=>
    array(10) {
      [0]=>
      array(3) {
        ["form"]=>
        string(10) "банка"
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
        array(1) {
          [0]=>
          array(2) {
            [0]=>
            int(165)
            [1]=>
            int(174)
          }
        }
      }
      [1]=>
      array(3) {
        ["form"]=>
        string(12) "банкам"
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
        array(1) {
          [0]=>
          array(2) {
            [0]=>
            int(167)
            [1]=>
            int(175)
          }
        }
      }
      [2]=>
      array(3) {
        ["form"]=>
        string(14) "банками"
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
        array(1) {
          [0]=>
          array(2) {
            [0]=>
            int(169)
            [1]=>
            int(175)
          }
        }
      }
      [3]=>
      array(3) {
        ["form"]=>
        string(12) "банках"
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
        array(1) {
          [0]=>
          array(2) {
            [0]=>
            int(170)
            [1]=>
            int(175)
          }
        }
      }
      [4]=>
      array(3) {
        ["form"]=>
        string(10) "банке"
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
      }
      [5]=>
      array(3) {
        ["form"]=>
        string(10) "банки"
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
        array(3) {
          [0]=>
          array(2) {
            [0]=>
            int(168)
            [1]=>
            int(175)
          }
          [1]=>
          array(2) {
            [0]=>
            int(166)
            [1]=>
            int(174)
          }
          [2]=>
          array(2) {
            [0]=>
            int(165)
            [1]=>
            int(175)
          }
        }
      }
      [6]=>
      array(3) {
        ["form"]=>
        string(12) "банкой"
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
        array(1) {
          [0]=>
          array(2) {
            [0]=>
            int(169)
            [1]=>
            int(174)
          }
        }
      }
      [7]=>
      array(3) {
        ["form"]=>
        string(12) "банкою"
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
        array(1) {
          [0]=>
          array(2) {
            [0]=>
            int(169)
            [1]=>
            int(174)
          }
        }
      }
      [8]=>
      array(3) {
        ["form"]=>
        string(10) "банку"
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
        array(1) {
          [0]=>
          array(2) {
            [0]=>
            int(168)
            [1]=>
            int(174)
          }
        }
      }
      [9]=>
      array(3) {
        ["form"]=>
        string(10) "банок"
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
        array(1) {
          [0]=>
          array(2) {
            [0]=>
            int(166)
            [1]=>
            int(175)
          }
        }
      }
    }
  }
}
