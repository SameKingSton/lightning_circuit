#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/optional/optional_io.hpp>

#include "snark.hpp"
#include "test.h"

using namespace libsnark;
using namespace std;

int main(int argc, char**argv)
{
    // Initialize the curve parameters.
    default_r1cs_ppzksnark_pp::init_public_params();

    // create
    auto keypair = generate_keypair<default_r1cs_ppzksnark_pp>();

    stringstream verificationKey;
    verificationKey << keypair.vk;

    ofstream fileOut;
    fileOut.open("vk");
    fileOut << verificationKey.rdbuf();
    fileOut.close();

    stringstream provingKey;
    provingKey << keypair.pk;
    fileOut.open("pk");
    fileOut << provingKey.rdbuf();
    fileOut.close();

    // prove
    r1cs_ppzksnark_proving_key<default_r1cs_ppzksnark_pp> provingKey_in;
    
    ifstream fileIn("pk");
    stringstream provingKeyFromFile;
    if (fileIn) {
       provingKeyFromFile << fileIn.rdbuf();
       fileIn.close();
    }
    provingKeyFromFile >> provingKey_in;

    run_test(provingKey_in);

    // verify
    // some code deleted intentionally
    // bool res = run_verify(verificationKey_in, proof);
    // if(res == true){
    //     cout << "use vk to verify this proof; it is successful." << endl;
    // }else{
    //    cout << "use vk to verify this proof; it is NOT successful." << endl; 
    // }
}

bool run_verify(r1cs_ppzksnark_verification_key<default_r1cs_ppzksnark_pp> &vk, r1cs_ppzksnark_proof<default_r1cs_ppzksnark_pp> &proof){
    // some code deleted intentionally
    return true;
}

bool run_test(r1cs_ppzksnark_proving_key<default_r1cs_ppzksnark_pp>& pk) {
    std::vector<bool> h1_bv(256);
    std::vector<bool> h2_bv(256);
    std::vector<bool> x_bv(256);
    std::vector<bool> r1_bv(256);
    std::vector<bool> r2_bv(256);

    {
        h1_bv = int_list_to_bits({169, 231, 96, 189, 221, 234, 240, 85, 213, 187, 236, 114, 100, 185, 130, 86, 231, 29, 123, 196, 57, 225, 159, 216, 34, 190, 123, 97, 14, 57, 180, 120}, 8);
        h2_bv = int_list_to_bits({253, 199, 66, 55, 24, 155, 80, 121, 138, 60, 36, 201, 186, 221, 164, 65, 194, 53, 192, 159, 252, 7, 194, 24, 200, 217, 57, 55, 45, 204, 71, 9}, 8);
        x_bv = int_list_to_bits({122, 98, 227, 172, 61, 124, 6, 226, 115, 70, 192, 164, 29, 38, 29, 199, 205, 180, 109, 59, 126, 216, 144, 115, 183, 112, 152, 41, 35, 218, 1, 76}, 8);
        r1_bv = int_list_to_bits({180, 34, 250, 166, 200, 177, 240, 137, 204, 219, 178, 17, 34, 14, 66, 65, 203, 6, 191, 16, 141, 210, 73, 136, 65, 136, 152, 60, 117, 24, 101, 18}, 8);
        r2_bv = int_list_to_bits({206, 64, 25, 10, 245, 205, 246, 107, 191, 157, 114, 181, 63, 40, 95, 134, 6, 178, 210, 43, 243, 10, 217, 251, 246, 248, 0, 21, 86, 194, 100, 94}, 8);
    }

    cout << "Trying to generate proof..." << endl;

    // yet, only 40 proofs among all proofs are real.
    for(int i = 1; i <= 80; i++){
        auto proof = generate_proof<default_r1cs_ppzksnark_pp>(pk, h1_bv, h2_bv, x_bv, r1_bv, r2_bv);

        stringstream proofStream;
        proofStream << *proof;

        stringstream proofFileNameStream;
        proofFileNameStream << "proof/proof_" << i;

	std::string proofFileName = proofFileNameStream.str();

        ofstream fileOut;
        fileOut.open(proofFileName);
        fileOut << proofStream.rdbuf();
        fileOut.close();
    }

    cout << "Proof generated!" << endl;

    return true;
}
