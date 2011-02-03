#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#define HOST "10.8.0.10"
#define USER "vpsm"
#define PASS "bla"
#define BASE "vpsm"

int my_atoi (char * str )
{
	int res=atoi(str);
	free(str);
	return res;
}

char   **my_explode(char *str, char separator)
{
	char **res = NULL;
	int  nbstr = 1;
	int  len;
	int  from = 0;
	int  i;
	int  j;

	res = (char **) malloc(sizeof (char *));
	len = strlen(str);
	for (i = 0; i <= len; ++i)
	{
		if ((i == len) || (str[i] == separator))
		{
			res = (char **) realloc(res, ++nbstr * sizeof (char *));
			res[nbstr - 2] = (char *) malloc((i - from + 1) * sizeof (char));
			for (j = 0; j < (i - from); ++j)
				res[nbstr - 2][j] = str[j + from];
			res[nbstr - 2][i - from] = '\0';
			from = i + 1;
			++i;
		}
	}
	res[nbstr - 1] =  NULL;
	return res;
}
/**
 * The va_list method for str() above
 **/

char *vstr(char *format, va_list args)
{
  char *buffer = NULL;
  int va_size = 256;
  /* Parse the format and generate a proper string output */
  do
  {
    va_size *= 2;
    buffer = (char*)realloc(buffer, va_size);
    memset(buffer, 0, va_size);
  } while (vsnprintf(buffer, va_size, format, args) < 0);

  /* Trim any white space at the end */
  char *output = (char*)malloc(strlen(buffer) + 1);
  strcpy(output, buffer);
  free(buffer);
  return output;
}
/**
 * Method to produce a malloc()'d char*, similar to printf()
 **/
char *str(char *format, ...)
{
  va_list args;
  va_start(args,format);
  char *ret = vstr(format, args);
  va_end(args);
  return ret;
}
// Fonction pour logger un message dans le fichier de logs
void log_message(char * message)
{
    FILE *file;
    char infotime[80];
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strftime (infotime,80,"[%d/%m/%y - %X] ",timeinfo);
	if((file = fopen("log.txt","a"))) // Ouverture du fichier en append
	{
	    message=str("%s%s\n",infotime,message);
	    fwrite(message,sizeof(char),strlen(message),file);
	}
	free(message);
	fclose(file);
}
int do_query(char * query)
{
	int res=-1;
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");
  	if(mysql_real_connect(&mysql,HOST,USER,PASS,BASE,0,NULL,0))
  	{
  	    if(mysql_query(&mysql,query))
  	    {
  	        res=1;
  	    }
  	}
    	mysql_close(&mysql);
    	free(query);
  	return res;
}
void update_status()
{

        int vmid=0;
        int status=0;
	FILE *process;
	process = popen("{ vzlist && qm list; } | grep -vi 'status' | tr -s ' ' | cut -d ' ' -f 2,4 | sort -gk1 | sed 's/running/1/' | sed 's/stopped/2/'","r");
	char data[50];
	char **line;
	int vmids[30];
        int vmstatus[30];
        int i=0;
        char* tstatus[3];
        tstatus[0]="";
        tstatus[1]="Actif";
        tstatus[2]="Éteind";
	while(fgets(data,50,process))
	{
		line=my_explode(data,' ');
		vmid=atoi(line[0]);
		status=atoi(line[1]);
		vmids[i]=vmid;
		vmstatus[i]=status;
		//printf("%d is %d \n",vmid,status);
		i++;
		free(line[0]);
		free(line[1]);
		free(line);
	}
	fclose(process);
	int length=i;
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");
	mysql_real_connect(&mysql,HOST,USER,PASS,BASE,0,NULL,0);
        mysql_query(&mysql,"SELECT vmid,status FROM vps ORDER BY vmid");
        MYSQL_RES *result=NULL;
        MYSQL_ROW row;
        result=mysql_use_result(&mysql);
        i=0;
        //printf("test database : \n");
        while((i<length) && (row=mysql_fetch_row(result)))
        {
		unsigned long *lengths=mysql_fetch_lengths(result);
		vmid=my_atoi(str("%.*s", (int) lengths[0], row[0]));
		status=my_atoi(str("%.*s", (int) lengths[1], row[1]));
		//printf("i = %d, vmid=%d, status=%d, dvmid=%d, vstatus=%d\n",i,vmid,status,vmids[i],vmstatus[i]);
		while(i<length && vmids[i]<vmid)
		{
			//log_message(str("VPS %d non trouvé dans la base, passage au VPS %d",vmids[i],vmids[i+1]));
			i++;
		}
		if(vmids[i]==vmid)
		{
			if(vmstatus[i]!=status)
			{
				log_message(str("Changement d'état du VPS %d à %s",vmid,tstatus[vmstatus[i]]));
				do_query(str("UPDATE vps SET status=%d WHERE vmid=%d",vmstatus[i],vmid));
				//printf("%d status updated to %d",vmid,vmstatus[i]);
			}
			i++;
		}
		else if (status==1)
		{
			log_message(str("Statut du VPS %d non récupéré, passage a État %s",vmid,tstatus[2]));
			do_query(str("UPDATE vps SET status=2 WHERE vmid=%d",vmid));
			//printf("vps %d not found, setting to 2",vmid);
		}
			
        }
        mysql_free_result(result);
        mysql_close(&mysql);
}
int exec_process(char * command)
{
	FILE * process = popen(str("%s &>/dev/stdout",command),"r");
	char data[100];
	char **line;
	while(fgets(data,100,process))
	{
		line=my_explode(data,'\n');
		log_message(str("%s: %s",command, line[0]));
		free(line[0]);
		free(line);
	}
	int res=pclose(process);
	return res;
}
void exec_task(char * command,int id)
{
	do_query(str("UPDATE tasks SET status=3 WHERE id=%d",id));
	log_message(str("[Tâche %d] Exécution de : %s",id,command));
	int res=exec_process(command);
	if(res) // Si commande échouée
	{
	    log_message(str("[Tâche %d] Une Erreur est survenue",id));
	    do_query(str("UPDATE tasks SET status=2 WHERE id=%d",id));
	}
	else
	{
	    //exec_process("php update.php");
	    update_status();
	    log_message(str("[Tâche %d] Exécution Terminée",id));
	    do_query(str("UPDATE tasks SET status=1 WHERE id=%d",id));
	}
	free(command);
	
}

