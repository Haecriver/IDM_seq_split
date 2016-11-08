#include "hasard.hpp"

Hasard::Hasard(unsigned int pNb_exp, std::string pStatePath, 
		std::string pStateName, std::string pStateExt, std::string pResPath, 
		std::string pResName, std::string pmot_recherche="hasard", bool pmode_seq_split=true
	):
	SeqSplit(pNb_exp, pStatePath, 
		pStateName, pStateExt, pResPath, pResName,
		pmode_seq_split),
		_mot_recherche(pmot_recherche)
{
	std::transform(_mot_recherche.begin(), _mot_recherche.end(), _mot_recherche.begin(), ::tolower);
}

Hasard::~Hasard(){}

void Hasard::do_computing(std::fstream& fs, CLHEP::MTwistEngine* mt){
	unsigned index_cur, cpt=0;
	float rand,res_tirage=0.0;
	char lettre_cur;
	bool cont=true, cont_cour=true;
	
	while(cont){
		index_cur=0;
		cont_cour = true;
		while(cont_cour){
			rand=get_genrand(mt);
			rand = (int)(rand*10)%26;
			lettre_cur = 'a' + rand;
			
			cont = _mot_recherche.size()>index_cur;
			cont_cour = cont && _mot_recherche[index_cur] == lettre_cur;
			++index_cur;
		}
		cpt++;
	}
	res_tirage=(float)cpt;

	// SAUVEGARDE RES
	fs << res_tirage << " " << res_tirage*res_tirage;
}

/*renvoit un tableau de float, dans la première case, on renvoit la moyenne, dans la deuxième on renvoit la variance*/
std::vector<float> Hasard::mot_hasard (){
	std::vector<float> res_hasard(2);
	res_hasard[0]=0.0;
	res_hasard[1]=0.0;

	compute_res();
	
	// Recuperation des resultats
	for(unsigned i=0;i<_nb_exp;i++){
		std::stringstream nameFile;
		float moy,var;
		nameFile << "res/" << _resPath << _resName << i  << ".txt";
		std::ifstream ifs(nameFile.str().c_str());
		
		ifs >> moy >> var;
		ifs.close();
		
		res_hasard[0]+=moy;
		res_hasard[1]+=var;
	}

	res_hasard[0]/=_nb_exp;
	res_hasard[1]=(res_hasard[1]/_nb_exp)-(res_hasard[0]*res_hasard[0]);
	/*Var = E[X²]-E[X]²*/

	if (DEBUG_MC){
		std::cout << "RESULTAT MOYEN = "<< res_hasard[0] << " \t VARIANCE = " << res_hasard[1] << std::endl;
	}
	
	return res_hasard;
}

int main (int argc, char* argv[]){
	std::vector<float> res_hasard;
	time_t ms;
	int nb_exp = 10;
	std::string mot_rech = "Has";
	
	if (argc>=2){
		sscanf(argv[1],"%d",&nb_exp);
	}
		
	ms = time(NULL);
	Hasard has(nb_exp,
	 "pi_states/", "state", "state",
	  "hasard_res/", "hasard",
	  mot_rech);
	
	res_hasard = has.mot_hasard();
	
	std::cout 
		<< "Temps d'execution = " << (long)time(NULL) - (long)ms << std::endl 
		<< "Replications sequentiel = " << nb_exp << std::endl
		<< "Phrase a trouver :" << mot_rech << std::endl
		<< "Nombre de tirage moyen pour le mot hasard : " << res_hasard[0] << std::endl
		<< "Variance : "<< res_hasard[1] << std::endl;
 	return 0;
}
