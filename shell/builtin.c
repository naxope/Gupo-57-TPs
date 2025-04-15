#include "builtin.h"

// returns true if the 'exit' call
// should be performed
//
// (It must not be called from here)
int
exit_shell(char *cmd)
{
	// Your code here

	return 0;
}

// returns true if "chdir" was performed
//  this means that if 'cmd' contains:
// 	1. $ cd directory (change to 'directory')
// 	2. $ cd (change to $HOME)
//  it has to be executed and then return true
//
//  Remember to update the 'prompt' with the
//  	new directory.
//
// Examples:
//  1. cmd = ['c','d', ' ', '/', 'b', 'i', 'n', '\0']
//  2. cmd = ['c','d', '\0']
int
cd(char *cmd)
{	
	// Me fijo que:
	// 1. El comando empieze con cd
	// 2. El segundo caracter sea espacio o fin "Por ejemplo que no sea cdf o cdkgfjfd"
	if (strncmp(cmd, "cd", 2) != 0 || (cmd[2] != ' ' && cmd[2] != '\0'))
        return false; 

	// Creo la variable apuntando a referencia nula
	char *dir = NULL;

	// Si no hay argumentos
	if (cmd[2] == "\0"){
		// Debo cambiar a HOME
		dir = getenv("HOME");
	}
	else {
		dir = cmd + 3; 	// Me salteo el cd y el espacio
						// Me quedo con el resto de la cadena
	}
	
	chdir(dir); // Cambio de directorio
	return true;
}

// returns true if 'pwd' was invoked
// in the command line
//
// (It has to be executed here and then
// 	return true)
int
pwd(char *cmd)
{
	// Me fijo que el comando sea pwd
	if(strncmp(cmd, "pwd", 3) != 0)
		return false;
	
	// Declaro el buffer que voy a usar
	char buf[BUFLEN];

	// Busco el directorio actual
	getcwd(buf, sizeof buf);
	// Y lo imprimo
	printf("%s\n", buf);
	return true;

}

// returns true if `history` was invoked
// in the command line
//
// (It has to be executed here and then
// 	return true)
int
history(char *cmd)
{
	// Your code here

	return 0;
}
