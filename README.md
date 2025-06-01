### parser
- "e"c'h'o                               -> "echo"
- $VAR="abc def"                         -> "abc" "def"
- cmd$VAR                                -> "cmd" "abc" "def"
- cmd "test string"                      -> "cmd" "test string"
- ""test""                               -> "test"
- ''test''                               -> "test"
- A="test"                               -> "A=test"
- export "A="test hello" B="cart curt""  -> export "A=test hello"


- handle only space or tabs
- count tabs as spaces or white_spaces
- handle unclosed pipe