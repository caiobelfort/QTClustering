/*
 * Created by Caio Belfort
 * Contact: caiobelfort90@gmail.com
 */

#ifndef QTCLUSTERING
#define QTCLUSTERING

#include <vector>
#include <algorithm>

using std::vector;
using std::find;

/*
 * Algoritmo de clusterização Quality Threshold Clustering
 * Este algoritmo requer que os tipos templates possuam operador - (subtraçao) e que
 * retorne como resultado um tipo numérico referente a diferença entres os dois objetos do tipo T
 */
template<typename T>
vector<vector<T>> QTClustering(const vector<T> &initial_cluster, double radius)
{
    vector<T> data = initial_cluster; //Cópia
    vector<vector<T>> cluster_collection_temp;
    vector<vector<T>> cluster_collection_final;

    if(data.size() == 0) return cluster_collection_final;

    vector<T> current_cluster;
    vector<unsigned> clustered_indexes;


    for(unsigned i = 0; i < data.size(); ++i) //Cria semente
    {
        //Já está alocado à algum cluster
        if(find(clustered_indexes.begin(), clustered_indexes.end(), i) != clustered_indexes.end()) continue;

        //Escolheu uma semente
        current_cluster.push_back(data[i]);
        clustered_indexes.push_back(i);

        for(unsigned j = 0; j < data.size(); ++j) //Agrupa dados à semente
        {
            //Já está alocado à algum cluster
            if(find(clustered_indexes.begin(), clustered_indexes.end(), j) != clustered_indexes.end()) continue;

            double difference = abs(data[i] - data[j]);
            if(difference <= radius) //Se encaixa com a semente
            {
                current_cluster.push_back(data[j]);
                clustered_indexes.push_back(j);
            }

        }
        cluster_collection_temp.push_back(current_cluster); //Foi formado um cluster temporário
        current_cluster.clear(); //Limpa os dados da variável
    }

    //Após formados todos os clusters temporários, escolher o de maior tamanho.
    vector<T> best_cluster;
    for(unsigned i = 0; i < cluster_collection_temp.size(); ++i)
    {
        if(cluster_collection_temp[i].size() > best_cluster.size())
            best_cluster = cluster_collection_temp[i];
    }

    //Remove os objetos do melhor cluster da base inicial
    for(T obj : best_cluster)
    {
        for(unsigned i = 0; i < data.size(); ++i)
        {
            if(obj == data[i])
            {
                data.erase(data.begin() + i);

                if(i > 0) i--;
            }
        }
    }

    cluster_collection_final.push_back(best_cluster);

    auto result = QTClustering<T>(data, radius);

    for(auto cluster : result)
    {
        if(cluster.size() > 0) //O caso base sempre vai gerar uma cluster de tamanho 0
            cluster_collection_final.push_back(cluster);
    }

    return cluster_collection_final;


}







#endif // QTCLUSTERING

