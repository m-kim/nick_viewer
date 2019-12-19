#include "DriverBH.h"
#include "BarnesHut.h"
#include <iostream>
#include <fstream>

using namespace std;

DriverBH::DriverBH()
{

    std::ifstream file;
    file.open("/home/mkim/new-edelta-velocity.ply");
    if (!file.is_open()){
        std::cout << "Couldn't open file, exiting..." << std::endl;
    }
    int nbodies = 0;
    std::string line, scratch;
    std::getline(file, line);//ply
    while (line.compare("end_header") != 0){
        std::getline(file, line);//format ascii
        std::string str;
        std::istringstream iss(line);
        iss >> str;
        if (str.compare("element") == 0){
            iss >> str;
            if (str.compare("vertex") == 0){
                iss >> nbodies;
            }
        }
    }
//    std::getline(file, line);//element vertex
//    std::getline(file, line);//property float x
//    std::getline(file, line);//property float y
//    std::getline(file, line);//property float z
//    std::getline(file, line);//element face
//    std::getline(file, line);//property list uchar  int vertex_indices
//    std::getline(file, line);//end_header

    Particle pmin, pmax;
    pmin = Particle(1e6,1e6,1e6);
    pmax = Particle(-1e6,-1e6,-1e6);

    for (int i=0; i<nbodies; i++){
        std::getline(file, line);//end_header
        std::istringstream iss(line);
        Particle prt;
        iss >> prt.x >> prt.y >> prt.z;

        if (prt.x < pmin.x)
            pmin.x = prt.x;
        if (prt.y < pmin.y)
            pmin.y  = prt.y;
        if (prt.z < pmin.z)
            pmin.z = prt.z;
        if (prt.x > pmax.x)
            pmax.x = prt.x;
        if (prt.y > pmax.y)
            pmax.y = prt.y;
        if (prt.z > pmax.z)
            pmax.z = prt.z;

        prts.push_back(prt);


    }
    file.close();

    Vector_f mesh_min, mesh_max;
    mesh_min = Vector_f(pmin[0], pmin[1], pmin[2]);
    mesh_max = Vector_f(pmax[0], pmax[1], pmax[2]);

    Vector_f lengths = mesh_max-mesh_min;
    float max_len = max(lengths.x, max(lengths.y, lengths.z));
    for(int i=0; i<3;i++){
        float delta = max_len - lengths[i];
        if(delta != 0){
            mesh_min[i] = mesh_min[i] - (delta / 2.0f);
            mesh_max[i] = mesh_max[i] + (delta / 2.0f);
        }
    }

    unit_length = (mesh_max[0] - mesh_min[0]);

    for (int i=0; i<prts.size(); i++){
        prts[i][0] -= mesh_min.x;
        prts[i][1] -= mesh_min.y;
        prts[i][2] -= mesh_min.z;

        prts[i] /= unit_length;
    }

    bh = new BarnesHut(prts, pmax);
    //bh->calcForce();
    bh->buildTree(); // Build BN tree based on current pos

    cout << bh->max_depth << endl;
}

DriverBH::~DriverBH()
{

}

void DriverBH::saveParticles(stringstream &fn)
{
    ofstream file;
    file.open(fn.str().c_str());
    for (int i=0; i<prts.size(); i++){
        //if (fabs((prts[i] - bnd_ctr).length() - bnd_r) > 0.00001)
            file << prts[i].x << " " << prts[i].y << " " << prts[i].z << " 0.0 0.0 0.0" << endl;
    }
    file.close();

}
