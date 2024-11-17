# Minishell

## Usage

```
git clone git@github.com:Alaxea/Minishell.git minishell
cd minishell
make && ./minishell
```
### Troubleshooting
If you have an error when running **make**, it is probably because you do not have the **readline library** installed on your computer, or that it is not well linked.
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

### search_in_path
Wyszukuje wykonywalną komendę w zmiennej środowiskowej PATH i uruchamia ją, jeśli została znaleziona. Sprawdza, czy komenda zawiera pełną ścieżkę, i wywołuje odpowiednią funkcję w zależności od wyniku.
### find_binary
Szuka pliku wykonywalnego w katalogach zawartych w zmiennej PATH. Sprawdza, czy plik istnieje i ma odpowiednie uprawnienia, a następnie uruchamia go, jeśli jest dostępny.
### execute_path
Uruchamia plik wykonywalny w nowym procesie za pomocą execve. Obsługuje błędy związane z procesami oraz wykonaniem komendy.
### free_paths
Funkcja ta odpowiada za zwalnianie pamięci dla tablicy łańcuchów znakowych (paths).
Przechodzi przez każdy element tablicy paths i zwalnia pamięć związaną z każdym z tych elementów.
Po zwolnieniu pamięci dla wszystkich elementów, zwalnia także samą tablicę.
### concat_path
Funkcja ta tworzy pełną ścieżkę do pliku wykonywalnego, łącząc katalog (dir) z nazwą pliku wykonywalnego (command).
### get_env_var
Funkcja ta wyszukuje zmienną środowiskową o nazwie var_name w tablicy zmiennych środowiskowych envp.
### get_full_path
Funkcja ta zwraca pełną ścieżkę do komendy, jeśli jest ona dostępna w systemie. Sprawdza, czy komenda jest absolutną ścieżką (rozpoczyna się od / lub .), czy jest to komenda, którą trzeba szukać w katalogach określonych w zmiennej środowiskowej PATH.
### execute_command
Funkcja ta wykonuje daną komendę w nowym procesie.
### check_permission
Funkcja ta sprawdza, czy plik jest wykonywalny.
Jeśli plik jest wykonywalny, funkcja zwraca 1, w przeciwnym razie wypisuje komunikat o błędzie i zwraca 0.
### find_script
Znajduje pełną ścieżkę do skryptu, jeśli jest to ścieżka względna. Jeśli skrypt nie jest ścieżką względną, funkcja zwraca po prostu nazwę skryptu.
### close_pipes
Funkcja jest używana do zamknięcia wszelkich otwartych deskryptorów plików, które są używane do przekierowań wejścia/wyjścia, po zakończeniu wykonywania komend.
### create_pipes
Funkcja ta tworzy pipes między kolejnymi poleceniami w przypadku, gdy są one powiązane operatorem (|).
Dla każdego polecenia w łańcuchu tworzy parę deskryptorów (pipe(env->fd)), ustawia odpowiednie deskryptory fd_in i fd_out dla każdego polecenia w łańcuchu, aby połączyć wyjście jednego polecenia z wejściem następnego.
### fork_and_execute
Tworzy procesy potomne, które wykonują komendy z przekierowaniami. Wykonuje komendy wbudowane lub z execve, jeśli są to komendy zewnętrzne.
### execute
Funkcja ta wykonuje procesy związane z uruchamianiem poleceń z możliwymi przekierowaniami i potokami.
Jeśli w łańcuchu jest tylko jedno polecenie (brak potoków), tworzony jest jeden proces potomny, który wykonuje odpowiednią komendę po ewentualnym skonfigurowaniu redirekcji wejścia/wyjścia.
Jeśli jest więcej niż jedno polecenie (z potokami), tworzone są pipes za pomocą create_pipes(), a następnie dla każdego polecenia tworzony jest proces potomny, który ustawia odpowiednie przekierowanie dla stdin i stdout i wykonuje komendę.
Po zakończeniu procesów potomnych, funkcja czeka na ich zakończenie za pomocą waitpid.
### exit_shell
Funkcja jest odpowiedzialna za zakończenie działania programu shell, czyszcząc zasoby tylko wtedy, gdy to konieczne i kończąc proces z odpowiednim kodem zakończenia (sukcesu lub błędu) w zależności od wartości parametru fail.
### copy_env_var
Kopiuje zmienne środowiskowe z tablicy env_var do struktury env. Alokuje pamięć na nowe zmienne środowiskowe, a następnie kopiuje każdą z nich, kończąc tablicę NULL-em.
### set_env_var
Zwraca wartość zmiennej środowiskowej o nazwie name z tablicy env_var. Jeśli zmienna jest obecna, funkcja zwraca jej wartość, w przeciwnym przypadku zwraca NULL.
### add_env_var
Dodaje lub aktualizuje zmienną środowiskową o nazwie name i wartości value w strukturze env. Jeśli zmienna już istnieje, zostaje usunięta przed dodaniem nowej wartości.
### delete_env_var
Usuwa zmienną środowiskową o nazwie name z tablicy env_var w strukturze env. Tworzy nową tablicę zmiennych środowiskowych, kopiując do niej wszystkie zmienne z wyjątkiem usuwanej.
### signals
Funkcja ta ustawia obsługę sygnałów:
1) SIGQUIT jest ignorowany (SIG_IGN), co oznacza, że nie będzie powodował żadnej akcji (ctrl + \).
2) SIGINT jest obsługiwany przez funkcję handle_sigint, co powoduje, że po naciśnięciu (ctrl + C) zostanie wykonane czyszczenie w terminalu.
3) SIGTERM (sygnał zakończenia procesu) jest obsługiwany przez funkcję handle_sigquit, która nie wykonuje żadnych działań, więc sygnał nie ma żadnego efektu.
### redirection
1) in_redir(t_simple_cmd *cmd):
Obsługuje przekierowanie wejścia (<). Otwiera plik wskazany w cmd->input_path w trybie tylko do odczytu (O_RDONLY).
Jeśli plik nie istnieje, wyświetla błąd i kończy program.
Zapisuje oryginalny deskryptor stdin za pomocą dup(STDIN_FILENO) w cmd->saved_stdin.
Zastępuje stdin deskryptorem pliku (przekierowuje wejście z pliku).
Jeśli operacje na deskryptorach nie powiodą się, zamyka pliki i kończy program.
2) append_redir(t_simple_cmd *cmd):
Obsługuje przekierowanie wyjścia z dopisaniem do pliku (>>). Otwiera plik w trybie dopisywania (O_APPEND).
Jeśli plik nie istnieje lub nie ma uprawnień, wyświetla błąd i kończy program.
Zapisuje oryginalny deskryptor stdout w cmd->saved_stdout.
Zastępuje stdout deskryptorem pliku (przekierowuje wyjście do pliku).
Po zakończeniu zamyka deskryptory.
3) out_redir(t_simple_cmd *cmd):
Obsługuje przekierowanie wyjścia do pliku (>). Otwiera plik w trybie zapisu, nadpisując go (O_TRUNC).
Jeśli plik nie istnieje lub nie ma odpowiednich uprawnień, wyświetla błąd i kończy program.
Zapisuje oryginalny deskryptor stdout w cmd->saved_stdout.
Zastępuje stdout deskryptorem pliku (przekierowuje wyjście do pliku).
Po zakończeniu zamyka deskryptory.
4) heredoc_redir(t_simple_cmd *cmd):
Obsługuje przekierowanie wejścia za pomocą heredoc (<<). Tworzy plik tymczasowy .heredoc, do którego zapisuje dane wprowadzone przez użytkownika.
Użytkownik wprowadza dane, aż wpisze delimiter (określony w cmd->delimiter_heredoc), po czym plik jest zamykany.
Plik .heredoc jest otwierany ponownie do odczytu i zawartość jest przekierowywana na stdin za pomocą dup2().
Na końcu plik tymczasowy jest usuwany przy pomocy unlink().
5) redir_check(t_simple_cmd *cmd):
Funkcja ta sprawdza, czy istnieją jakiekolwiek ścieżki wejścia (input_path), wyjścia (output_path), dopisywania (output_path_append) lub heredoc (heredoc).
Funkcja ustawia również zmienne do przechowywania oryginalnych deskryptorów (stdin, stdout), aby po zakończeniu przekierowań móc je przywrócić, jeśli to konieczne.
