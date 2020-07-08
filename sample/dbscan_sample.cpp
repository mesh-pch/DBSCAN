/**
* \brief 
* \author pengcheng (pengcheng@yslrpch@126.com)
* \date 2020-07-07
* \attention CopyrightÃ‚Â©ADC Technology(tianjin)Co.Ltd
* \attention Refer to COPYRIGHT.txt for complete terms of copyright notice
*/


#include <cstdlib>						// C standard library
#include <cstdio>						// C I/O (for sscanf)
#include <cstring>						// string manipulation
#include <fstream>	                    // file I/O
#include <iostream>
#include <vector>
#include "ANN/impl/dbscan.hpp"

int	main(int argc, char **argv)
{
    std::string data_file = "../dataset/test_data.pts";
    std::fstream data_in ;
    data_in.open(data_file, std::ios::in);

    std::vector<std::vector<double>> pts;
    for(int i = 0; i < 500; i++)
    {
        double x, y;
        data_in>>x;
        data_in>>y;
        std::vector<double> pt;
        pt.push_back(x);
        pt.push_back(y);
        pts.push_back(pt);
    }

    dbscan::Dbscan<double> scan = dbscan::Dbscan<double>(2,0.0576,20);
    scan.Run(pts);
    std::vector<std::vector<std::vector<double>>>  res;
    scan.GetCluster(res);
    std::fstream data_out;
    data_out.open("../dataset/dbscan-res.pts", std::ios::out);
    for(std::vector<std::vector<double>> cluter : res)
    {
        data_out<<"@@##@@"<<std::endl;
        for(std::vector<double> pt : cluter)
        {
            data_out<<pt[0]<<" "<<pt[1]<<std::endl;
        }

    }
    data_out.close();
    data_in.close();
   // system("pause");
    return 0;
}
