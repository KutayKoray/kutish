### completed
- env/*
- utils/*
- exec/exec_prep.c
- builtins/echo.c

### not completed
- builtins/* && !builtins/echo.c
- exec/* && !exec/exec_prep.c

### todo
- implement builtins

### parser
- "e"c'h'o          -> "echo"
- $VAR="abc def"    -> "abc" "def"
- cmd$VAR           -> "cmd" "abc" "def"
- cmd "test string" -> "cmd" "test string"
- ""test""          -> "test"
- ''test''          -> "test"