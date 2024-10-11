# Minishell
## lexing
Podczas lexingu input, pobierany od użytkownika poprzez funkcję readline, jest przekształcany w listę dwukierunkową.
Każdy węzeł w liście oznaczany jest albo jako WORD albo jako OPERATOR. Oznaczenia węzłów są zależne od występowania domkniętych cudzysłowów. 
Węzeł oznaczony jako WORD jest po prostu ciągiem liter bądź zawartością cudzysłowia. Oznaczenie OPERATOR dotyczy symboli przekierowań (np. '>', '>>', itd.) oraz symbolu pipe.

## parsing
Podczas parsingu, lista tokenów powstałych podczas lexingu przekształcana jest w strukturę simple_cmd. Jest to skrót od Simple Commands, wyrażenia stosowanego w gramatyce Bash Shell.
Struktura simple_cmd zawiera wszystko co znajduje się przed operatorem '|' (pipe). Jeśli '|' nie występuje w input, wszystkie informacje na temat komendy i przekierowań będą znajdować się w jednej strukturze simple_cmd.
Jeśli występuje jeden operator pipe, powstaną dwie struktury simple_cmd, przy czym pierwsza będzie posiadała pointer do drugiej (next), jak i druga będzie posiadała pointer do pierwszej (prev)
