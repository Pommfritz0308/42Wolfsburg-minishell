# 42 MINISHELL

### Project status

- [x] History
- [ ] Parsing
- [ ] Path
- [ ] Redirections < > << >> 
- [ ] Pipes
- [ ] Enviroment variables
- [ ] $?
- [ ] Signals
- [ ] Builtins:
	- [ ] echo
	- [ ] cd
	- [ ] pwd
	- [ ] export
	- [ ] unset
	- [ ] env
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

- Find all input pipes < and heredocs << (except ones inside '' or ""), open file descriptors, fill fd_in array (int *). For heredocs we can use -1.
- Find all output pipes > >> (except ones inside '' or ""), open file descriptors, fill fd_out array.
- Fill cmd with the first remaining word (after removing redirections from prompt).
- Fill args with the rest.