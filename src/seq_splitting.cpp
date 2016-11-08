#include "seq_splitting.hpp"

SeqSplit::SeqSplit(unsigned int pNb_exp, std::string pStatePath, 
	std::string pStateName, std::string pStateExt, std::string pResPath, 
	std::string pResName, bool pmode_seq_split = true):
		_mt(NULL),
		_nb_exp(pNb_exp),
		_children(_nb_exp),
		_statePath(pStatePath),	_stateName(pStateName),	_stateExt(pStateExt),
	 	_resPath(pResPath) , _resName(pResName),
	 	_mode_seq_split(pmode_seq_split)
{}

SeqSplit::~SeqSplit(){
	//delete _mt;
}


float SeqSplit::get_genrand(CLHEP::MTwistEngine* mt){
	return mt->flat();		
}

int SeqSplit::compute_res(){
	int status;
	
	for(unsigned i=0;i<_nb_exp;i++){
		// Si on est en mode seq split
		if (_mode_seq_split)
			_children[i]=fork();
	
		// Si on est dans le fork ou si on est pas en mode seq split
		if(!_children[i] || !_mode_seq_split){	
			std::stringstream nameFile, nameState;
			
			nameFile << "res/" << _resPath << _resName << i  << ".txt";
			std::fstream fs(nameFile.str().c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);
		
			nameState << "res/" << _statePath << _stateName  << i << "." << _stateExt;
			_mt = new CLHEP::MTwistEngine();
			_mt->restoreStatus(nameState.str().c_str());
	
			do_computing(fs, _mt);
			fs.close();	
			delete _mt;
			
			abort();
		}
	}
	
	// attente de la fin des calculs (si on est en mode sequence splitting)
	if(_mode_seq_split){
		for(unsigned i=0;i<_nb_exp;i++){
			status =0;
			waitpid(_children[i],&status,0);
		}
	}
	
	return 0;
}

