#include "pi.hpp"

Pi::Pi(unsigned int pNb_exp, unsigned long pNb_tirage,
				std::string pStatePath, std::string pStateName, std::string pStateExt, 
				std::string pResPath, std::string pResName):
	SeqSplit(pNb_exp, pNb_tirage, pStatePath, 
		pStateName, pStateExt, pResPath, pResName)
{}

Pi::~Pi(){}

void Pi::do_computing(std::fstream& fs, CLHEP::MTwistEngine* mt){
	int cpt=0;
	float x,y,res_tirage=0.0;
	for(unsigned j=0;j<_nb_tirages;j++){
		x=get_genrand(mt);
		y=get_genrand(mt);

		if ((x*x+y*y)<=1.0) cpt++;
	}
	res_tirage=((float)cpt/(float)_nb_tirages)*4.0;

	// SAUVEGARDE RES
	fs << res_tirage << " " << res_tirage*res_tirage;
}

/*renvoit un tableau de float, dans la première case, on renvoit la moyenne, dans la deuxième on renvoit la variance*/
std::vector<float> Pi::monte_carlo (){
	std::vector<float> res_monte_carlo(2);
	res_monte_carlo[0]=0.0;
	res_monte_carlo[1]=0.0;

	compute_res();
	
	// Recuperation des resultats
	for(unsigned i=0;i<_nb_exp;i++){
		std::stringstream nameFile;
		float moy,var;
		nameFile << "res/" << _resPath << _resName << i  << ".txt";
		std::ifstream ifs(nameFile.str().c_str());
		
		ifs >> moy >> var;
		ifs.close();
		
		res_monte_carlo[0]+=moy;
		res_monte_carlo[1]+=var;
	}

	res_monte_carlo[0]/=_nb_exp;
	res_monte_carlo[1]=(res_monte_carlo[1]/_nb_exp)-(res_monte_carlo[0]*res_monte_carlo[0]);
	/*Var = E[X²]-E[X]²*/

	if (DEBUG_MC){
		printf("RESULTAT MOYEN = %f\t VARIANCE = %f\n",res_monte_carlo[0],res_monte_carlo[1]);
	}
	
	return res_monte_carlo;
}

int main (int argc, char* argv[]){
	std::vector<float> res_monte_carlo;
	time_t ms;
	int nb_exp = 10;
	unsigned long nb_tirages = 1000000000;
	
	if (argc>=2){
		sscanf(argv[1],"%d",&nb_exp);
	}
		
	ms = time(NULL);
	Pi pi(nb_exp, nb_tirages,
	 "pi_states/", "state", "state",
	  "pi_res/", "pi");
	
	res_monte_carlo = pi.monte_carlo();
	
	printf("Temps d'execution = %ld\n", (long)time(NULL) - (long)ms);
	printf("Replications sequentiel = %d, Nombre de points = %d\n", nb_exp, (int)nb_tirages);
	printf("PI=%0.15f, PI_Monte Carlo=%0.15f\n",M_PI,res_monte_carlo[0]);
	printf("Ecart de MC_PI par rapport a M_PI %f\n",fabs((res_monte_carlo[0]-M_PI)/M_PI)*100.0);
 	return 0;
}
