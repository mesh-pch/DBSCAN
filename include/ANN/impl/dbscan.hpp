/**
* \brief 
* \author pengcheng (pengcheng@yslrpch@126.com)
* \date 2020-07-6
* \attention CopyrightÃ‚Â©ADC Technology(tianjin)Co.Ltd
* \attention Refer to COPYRIGHT.txt for complete terms of copyright notice
*/

#include <vector>
#include <queue>
#include <set>
#include <memory>
#include <ANN/ANN.h>

namespace dbscan
{

template<typename T>
class Dbscan final
{

public:
    using ValeType = T;
    typedef std::vector<std::vector<std::vector<ValeType>>> ClustersType;
    typedef std::vector<std::vector<ValeType>> PtsType;

    Dbscan(const uint dim, const double radius, const uint min_pts);
    void Run(PtsType& pts);
    void GetCluster(ClustersType& cluster);
    void GetNoise(PtsType& noise);

private:
    PtsType input_dataset_;
    ANNkd_tree* kd_tree_ptr_;
    ANNpointArray pts_dataset_;
    std::vector<bool> visited_;
    std::vector<bool> assigned_;
    std::vector<bool> borders_;
    uint min_pts_;
    double radius_;
    uint dim_;
    std::vector<std::vector<uint>>  Clusters;
    std::vector<uint>               Noise;
private:
    inline void AddToCluster(const uint pid, const uint cid)
    {
        Clusters[cid].push_back(pid);
        assigned_[pid] = true;
        // std::cout<<"cid: "<<cid<<" size:"<<Clusters[cid].size()<<std::endl;
    }
    inline void AddToClusterSet(ANNidxArray idx_array_ptr, const int k, const uint cid)
    {
        for(int i = 0; i < k; i++)
        {
            uint pid = idx_array_ptr[i];
            //AddToCluster(pid, cid);
        }
    }
    inline void AddToBorderSet(const uint pid)
    {
        borders_.push_back(pid);
    }
    void  ExpandCluster(const uint cid, int* neighbors, int k);

    void SearchNearst(const uint pid,ANNidxArray* idx_array_ptr, int& k);
};



}