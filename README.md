# Minishell
## wstęp
### struktura t_data
Jest podstawową strukturą programu. Zbiera informacje na temat działania programu. Zawiera takie elementy jak:
1) input od użytkownika
2) tablicę zmiennych środowiskowych
3) informację o aktualnym folderze
4) pointer do struktury simple_cmd

## lexing
Podczas lexingu input, pobierany od użytkownika poprzez funkcję readline, jest przekształcany w listę dwukierunkową.
Każdy węzeł w liście oznaczany jest albo jako WORD albo jako OPERATOR. Oznaczenia węzłów są zależne od występowania domkniętych cudzysłowów. 
Węzeł oznaczony jako WORD jest po prostu ciągiem liter bądź zawartością cudzysłowia. Oznaczenie OPERATOR dotyczy symboli przekierowań (np. '>', '>>', itd.) oraz symbolu pipe.

## parsing
Podczas parsingu, lista tokenów powstałych podczas lexingu przekształcana jest w strukturę simple_cmd. Jest to skrót od Simple Commands, wyrażenia stosowanego w gramatyce Bash Shell.
Struktura simple_cmd zawiera wszystko co znajduje się przed operatorem '|' (pipe). Jeśli '|' nie występuje w input, wszystkie informacje na temat komendy i przekierowań będą znajdować się w jednej strukturze simple_cmd.
Jeśli występuje jeden operator pipe, powstaną dwie struktury simple_cmd, przy czym pierwsza będzie posiadała pointer do drugiej (next), jak i druga będzie posiadała pointer do pierwszej (prev). Jeśli występuje więcej operatorów pipe, powstają kolejne struktury simple_cmd.
### W strukturze simple_cmd znajdują się następujące elementy:
1) __char **cmd__ - tablica składająca się ze strings, przy czym cmd[0] (np. ls, grep, itd.) to zawsze główna komenda, a kolejne cmd[n] to argumenty do niej. tablica zakończona jest NULL'em, dzięki czemu można jej używać bezpośrednio w funkcji **execve()**. Argumenty są opcjonalne.
2) __char *name__ - string oznaczający nazwę komendy. W większości przypadków jest to to samo, co cmd[0].
3) __char *(..)path__ - w strukturze znajdziemy cztery rodzaje stringów dotyczących przekierowań outputu bądź inputu. Więcej szczegółów w części przekierowywania.
4) __int fd_out, int fd_in__ - file descriptors dla przekierowywań
5) __struct s_simple_cmd	*next__ - pointer do kolejnej struktury simple_cmd, ma to znaczenie przy tworzeniu pipe'ów.
6) __struct s_simple_cmd	*prev__ - pointer to poprzedniej struktury simple_cmd.
7) __bool heredoc__ -  true oznacza, że należy pobrać input z heredoca.
8) __bool parser_done__ - *Nie używać w executing*. jest to oznaczenie używane podczas parsingu, aby oddzielić kolejne struktury simple_cmd od siebie.

### przekierowywanie inputu i outputu
Przed parsingiem defaultowe ustawienia struktury simple_cmd są takie, że wszystkie ścieżki przekierowywania są ustawione na NULL. Jeśli podczas parsingu program odnajdzie przekierowanie, zmienia odpowiednią ścieżkę na nazwę pliku. Przykładowo:

input: echo text > outfile.txt

po parsingu: 

              simple_cmd->output_path = outfile.txt
              simple_cmd->input_path = NULL
              simple_cmd->output_path_append = NULL

input: < input.txt cat

po parsingu: 

              simple_cmd->output_path = NULL
              simple_cmd->input_path = input.txt
              simple_cmd->output_path_append = NULL  

input: < input.txt cat >> outfile.txt

po parsingu: 

              simple_cmd->output_path = NULL
              simple_cmd->input_path = input.txt
              simple_cmd->output_path_append = outfile.txt   

## expanding

Po parsingu następuje etap expandingu, czyli "obróbki" elementów przed executingiem. Dzieją się tam następujące przemiany:
1) zmiana ścieżki względnej (zaczynającej się od './') na ścieżkę absolutną
2) rozszerzenie zmiennych środowiskowych w zależności od cudzysłowów (patrz zasady projektu)
3) wycięcie podwójnych lub pojedynczych cudzysłowów

## executing

