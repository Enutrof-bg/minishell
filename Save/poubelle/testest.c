
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main()

{
    int stats;
    struct stat buf;  // Structure, pas pointeur

	//creer un dossier test // mkdir test
	// puis executer pour tester // doit afficher isdir
	//puis supprimer et creer un ficher test // touch test
    stats = stat("./test", &buf);  // Passer l'adresse

    if (stats == 0 && S_ISDIR(buf.st_mode))  // Vérifier le succès ET tester st_mode
    {
        printf("isdir\n");
    }
    else if (stats == 0)
    {
        printf("not a directory\n");
    }
    else
    {
        printf("error accessing path\n");
    }
}