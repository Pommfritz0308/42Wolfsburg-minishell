# 42 MINISHELL

### Project status

- [x] History
- [X] Parsing
- [X] Path
- [X] Redirections < > << >>
- [X] Pipes
- [X] Enviroment variables
- [X] $?
- [X] Signals
- [ ] Builtins:
	- [x] echo
	- [x] cd
	- [x] pwd
	- [x] export
	- [x] unset
	- [x] env
	- [ ] exit
- [ ] Testing, leaks

### Parsing plan

#### General parsing:

- [BONUS] Split prompt by ().
- [BONUS] Split parts by && and ||.
- Replace all \$ENV by values from enviroment variables if any or by nothing except for \$ inside single quotes ('$ENV') and except \$?, \$.
- [BONUS] Wildcards: replace all * by corresponding values from current directory.
- Split prompt to commands by pypes (|) except for | inside single single '' or double "" quotes and except >| (output redirection ignoring noclobber option).
- Iterate throw commands and fill t_cmd list (see command parsing).

#### Command parsing:

- Find all input redirections < and heredocs << (except ones inside '' or ""), open file descriptors, fill fd_in array (int *). For heredocs we can use -1.
- Find all output redirections > >> (except ones inside '' or ""), open file descriptors, fill fd_out array.
- Split what remains by whitespaces (except whitespaces inside '' or "");
- Fill cmd with the first remaining word (after removing redirections from prompt).
- Fill args with the rest.

### Settings

Minishell config file is ~/.minishellrc.
Minishell changes INPUTRC environment variable to ~/.minishellrc.