int continuer=1;

void sighandler(int signum)
{
	continuer=0;
	log_message(str("Signal %d attrapé, Fermeture...",signum));
	exit(0);
}

int main()
{

	struct sigaction act;

	act.sa_handler = sighandler;
	sigfillset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(15, &act, NULL);
	sigaction(11, &act, NULL);

	char* vctype[3]; // Type du contrôlleur de VPS
	vctype[0]=""; // Rien
	vctype[1]="vzctl"; // OpenVZ
	vctype[2]="qm"; // KVM
	char* ttype[4]; // Type de la commande (tâche)
	ttype[0]=""; //Rien
	ttype[1]="start"; // Démarrage de la VM
	ttype[2]="stop"; // Éteindre la VM
	ttype[3]="shutdown"; // Éteindre la VM par ACPI
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");
        int id=0;
        int vid=0;
        int type=0;
        int status=0;
        int vtype=0;
        unsigned long *lengths;
  	if(mysql_real_connect(&mysql,HOST,USER,PASS,BASE,0,NULL,0))
  	{
  		log_message("Connexion réussie");
  		// Création du daemon
  		int p=fork();
  		if(p!=0) // Si c'est le parent
  		{
  		    // On détache...
  		    printf("VPSMd: Démarrage et détachement de la console...\n");
  		    exit(0);
  		}
  		else
  		{
  		    // On commence le daemon
  		    log_message("Daemon démarré");
  		    while(continuer)
  		    {
  		        // exec_process("php update.php");
  		        update_status();
		        // Rercherche des tâches à effectuer (status 0 : à traiter)
		        mysql_query(&mysql,"SELECT t.id,t.vid,t.type,t.status,v.type AS vtype FROM tasks t JOIN vps v ON t.vid=v.vmid WHERE t.status=0");
		        MYSQL_RES *result=NULL;
		        MYSQL_ROW row;

		        result=mysql_use_result(&mysql);
		        while((row=mysql_fetch_row(result)))
		        {
		           lengths=mysql_fetch_lengths(result);
		           id=my_atoi(str("%.*s", (int) lengths[0], row[0]));
		           vid=my_atoi(str("%.*s", (int) lengths[1], row[1]));
		           type=my_atoi(str("%.*s", (int) lengths[2], row[2]));
		           status=my_atoi(str("%.*s", (int) lengths[3], row[3]));
		           vtype=my_atoi(str("%.*s", (int) lengths[4], row[4]));
		           log_message(str("Tâche numéro %d pour le VPS numero %d, de type %d, statut %d",id,vid,type,status));
		           exec_task(str("%s %s %d",vctype[vtype],ttype[type],vid),id);
		        }
		        mysql_free_result(result);
		        sleep(3);
		    }
        }
        mysql_close(&mysql);
        log_message("Connexion fermée");
        log_message("Fermeture du daemon");
	}
	else
	{
		log_message("Erreur de connexion ! Fermeture du daemon");
	}
	return 0;
}
