#include <boost/config.hpp>
#include <iostream>
#include <string>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/read_dimacs.hpp>
#include "../src/stopwatch/stopwatch.h"

int main()
{

    Stopwatch S;
    S.set_mode(REAL_TIME);

    S.start("TOTAL");
    S.start("READ");
    using namespace boost;

    typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
    typedef adjacency_list<
        vecS, vecS, directedS, property<vertex_name_t, std::string>,
        property<edge_capacity_t, long, property<edge_residual_capacity_t, long, property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

    Graph g;
    long flow;

    property_map<Graph, edge_capacity_t>::type capacity = get(edge_capacity, g);
    property_map<Graph, edge_reverse_t>::type rev = get(edge_reverse, g);
    property_map<Graph, edge_residual_capacity_t>::type residual_capacity = get(edge_residual_capacity, g);

    Traits::vertex_descriptor s, t;
    read_dimacs_max_flow(g, capacity, rev, s, t);
    S.stop("READ");

    S.start("BST");
    flow = push_relabel_max_flow(g, s, t);
    S.stop("BST");
    S.stop("TOTAL");

    std::cout << "Vertices   : " << t + 1 << std::endl;
    std::cout << "Edges      : " << -1 << std::endl;
    // std::cout << "\n";
    std::cout << "BST Flow   : " << flow << std::endl;
    // std::cout << "Sta Flow : " << flowS << std::endl;
    // std::cout << "FF  Flow : " << FF.E.getFlow() << std::endl;
    // std::cout << "\n";
    std::cout << "BST Time   : " << S.get_total_time("BST") << std::endl;
    std::cout << "READ Time  : " << S.get_total_time("READ") << std::endl;
    std::cout << "TOTAL Time : " << S.get_total_time("TOTAL") << std::endl;
    // std::cout << "Sta Time : " << S.get_total_time("S") << endl;
    // std::cout << "FF  Time : " << S.get_total_time("FF") << endl;
    // std::cout << "\n";
    // std::cout << "FF Paths : " << FF.IterationsCount << endl;
    // std::cout << "\n";
    // std::cout << "Push     : " << RTF.PushCount << endl;
    // std::cout << "Relabel  : " << RTF.RelabelCount << endl;
    // std::cout << "Discharge: " << RTF.DischargeCount << endl;


    // std::cout << "c  The total flow:" << std::endl;
    // std::cout << "s " << flow << std::endl << std::endl;

    // std::cout << "c flow values:" << std::endl;
    // graph_traits<Graph>::vertex_iterator u_iter, u_end;
    // graph_traits<Graph>::out_edge_iterator ei, e_end;
    // for (tie(u_iter, u_end) = vertices(g); u_iter != u_end; ++u_iter)
    //     for (tie(ei, e_end) = out_edges(*u_iter, g); ei != e_end; ++ei)
    //         if (capacity[*ei] > 0)
    //             std::cout << "f " << *u_iter << " " << target(*ei, g) << " " << (capacity[*ei] - residual_capacity[*ei]) << std::endl;
    return 0;
}
