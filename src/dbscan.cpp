/**
* \brief 
* \author pengcheng (pengcheng@yslrpch@126.com)
* \date 2020-07-07
* \attention CopyrightÃ‚Â©ADC Technology(tianjin)Co.Ltd
* \attention Refer to COPYRIGHT.txt for complete terms of copyright notice
*/

#include "ANN/impl/dbscan.hpp"

namespace dbscan
{

template <typename T>
Dbscan<T>::Dbscan(const uint dim, const double radius, const uint min_pts):
        dim_(dim), radius_(radius), min_pts_(min_pts)
{

}

template <typename T>
void Dbscan<T>::GetCluster(ClustersType& cluster)
{
    cluster.clear();
    for(size_t i = 0; i < Clusters.size(); i++)
    {   
        // cluster.push_back(std::vector<std::vector<ValeType>>());
        std::vector<std::vector<ValeType>> cluster_t;
        for(auto pid_cluster : Clusters[i])
        {
            cluster_t.push_back(input_dataset_[pid_cluster]);
        }
        cluster.push_back(cluster_t);
    }
}

template <typename T>
void Dbscan<T>::Run(PtsType& pts)
{
    size_t data_size = pts.size();
    input_dataset_ = pts;
    pts_dataset_ = annAllocPts(data_size, dim_);
    for(size_t i = 0; i < data_size; i++)
    {
        for(uint d = 0; d < dim_; d++)
        {
            pts_dataset_[i][d] = pts[i][d];
        }
    }

    kd_tree_ptr_ = new ANNkd_tree(                  // build search structure
                    pts_dataset_,                   // the data points
                    data_size,                      // number of points
                    dim_);                          // dimension of space

    visited_ = std::vector<bool>(data_size, false);
    assigned_ = std::vector<bool>(data_size, false);

    for(size_t pid = 0; pid < data_size; pid++)
    {
        
        if(!visited_[pid])
        {
            visited_[pid] = true;
            int k;
            int* idx = nullptr;
            SearchNearst(pid, &idx, k);
            if(k < min_pts_)
            {
                continue;
            }
            else
            {
                borders_ = std::vector<bool>(data_size, false);
                size_t cid = Clusters.size();
                Clusters.push_back(std::vector<uint>()); // add a cluster
                AddToCluster(pid, cid);
               // AddToClusterSet(idx, k, cid);                
                ExpandCluster(cid, idx, k);           
            }
            delete[] idx;              
        }
    }
    delete kd_tree_ptr_;
    kd_tree_ptr_ = nullptr;
    annDeallocPts(pts_dataset_);
    annClose();             
}

template<typename T>
void Dbscan<T>::ExpandCluster(const uint cid, int* neighbors, int k)
{
    std::queue<uint> borfers;
    for(int i = 0; i < k; i++)
    {
        int pid = neighbors[i];
        borfers.push(pid);
        borders_[pid] = true;
    }

    while(borfers.size() > 0)
    {
        const uint pid = borfers.front();
        borfers.pop();
        int k;
        if(!visited_[pid])
        {
            visited_[pid] = true;
            int* idx;
            SearchNearst(pid, &idx, k);// idx new in this function
            if(k > min_pts_)
            {
                if(!assigned_[pid]) 
                {
                    AddToCluster(pid, cid);
                  //  AddToClusterSet(idx, k, cid);
                }
                for(int index = 0; index < k; index++)
                { 
                    int bid = idx[index];
                    if(!borders_[bid])
                    {
                        borfers.push(bid);
                        borders_[bid] = true;
                    }
                }
            }
            delete[] idx;
        }
    }
}

template<typename T>
void Dbscan<T>::SearchNearst(const uint pid, ANNidxArray* idx_array_ptr, int& k)
{
    if(nullptr != kd_tree_ptr_)
    {
        ANNpoint query_pt = annAllocPt(dim_);
        for(uint i = 0; i < dim_; i++) query_pt[i] = pts_dataset_[pid][i];
        k = kd_tree_ptr_->annkFRSearch(
            query_pt,
            radius_,
            0
        );
        *idx_array_ptr = new ANNidx[k];
        ANNdistArray dists = new ANNdist[k];
        kd_tree_ptr_->annkSearch(						// search
				query_pt,						// query point
				k,								// number of near neighbors
				*idx_array_ptr,							// nearest neighbors (returned)
				dists);
         delete[] dists;
         annDeallocPt(query_pt);
    }
}

template class Dbscan<double>;
}