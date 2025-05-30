### parser
- "e"c'h'o          -> "echo"
- $VAR="abc def"    -> "abc" "def"
- cmd$VAR           -> "cmd" "abc" "def"
- cmd "test string" -> "cmd" "test string"
- ""test""          -> "test"
- ''test''          -> "test"
- A="test"          -> "A=test"
- "A "B C""         -> "A B" "C"

- handle only space or tabs
