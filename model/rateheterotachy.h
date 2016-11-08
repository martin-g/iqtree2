//
//  rateheterotachy.hpp
//  iqtree
//
//  Created by Minh Bui on 11/8/16.
//
//

#ifndef rateheterotachy_hpp
#define rateheterotachy_hpp


#include "rateheterogeneity.h"

class PhyloTree;

/**
    rate-heterotachy model, allowing for mixed branch lengths
*/
class RateHeterotachy: public RateHeterogeneity {


public:
	/**
		constructor
		@param ncat number of rate categories
        @param sorted_rates TRUE to sort the rate in increasing order
		@param tree associated phylogenetic tree
	*/
    RateHeterotachy(int ncat, string params, bool sorted_rates, PhyloTree *tree);

	/**
		destructor
	*/
    virtual ~RateHeterotachy();

    /**
        save object into the checkpoint
    */
    virtual void saveCheckpoint();

    /**
        restore object from the checkpoint
    */
    virtual void restoreCheckpoint();


	/**
	 * @return model name with parameters in form of e.g. GTR{a,b,c,d,e,f}
	 */
	virtual string getNameParams();


	/**
		return the number of dimensions
	*/
	virtual int getNDim();

	/**
		@return the number of rate categories
	*/
	virtual int getNRate() { return ncategory; }

	/**
		get the number of rate categories for site-specific category model
		@return the number of rate categories
	*/
	virtual int getNDiscreteRate() { return ncategory; }

	/**
		@param category category ID from 0 to #category-1
		@return the rate of the specified category
	*/
	virtual double getRate(int category) { return 1.0; }

	/**
		get the proportion of sites under a specified category.
		@param category category ID from 0 to #category-1
		@return the proportion of the specified category
	*/
	virtual double getProp(int category) { return prop[category]; }

	/**
		optimize parameters. Default is to optimize gamma shape
		@return the best likelihood
	*/
	virtual double optimizeParameters(double gradient_epsilon);

    /** 
        optimize rate parameters using EM algorithm 
        @return log-likelihood of optimized parameters
    */
    double optimizeWithEM();

	/**
		write information
		@param out output stream
	*/
	virtual void writeInfo(ostream &out);

	/**
		write parameters, used with modeltest
		@param out output stream
	*/
	virtual void writeParameters(ostream &out);

    /**
        set number of rate categories
        @param ncat #categories
    */
	virtual void setNCategory(int ncat);


protected:

	/**
		number of rate categories
	*/
	int ncategory;


	/**
	 * proportion of sites for each rate categories
	 */
    double *prop;

	/** TRUE to fix parameters */
	bool fix_params;

    /** true to sort rate in increasing order, false otherwise */
    bool sorted_rates;


};




#endif /* rateheterotachy_hpp */
