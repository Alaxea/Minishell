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

### Działanie poszczególnych funkcji:


Funkcja ta ma za zadanie przeszukiwać katalogi podane w zmiennej PATH, aby znaleźć plik wykonywalny odpowiadający podanej komendzie.

Iteracja przez katalogi w PATH: Funkcja przeszukuje każdy katalog w zmiennej PATH.
Łączenie ścieżek: Używa funkcji concat_path, aby połączyć każdy katalog z nazwą komendy.
Sprawdzanie istnienia pliku: Używa lstat, aby sprawdzić, czy plik istnieje i czy jest dostępny.
Sprawdzanie uprawnień: Jeżeli plik istnieje, wywołuje check_permission, aby upewnić się, że użytkownik ma prawo do jego wykonania.
Zwracanie wyniku: W przypadku znalezienia odpowiedniego pliku, wywołuje funkcję execute_path. Jeśli plik nie zostanie znaleziony w żadnym katalogu, zwraca kod błędu 127.
### execute_path
Funkcja ma na celu wykonanie znalezionego pliku wykonywalnego w nowym procesie.

Tworzenie nowego procesu: Używa fork, aby utworzyć nowy proces.
Ustawienie sygnałów: Ustawia domyślne zachowanie dla sygnałów SIGINT i SIGQUIT.
Wykonanie pliku: W dziecku wywołuje execve, aby uruchomić plik wykonywalny z odpowiednimi argumentami i zmiennymi środowiskowymi.
Zarządzanie błędami: W przypadku niepowodzenia execve, wypisuje komunikat o błędzie i kończy proces.
Czekanie na zakończenie procesu: W rodzicu używa waitpid, aby czekać na zakończenie wykonania procesu i zapisuje kod wyjścia.
Zarządzanie pamięcią: Zwolnienie pamięci dla zmiennej bin_path po jej użyciu.

### free_paths
Funkcja ma na celu zwolnienie pamięci zajmowanej przez tablicę ścieżek (wskaźników do łańcuchów znakowych).

Iteruje przez wszystkie elementy tablicy paths, zwalniając każdy z nich.
Na końcu zwalnia pamięć zajmowaną przez samą tablicę.
### concat_path
Funkcja łączy katalog (directory) z nazwą komendy, tworząc pełną ścieżkę do pliku wykonywalnego.

Oblicza długość katalogu i nazwy komendy.
Alokuje pamięć na nowy łańcuch, który będzie przechowywał połączoną ścieżkę.
Kopiuje katalog do nowego łańcucha, dodaje znak /, a następnie dodaje nazwę komendy.
Zwraca połączoną ścieżkę.
### get_env_var
Funkcja wyszukuje wartość zmiennej środowiskowej o podanej nazwie (var_name) w tablicy wskaźników do łańcuchów znakowych (envp).

Iteruje przez wszystkie elementy tablicy envp, sprawdzając, czy dany element zaczyna się od var_name i jest zakończony znakiem =.
Jeśli znajdzie zmienną, zwraca wskaźnik na jej wartość (część po znaku =).
W przeciwnym razie zwraca NULL.
### get_full_path
Funkcja znajduje pełną ścieżkę do pliku wykonywalnego na podstawie nazwy komendy i zmiennej PATH.

Używa funkcji get_env_var, aby uzyskać wartość zmiennej PATH.
Dzieli tę wartość na różne katalogi przy użyciu ft_split.
Iteruje przez katalogi, łącząc każdy z nich z nazwą komendy za pomocą concat_path.
Sprawdza, czy utworzona ścieżka jest dostępna do wykonania za pomocą access.
Jeśli tak, zwraca pełną ścieżkę; w przeciwnym razie zwraca NULL.
### execute_command
Funkcja wykonuje komendę w nowym procesie, wykorzystując fork i execve.

Tworzy nowy proces za pomocą fork.
W procesie dziecka:
Sprawdza ewentualne przekierowania przy pomocy redir_check.
Uzyskuje pełną ścieżkę do komendy przy użyciu get_full_path.
Wykonuje komendę za pomocą execve. Jeśli nie uda się jej wykonać, wypisuje komunikat o błędzie.
W procesie rodzica czeka na zakończenie procesu dziecka za pomocą waitpid.
### check_permission
Funkcja sprawdza, czy dany plik jest plikiem wykonywalnym.

Używa bitów w st_mode struktury stat, aby sprawdzić:
Czy plik jest regularnym plikiem (S_ISREG).
Czy jest wykonywalny przez użytkownika (S_IXUSR).
Zwraca 1, jeśli plik ma odpowiednie uprawnienia, a 0 w przeciwnym razie, wypisując stosowne komunikaty.
### find_script
Funkcja przekształca ścieżkę do skryptu względnego na absolutną.

Sprawdza, czy ścieżka zaczyna się od kropki (.), co oznacza, że jest to ścieżka względna.
Używa ft_substr do uzyskania ścieżki po kropce i łączy ją z aktualnym katalogiem roboczym (pobieranym przez set_env_var).
Jeśli ścieżka nie jest względna, zwraca ją bez zmian.

### close_pipes
Funkcja zamyka wszystkie otwarte deskryptory potoków (fd_in i fd_out) dla wszystkich komend w liście t_simple_cmd.

Iteruje przez wszystkie elementy listy komend.
Dla każdej komendy zamyka deskryptor fd_in, jeśli jest większy od 0.
Dla każdej komendy zamyka deskryptor fd_out, jeśli jest większy od 0.
Przechodzi do następnej komendy, aż do końca listy.
### create_pipes
Funkcja tworzy potoki (pipes) dla wszystkich komend w liście t_simple_cmd, aby umożliwić przekazywanie danych między nimi.

Używa pętli, aby iterować przez wszystkie komendy w liście.
Dla każdej pary komend tworzy nowy potok za pomocą funkcji pipe.
Ustawia deskryptor wyjścia (fd_out) bieżącej komendy na env->fd[1].
Ustawia deskryptor wejścia (fd_in) następnej komendy na env->fd[0].
Zwraca -1 w przypadku błędu przy tworzeniu potoku, w przeciwnym razie zwraca 0.
### fork_and_execute
Funkcja tworzy procesy potomne dla każdej komendy w liście t_simple_cmd i wykonuje je.

Iteruje przez wszystkie komendy w liście.
Dla każdej komendy wywołuje fork, aby utworzyć nowy proces.
W procesie potomnym:
Ustawia standardowe wejście (STDIN_FILENO) na deskryptor fd_in, jeśli jest otwarty.
Ustawia standardowe wyjście (STDOUT_FILENO) na deskryptor fd_out, jeśli jest otwarty.
Zamyka wszystkie potoki, wywołując close_pipes.
Uruchamia komendę za pomocą execve. Jeśli execve zwróci -1, wypisuje błąd i kończy proces z kodem 127.
Kontynuuje do następnej komendy.
### execute
Funkcja koordynuje wykonanie wszystkich komend w liście t_simple_cmd, zarządzając potokami i procesami.

Wywołuje create_pipes, aby utworzyć potoki dla wszystkich komend. Jeśli wystąpi błąd, zwraca -1.
Wywołuje fork_and_execute, aby stworzyć procesy dla komend. Jeśli wystąpi błąd, zwraca -1.
Zamyka wszystkie potoki w procesie głównym, wywołując close_pipes.
Czeka na zakończenie wszystkich procesów potomnych za pomocą waitpid i aktualizuje last_result w strukturze t_data, aby zapisać kod wyjścia ostatniego zakończonego procesu.
Zwraca last_result, czyli kod wyjścia ostatniego procesu.

### do dodania redirection, signals
